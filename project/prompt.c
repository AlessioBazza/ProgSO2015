/* Librerie di Sistema */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Librerie Personali */
#include "functions.h"
#include "utilities.h"

/* Funzione Principale per simulare un prompt */
void funcCommand(char* text, int pid, char* prompt, char* loglevel, char* logfile, char* logstatus, char* logstatustext) {
	/* Variabili per prompt */
	char* line = NULL;			/* Stringa intera digitata dall'utente */
	char* command = NULL;		/* Comando estratto */
	char* params = NULL;		/* Parametri estratti */
	char commandFrom = 'e';		/* Tipo di comando: e = esterno, i = interno */
	int len;					/* Lunghezza stringa */
	
	/* Ciclo per prompt */
	for (;;) {
		
		/* Verifica esistenza di un comando passato dal padre */
		if (text != NULL) {
			line = text;
		} else {
			/* Lettura input utente */
			printf("%s ", prompt);
			getline(&line, (size_t*)&len, stdin);
			if (line[strlen(line) - 1] == '\n')
				line[strlen(line) - 1] = '\0';
		}
		
		/* Divisione stringa in comando e parametri */
		command = funcFindCommand(line);
		params = funcFindParams(line);
		
		/* Prompt di sistema o prompt personale */
		if (line[0] == '!') {
			/* --- SHOWLEVEL */
			if (strcmp(line, "!showlevel") == 0) {
				funcShowlevel(*loglevel);
				logstatustext = malloc(strlen("Livello Log Mostrato") + 1);
				strcpy(logstatustext, "Livello Log Mostrato");
			}
			/* --- LOGON */
			else if (strcmp(line, "!logon") == 0) {
				funcLogOn(logstatus);
				logstatustext = malloc(strlen("Log Attivato") + 1);
				strcpy(logstatustext, "Log Attivato");
			}
			/* -- LOGOFF */
			else if (strcmp(line, "!logoff") == 0) {
				funcLogOff(logstatus);
				logstatustext = malloc(strlen("Log Disattivato") + 1);
				strcpy(logstatustext, "Log Disattivato");
			}
			/* -- LOGSHOW */
			else if (strcmp(line, "!logshow") == 0) {
				funcLogShow(logfile);
				logstatustext = malloc(strlen("Log Mostrato") + 1);
				strcpy(logstatustext, "Log Mostrato");
			}
			/* -- SETLEVEL */
			else if (strncmp(line, "!setlevel", 9) == 0) {
				int len = strlen(line) - 10;
				/* Controllo parametro */
				if (len <= 0) {
					printf("|-> Il comando !setlevel necessita di un input valido\n");
					logstatustext = malloc(strlen("Parametro !setlevel Errato") + 1);
					strcpy(logstatustext, "Parametro !setlevel Errato");;
				} else {
					/* Esecuzione comando */
					if (funcSetLevel(loglevel, params) == 't') {
						funcShowlevel(*loglevel);
						logstatustext = malloc(strlen("Livello Log Modificato") + 1);
						strcpy(logstatustext, "Livello Log Modificato");;
					} else {
						printf("|-> Il comando !setlevel necessita un input valido\n");
						logstatustext = malloc(strlen("Parametro !setlevel Errato") + 1);
						strcpy(logstatustext, "Parametro !setlevel Errato");;
					}
				}
			}
			/* -- SETPROMPT */
			else if (strncmp(line, "!setprompt", 10) == 0) {
				int len = strlen(line) - 11;
				/* Controllo parametro */
				if (len <= 0) {
					printf("|-> Il comando !setprompt necessita un input valido\n");
					logstatustext = malloc(strlen("Parametro !setprompt Errato") + 1);
					strcpy(logstatustext, "Parametro !setprompt Errato");
				} else {
					/* Esecuzione comando */
					prompt = funcSetPrompt(params);
					logstatustext = malloc(strlen("Testo Prompt Modificato") + 1);
					strcpy(logstatustext, "Testo Prompt Modificato");
				}
			}
			/* -- RUN */
			else if (strncmp(line, "!run", 4) == 0) {
				int len = strlen(line) - 5;
				/* Controllo parametro */
				if (len <= 0) {
					printf("|-> Il comando !run necessita un input valido\n");
					logstatustext = malloc(strlen("Parametro Errato") + 1);
					strcpy(logstatustext, "Parametro Errato");
				} else {
					/* Esecuzione comando */
					funcRun(params, prompt, loglevel, logfile, logstatus, logstatustext);
					logstatustext = malloc(strlen("Processo Figlio Creato") + 1);
					strcpy(logstatustext, "Processo Figlio Creato");
				}
			}
			/* -- QUIT */
			else if (strcmp(line, "!quit") == 0) {
				break;
			}
			/* COMANDO NON VALIDO */
			else {
				printf("Comando non valido!\n");
				logstatustext = malloc(strlen("Comando Personale Inesistente") + 1);
				strcpy(logstatustext, "Comando Personale Inesistente");
			}
			/* Comando interno */
			commandFrom = 'i';
		} else {
			/* Prompt di Sistema */
			int err;
			if (strcmp(command, "cd") == 0) {
				err = chdir(params);
			} else {
				err = system(line);
			}
			commandFrom = 'e';
			/* Log Status */
			if (err == 0) {
				logstatustext = malloc(strlen("Comando di Sistema Correttamente Eseguito") + 1);
				strcpy(logstatustext, "Comando di Sistema Correttamente Eseguito");
			} else {
				logstatustext = malloc(strlen("Errore nell'esecuzione del Comando") + 1);
				strcpy(logstatustext, "Errore nell'esecuzione del Comando");
			}
		}
		
		/* Salvo in file di testo i comandi se log è attivo*/
		if (*logstatus == 't') {
			funcWriteLog(logfile, command, params, commandFrom, logstatustext, *loglevel);
		}
		
		/* Uscita se il processo è un figlio */
		if (pid != 0) {
			return;
		}
		
	}
	
	/* Liberazione Memoria */
	free(line);
	free(command);
	free(params);
	free(prompt);
	free(logstatustext);
	free(logfile);
	
}

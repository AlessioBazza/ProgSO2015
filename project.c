#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Libreria gestione stringhe
#include <getopt.h>		// Argomenti input avvio programma
#include <time.h>		// Libreria per creazione data


// DICHIARAZIONE FUNZIONE PRINCIPALE
void funcCommand(char*, char);

// DICHIARAZIONE FUNZIONI PROMPT PERSONALIZZATO ---------------------------------------------------------------------
char* funcShowlevel(char);
void funcLogOn(char*);
void funcLogOff(char*);
void funcLogShow(char*);
char funcSetLevel(char*);
char* funcSetPrompt(char*);
void funcRun(char*);
void funcQuit();


// DICHIARAZIONE FUNZIONI AUSILIARIE --------------------------------------------------------------------------------
char* funcCreateDate();
void funcWriteLog(char*, char*, char, char);
char* funcFindCommand(char*);
char* funcFindParams(char*);


// VARIABILI STATICHE -----------------------------------------------------------------------------------------------
// Argomenti input validi
static struct option long_options[] = {
	{"prompt",		required_argument,	NULL,	'a'},
	{"loglevel",	required_argument,	NULL,	'b'},
	{"logfile",		required_argument,	NULL,	'c'},
	{NULL,			no_argument,		NULL,	0}
};


// VARIABILI PROGRAMMA ----------------------------------------------------------------------------------------------
// Impostazioni programma
char* prompt = NULL;		// Testo prompt
char loglevel = 'm';		// Livello log: l = low, m = middle, h = high
char* logfile = NULL;		// Percorso e nome del file di log
char logstatus = 't';		// Scrittura log: t = true (attivo), f = false (disattivo)
char* logstatustext = NULL;	// Testo risultato esecuzione processo


// MAIN PROGRAM -----------------------------------------------------------------------------------------------------
int main (int argc, char** argv) {

	// Inizializzazione impostazioni
	prompt = ">";
	logfile = "./log.txt";
	
	// Lettura argomenti avvio programma
	int ch = 0;
	while ((ch = getopt_long(argc, argv, "a:b:c", long_options, NULL)) != -1) {
		switch (ch) {
			// Command "--prompt"
			case 'a':
				printf("|-> Il Prompt e' stato impostato a: %s\n", optarg);
				prompt = optarg;
				break;
			// Command "--loglevel"
			case 'b':
				if (strcmp("low", optarg) != 0 && strcmp("middle", optarg) != 0 && strcmp("high", optarg) != 0) {
					printf("|-> Argomento passato per --loglevel errato!\n");
					printf("|-> Livello file log impostato di default a middle\n");
					loglevel = 'm';
				} else {
					loglevel = funcSetLevel(optarg);
					funcShowlevel(loglevel);
				}
				break;
			// Command "--logfile"
			case 'c':
				printf("|-> Il nome impostato per il file log e' %s\n", optarg);
				logfile = optarg;
				break;
		}
	}
	
	funcCommand(NULL, 'f');

	return 0;
}


// FUNZIONE PRINCIPALE ----------------------------------------------------------------------------------------------
void funcCommand(char* text, char parent) {
	
	// char parent -> f = father, c = child
	// Se parent = f, allora il processo chiede l'input e continua fino alla chiusura
	// Se parente = c, il processo viene eseguito in automatico e viene chiuso da solo alla fine
	
	// Variabili per prompt
	char* line = NULL;			// Stringa intera digitata dall'utente
	char* command = NULL;		// Estrazione comando
	char* params = NULL;		// Estrazione parametri
	char commandFrom = 'e';		// Tipo di comando: e = esterno, i = interno
	int len;					// Lunghezza stringa
	
	// Ciclo per prompt
	for (;;) {
		
		if (text != NULL) {
			line = text;
		} else {
			// Lettura input utente
			printf("%s ", prompt);
			getline(&line, (size_t*)&len, stdin);
			if (line[strlen(line) - 1] == '\n')
				line[strlen(line) - 1] = '\0';
		}
			
		// Lettura comando e parametri
		command = funcFindCommand(line);
		params = funcFindParams(line);
		
		// Prompt normale o prompt personale
		if (line[0] == '!') {
			// --- SHOWLEVEL
			if (strcmp(line, "!showlevel") == 0) {
				funcShowlevel(loglevel);
				logstatustext = "Livello Log Mostrato";
			}
			// --- LOGON
			else if (strcmp(line, "!logon") == 0) {
				funcLogOn(&logstatus);
				logstatustext = "Log Attivato";
			}
			// -- LOGOFF
			else if (strcmp(line, "!logoff") == 0) {
				funcLogOff(&logstatus);
				logstatustext = "Log Disattivato";
			}
			// -- LOGSHOW
			else if (strcmp(line, "!logshow") == 0) {
				funcLogShow(logfile);
				logstatustext = "Log Mostrato";
			}
			// -- SETLEVEL
			else if (strncmp(line, "!setlevel", 9) == 0) {
				int len = strlen(line) - 10;
				// Controllo parametro
				if (len <= 0) {
					printf("|-> Il comando !setlevel necessita di un input valido\n");
					logstatustext = "Parametro !setlevel Errato";
				} else {
					// Esecuzione comando
					char temp;
					if ((temp = funcSetLevel(params)) != 'e') {
						loglevel = temp;
						funcShowlevel(loglevel);
						logstatustext = "Livello Log Modificato";
					} else {
						printf("|-> Il comando !setlevel necessita un input valido\n");
						logstatustext = "Parametro !setlevel Errato";
					}
				}
			}
			// -- SETPROMPT
			else if (strncmp(line, "!setprompt", 10) == 0) {
				int len = strlen(line) - 11;
				// Controllo parametro
				if (len <= 0) {
					printf("|-> Il comando !setprompt necessita un input valido\n");
					logstatustext = "Parametro !setprompt Errato";
				} else {
					// Esecuzione comando
					prompt = funcSetPrompt(params);
					logstatustext = "Testo Prompt Modificato";
				}
			}
			// -- RUN
			else if (strncmp(line, "!run", 4) == 0) {
				int len = strlen(line) - 5;
				// Controllo parametro
				if (len <= 0) {
					printf("|-> Il comando !run necessita un input valido\n");
					logstatustext = "Parametro Errato";
				} else {
					// Esecuzione comando
					funcRun(params);
					logstatustext = "Processo Figlio Creato";
				}
			}
			// -- QUIT
			else if (strcmp(line, "!quit") == 0) {
				break;
			}
			// COMANDO NON VALIDO
			else {
				printf("Comando non valido!\n");
				logstatustext = "Comando Personale Inesistente";
			}
			
			// Comando interno
			commandFrom = 'i';
		} else {
			int err = system(line);
			commandFrom = 'e';
			// Log Status
			if (err == 0) {
				logstatustext = "Comando di Sistema Correttamente Eseguito";
			} else {
				logstatustext = "Errore nell'esecuzione del Comando";
			}
		}
		
		// Salvo in file di testo i comandi se log è attivo
		if (logstatus == 't') {
			funcWriteLog(command, params, commandFrom, loglevel);
		}
		
		// Uscita se la durata è impostata a 0
		if (parent == 'c') {
			return;
		}
		
	}
	
	free(line);
}


// FUNZIONI PROMPT PERSONALIZZATO -----------------------------------------------------------------------------------

// Mostra il livello impostato per il file log [low, middle, high]
char* funcShowlevel(char level) {
	printf("|-> Il livello impostato per il file log e' ");
	switch (level) {
		case 'l':
			printf("low\n");
			return "low";
			break;
		case 'm':
			printf("middle\n");
			return "middle";
			break;
		case 'h':
			printf("high\n");
			return "high";
			break;
	}
	return "error";
}

// Attiva la registrazione sul file log
void funcLogOn(char* level) {
	*level = 't';
	printf("|-> Il file di LOG e' stato attivato\n");
}

// Disattiva la registrazione sul file log
void funcLogOff(char* level) {
	*level = 'f';
	printf("|-> Il file di LOG e' stato disattivato\n");
}

// Mostra il file log attuale
void funcLogShow(char* log) {
	FILE *fp;
	long elapsed_seconds;
	char line[256];
	
	// Verifica che il file esista e sia leggibile
	if((fp = fopen(log, "r+")) == NULL){
		printf("|-> Impossibile leggere il file log\n");
		return;
	}
	
	printf("|-> File Log: %s\n", logfile);
	
	// Lettura e stampa del file
	while(fgets(line, 256, fp) != NULL) {
		printf("%s", line);
	}
	
	// Fine lettura
	fclose(fp);
}

// Settaggio del livello del file log
char funcSetLevel(char* level) {
	if (strcmp("low", level) == 0) {
		return 'l';
	} else if (strcmp("middle", level) == 0) {
		return 'm';
	} else if (strcmp("high", level) == 0) {
		return 'h';
	}
	return 'e';
}

char* funcSetPrompt(char* input) {
	char* value = malloc(strlen(input) + 1);
	strcpy(value, input);
	return value;
}

// Azione passata eseguita in un processo figlio
void funcRun(char* params) {
	int parent = getpid();
	int pid = fork();
	
	if (pid == -1) {
		printf("|-> Impossibile creare il processo figlio\n");
	} else if (pid > 0) {
		// Codice padre
		// Attesa che il processo figlio abbia completato per proseguire
		int status;
		waitpid(pid, &status, 0);
	} else {
		// Codice figlio
		printf("|-> Codice eseguito in un processo figlio con PID: %d\n", getpid());
		funcCommand(params, 'c');
		exit(0);
	}
}

void funcQuit() {
	exit(0);
}



// FUNZIONI AUSILIARIE ----------------------------------------------------------------------------------------------

// Creazione data
char* funcCreateDate() {
	char* s = malloc(sizeof(char)*100);
	time_t t = time(NULL);
	struct tm * p = localtime(&t);
	strftime(s, 1000, "%A, %B %d %Y - %X", p);
	return s;
}

// Scrittura file log
void funcWriteLog(char* command, char* params, char source, char loglevel) {
	FILE *fp;
	if ((fp = fopen(logfile, "ab+")) == NULL)
		perror(logfile);
	else
		if (loglevel == 'l')
			fprintf(fp, "[%s]\t%s\t%s\n", funcCreateDate(), command, logstatustext);
		else if (loglevel == 'm')
			fprintf(fp, "[%s]\t%s\t%s\t%s\n", funcCreateDate(), command, params, logstatustext);
		else if (loglevel == 'h')
			fprintf(fp, "[%s]\t%s\t%s\t%s\t%s\n", funcCreateDate(), command, params, (source == 'i' ? "interno" : "esterno"), logstatustext);
	fclose(fp);
}

// Restituisce solo il comando
char* funcFindCommand(char* input) {
	int len;
	// Lunghezza parametri
	if (strchr(input, ' ') != NULL) {
		len = strlen(strchr(input, ' '));
	} else {
		len = 0;
	}
	int total_len = strlen(input);
	
	char* command = NULL;
	command = malloc((total_len - len) + 1);
	for (int i = 0; i < (total_len - len); i++)
		command[i] = input[i];
	
	command[total_len - len] = '\0';

	return command;
}

// Cerca i parametri e li restituisce
char* funcFindParams(char* input) {
	int len;
	// Lunghezza parametri -1 spazio iniziale
	if (strchr(input, ' ') != NULL) {
		len = strlen(strchr(input, ' ')) - 1;
	} else {
		len = 0;
	}
	int total_len = strlen(input);
	
	char* params = NULL;
	if (len > 0) {
		params = malloc(len + 1);
		for (int i = (total_len - len); i < strlen(input); i++)
			params[i-(total_len - len)] = input[i];
		
		params[len] = '\0';
		
	}
	return params;
}
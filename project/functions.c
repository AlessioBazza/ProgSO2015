/* Librerie di Sistema */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/* Librerie Personali */
#include "functions.h"
#include "prompt.h"

void funcShowlevel(char level) {
	printf("|-> Il livello impostato per il file log e' ");
	switch (level) {
		case 'l':
			printf("low\n");
			break;
		case 'm':
			printf("middle\n");
			break;
		case 'h':
			printf("high\n");
			break;
	}
}

/* Attiva la registrazione sul file log */
void funcLogOn(char* level) {
	*level = 't';
	printf("|-> Il file di LOG e' stato attivato\n");
}

/* Disattiva la registrazione sul file log */
void funcLogOff(char* level) {
	*level = 'f';
	printf("|-> Il file di LOG e' stato disattivato\n");
}

/* Mostra il file log attuale */
void funcLogShow(char* log) {
	FILE *fp;
	char line[256];
	/* Verifica che il file esista e sia leggibile */
	if((fp = fopen(log, "r+")) == NULL){
		printf("|-> Impossibile leggere il file log\n");
		return;
	}
	printf("|-> File Log: %s\n", log);
	/* Lettura e stampa del file */
	while(fgets(line, 256, fp) != NULL) {
		printf("%s", line);
	}
	/* Fine lettura */
	fclose(fp);
}

/* Settaggio del livello del file log */
char funcSetLevel(char* level, char* input) {
	if (strcmp("low", input) == 0) {
		*level = 'l';
	} else if (strcmp("middle", input) == 0) {
		*level = 'm';
	} else if (strcmp("high", input) == 0) {
		*level = 'h';
	} else {
		printf("|-> Valore livello file log non esistente\n");
		return 'f';
	}
	return 't';
}

/* Salvataggio del nuovo prompt */
char* funcSetPrompt(char* input) {
	char* tempPrompt;
	tempPrompt = malloc(strlen(input) + 1);
	strcpy(tempPrompt, input);
	return tempPrompt;
}

/* Azione passata eseguita in un processo figlio */
void funcRun(char* params, char* prompt, char* loglevel, char* logfile, char* logstatus, char* logstatustext) {
	int pid = fork();
	if (pid == -1) {
		printf("|-> Impossibile creare il processo figlio\n");
	} else if (pid > 0) {
		/* Codice padre */
		/* Attesa che il processo figlio abbia completato per proseguire */
		int status;
		waitpid(pid, &status, 0);
	} else {
		/* Codice figlio */
		printf("|-> Codice eseguito in un processo figlio con PID: %d\n", getpid());
		funcCommand(params, 1, prompt, loglevel, logfile, logstatus, logstatustext);
		exit(0);
	}
}

/* Uscita dal programma */
void funcQuit() {
	exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Creazione data */
char* funcCreateDate() {
	char* s = malloc(sizeof(char)*100);
	time_t t = time(NULL);
	struct tm * p = localtime(&t);
	strftime(s, 1000, "%A, %B %d %Y - %X", p);
	return s;
}

/* Scrittura file log */
void funcWriteLog(char* logfile, char* command, char* params, char source, char* logstatustext, char loglevel) {
	FILE *fp;
	/* Verifica del file */
	if ((fp = fopen(logfile, "ab+")) == NULL)
		perror(logfile);
	else
		/* Scrittura su file */
		if (loglevel == 'l')
			fprintf(fp, "[%s]\t%s\t%s\n", funcCreateDate(), command, logstatustext);
		else if (loglevel == 'm')
			fprintf(fp, "[%s]\t%s\t%s\t%s\n", funcCreateDate(), command, params, logstatustext);
		else if (loglevel == 'h')
			fprintf(fp, "[%s]\t%s\t%s\t%s\t%s\n", funcCreateDate(), command, params, (source == 'i' ? "interno" : "esterno"), logstatustext);
	/* Chiusura scrittura */
	fclose(fp);
}

/* Restituisce solo il comando */
char* funcFindCommand(char* input) {
	int i;
	int len;
	int totalLen;
	char* command;
	/* Lunghezza parametri */
	if (strchr(input, ' ') != NULL) {
		len = strlen(strchr(input, ' '));
	} else {
		len = 0;
	}
	totalLen = strlen(input);
	/* Creazione della nuova stringa */
	command = NULL;
	command = malloc((totalLen - len) + 1);
	for (i = 0; i < (totalLen - len); i++)
		command[i] = input[i];
	/* Aggiunta del carattere per concludere la stringa */
	command[totalLen - len] = '\0';
	return command;
}

/* Cerca i parametri e li restituisce */
char* funcFindParams(char* input) {
	int i;
	int len;
	int totalLen;
	char* params;
	/* Lunghezza parametri -1 spazio iniziale */
	if (strchr(input, ' ') != NULL) {
		len = strlen(strchr(input, ' ')) - 1;
	} else {
		len = 0;
	}
	totalLen = strlen(input);
	/* Creazione della nuova stringa */
	params = NULL;
	if (len > 0) {
		params = malloc(len + 1);
		for (i = (totalLen - len); i < strlen(input); i++)
			params[i-(totalLen - len)] = input[i];
		/* Aggiunta del carattere per concludere la stringa */
		params[len] = '\0';
		
	}
	return params;
}

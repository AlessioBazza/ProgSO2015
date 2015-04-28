/* Librerie di Sistema */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/* Librerie Personali */
#include "functions.h"
#include "prompt.h"

/* Argomenti input validi */
static struct option long_options[] = {
	{"prompt",		required_argument,	NULL,	'a'},
	{"loglevel",	required_argument,	NULL,	'b'},
	{"logfile",		required_argument,	NULL,	'c'},
	{"assets",		required_argument,	NULL,	'd'},
	{NULL,			no_argument,		NULL,	0}
};

/* Lettura dei parametri passati in input all'avvio del programma */
void funcGetParams(int argc, char** argv, char* prompt, char* loglevel, char* logfile, char* logstatus, char* logstatustext) {
	/* Lettura argomenti avvio programma */
	int ch = 0;
	/* Variabili per assets */
	FILE *fp;
	char line[256];
	char* p;
	/* Controllo dei parametri passati */
	while ((ch = getopt_long(argc, argv, "a:b:c:d", long_options, NULL)) != -1) {
		switch (ch) {
			/* Command "--prompt" */
			case 'a':
				printf("|-> Il Prompt e' stato impostato a: %s\n", optarg);
				free(prompt);
				prompt = malloc(strlen(optarg) + 1);
				strcpy(prompt, optarg);
				break;
			/* Command "--loglevel" */
			case 'b':
				if (strcmp("low", optarg) != 0 && strcmp("middle", optarg) != 0 && strcmp("high", optarg) != 0) {
					printf("|-> Argomento passato per --loglevel errato!\n");
					printf("|-> Livello file log impostato di default a middle\n");
					*loglevel = 'm';
				} else {
					funcSetLevel(loglevel, optarg);
					funcShowlevel(*loglevel);
				}
				break;
			/* Command "--logfile" */
			case 'c':
				printf("|-> Il nome impostato per il file log e' %s\n", optarg);
				free(logfile);
				logfile = malloc(strlen(optarg) + 1);
				strcpy(logfile, optarg);
				break;
			/* Command "--assets" */
			case 'd':
				/* Verifica che il file esista e sia leggibile */
				if((fp = fopen(optarg, "r+")) != NULL){
					printf("|-> ESEMPIO DI UTILIZZO DEL PROMPT PERSONALIZZATO\n");
					/* Lettura e esecuzione comandi */
					while(fgets(line, 256, fp) != NULL) {
						printf("%s %s", prompt, line);
						/* Rimozione del carattere '\n' e sostituzione con '\0' cioè fine stringa */
						p = strchr(line,'\n');
						if (p)
							*p = '\0';
						/* Esecuzione comando */
						funcCommand(line, 1, prompt, loglevel, logfile, logstatus, logstatustext);
					}
					/* Fine lettura */
					fclose(fp);
				}
				exit(0);
				break;
		}
	}
}

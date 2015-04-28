/* Librerie di Sistema */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Librerie Personali */
#include "options.h"
#include "prompt.h"

#define init_prompt ">"
#define init_loglevel 'm'
#define init_logfile "./log.txt"
#define init_logstatus 't'


/* Variabili Statiche */
static char* prompt;
static char loglevel;
static char* logfile;
static char logstatus;
static char* logstatustext;

int main(int argc, char** argv) {
	
	/******************/
	/* INIT VARIABLES */
	/******************/
	
	/* Set Prompt */
	prompt = malloc(strlen(init_prompt) + 1);
	strcpy(prompt, init_prompt);
	/* Set Loglevel */
	loglevel = init_loglevel;
	/* Set LogFile */
	logfile = malloc(strlen(init_logfile) + 1);
	strcpy(logfile, init_logfile);
	/* Set LogStatus */
	logstatus = init_logstatus;
	/* Set LogStatusText */
	logstatustext = NULL;

	
	/*********************/
	/* LETTURA PARAMETRI */
	/*********************/
	
	/* Legge i parametri di avvio del programma */
	funcGetParams(argc, argv, prompt, &loglevel, logfile, &logstatus, logstatustext);
	
	
	/*******************************/
	/* AVVIO PROMPT PERSONALIZZATO */
	/*******************************/
	
	funcCommand(NULL, 0, prompt, &loglevel, logfile, &logstatus, logstatustext);
	
	return 0;
}

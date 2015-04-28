#ifndef SISOP_PROJ_PROMPT_H
#define SISOP_PROJ_PROMPT_H

void funcCommand(char*, int, char*, char*, char*, char*, char*);

#endif

/*
funcPrompt
prende in input un comando come stringa (lo esegue se non è uguale a NULL, altrimenti lo chiede in input), il pid del figlio generato (se è il padre allora 0), la stringa del prompt, l'indirizzo del carattere di loglevel, la stringa con il nome del file di log, l'indirizzo del carattere di attivazione/disattivazione del file log e la stringa con lo status del log
(char*, int, char*, char*, char*, char*, char* -> void)
*/

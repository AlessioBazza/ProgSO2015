#ifndef SISOP_PROJ_FUNCTIONS_H
#define SISOP_PROJ_FUNCTIONS_H

void funcShowlevel(char);
void funcLogOn(char*);
void funcLogOff(char*);
void funcLogShow(char*);
char funcSetLevel(char*, char*);
char* funcSetPrompt(char*);
void funcRun(char*, char*, char*, char*, char*, char*);
void funcQuit();

#endif

/*
funcShowLevel
-> prende in input il carattere del libello attuale e lo restituisce come stringa: ['l', 'm', 'h'] -> ['low', 'middle', 'high']
(void -> char*)

funcLogOn
-> prende in input l'indirizzo di logstatus e modifica il contenuto in 't'
(char* -> void)

funcLogOff
-> prende in input l'indirizzo di logstatus e modifica il contenuto in 'f'
(char* -> void)

funcLogShow
-> prende in input la stringa contentente l'url del file log e lo stampa a video
(char* -> void)

funcSetLevel
-> prende in input l'indirizzo di loglevel e il valore inserito dall'utente e verifica se è corretto; in tal caso lo modifica e restituisce il carattere 't', altrimenti restituisce il carattere 'f'
(char*, char* -> char)

funcSetPrompt
-> prende in input il parametro e lo e lo alloca restituendo il nuovo indirizzo
(char* -> char*)

funcRun
-> prende in input un comando e lo esegue creando un figlio
(char* -> void)

funcQuit
-> close the program
(void -> void)
*/

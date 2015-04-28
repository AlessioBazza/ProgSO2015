#ifndef SISOP_PROJ_UTILITIES_H
#define SISOP_PROJ_UTILITIES_H

char* funcCreateDate();
void funcWriteLog(char*, char*, char*, char, char*, char);
char* funcFindCommand(char*);
char* funcFindParams(char*);

#endif

/*
funcCreateDate
restituisce una stringa con la data attuale
(void -> char*)

funcWriteLog
prende in input il nome del file, la stringa del comando, la stringa dei parametri, il carattere del tipo di risorsa (i = interna, e = esterna), la stringa con lo status del comando e il carattere del livello di file log
(char*, char*, char*, char, char*, char -> void)

funcFindCommand
prende in input la stringa inserita dall'utente e restituisce solo il comando (senza parametri)
(char* -> char*)

funcFindParams
prende in input la stringa inserita dall'utente e restituise solo i parametri (senza il comando)
(char* -> char*)
*/

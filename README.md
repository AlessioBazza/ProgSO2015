# Progetto SO_2015: Shell con logger
Implementare una shell interattiva (che accetti almeno comandi basilari) con le seguenti caratteristiche:
* Deve accettare tre argomenti opzionali: "--prompt <prompt>", "--loglevel <logleve>" e "--logfile <logfile>" per settare un prompt personalizzato, un livello di "logging" (un valore tra "low", "middle", "high") e il file di log: argomenti errati devono mostrare un opportuno avviso.
* Mostra un prompt personalizzato (di default o settato con l'argomento) e accetta comandi tali che sono passati alla shell standard, a meno che il primo carattere non vuoto sia un punto esclamativo, in questo caso ciò che segue è interpretato come un comando “interno” speciale:
  * !showlevel : mostra il livello impostato (default o settato con l'argomento).
  * !logon : attiva il logging.
  * !logoff: disattiva il logging.
  * !logshow : mostra il log attuale (nome del file, eventualmente di default + contenuto).
  * !setlevel <loglevel> : cambia il livello di log.
  * !setpromp <prompt> : cambia il prompt.
  * !run ... : esegue l'azione successiva in un processo separato.
  * !quit : esce dalla shell.
* La shell scrive in un file di log (di default o scelto dall'utente) le azioni svolte, a seconda del livello impostato:
  * Ogni riga inizia con un riferimento al timestamp (*) seguito dal comando eseguito (senza parametri).
  * Se il livello di log è “low” non ci sono altre informazioni intermedie.
  * Se il livello di log è “middle” deve essere riportata l'intera stringa (con tutti i parametri).
  * Se il livello di log è “high” deve essere anche riportata l'indicazione se si tratta di un comando interno o esterno.
  * Ogni riga termina con lo status (codice d'errore) dell'esecuzione del comando lanciato.
CC = gcc
CFLAGS = -Wall -ansi -pedantic
CDEBU = -g

MKDIR_P = mkdir -p
OBJS = functions.o options.o utilities.o prompt.o main.o

help:
	@ echo "\nPrompt personalizzato con funzioni aggiunte al prompt di sistema\n"
	@ echo "Lista comandi make:"
	@ echo "	help   - stampa questo messaggio"
	@ echo "	bin    - genera i binari compilati nella cartella bin"
	@ echo "	assets - genera un file (esempio.txt) di input con esempi di funzioni"
	@ echo "	test   - genera i binari e gli assets e viene lanciato l'eseguibile"
	@ echo "	clean  - elimina i files temporanei, binari e assets generati\n"

# Compilazione del programma
bin: all cleanonly

# Creazione degli assets
assets: cleanonly
	@${MKDIR_P} assets
	@echo "ls\n!showlevel\n!setlevel high\n!logoff\n!logon" > assets/esempio.txt

# Test
test: bin assets
	@./bin/prompt --assets assets/esempio.txt

# Istruzioni per compilare il programma
all: $(OBJS)
	@${MKDIR_P} bin
	$(CC) $(OBJS) -o bin/prompt
main.o: main.c
	$(CC) $(CFLAGS) $(CDEBU) -c main.c
functions.o: functions.c functions.h
	$(CC) $(CFLAGS) $(CDEBU) -c functions.c
options.o: options.c options.h
	$(CC) $(CFLAGS) $(CDEBU) -c options.c
utilities.o: utilities.c utilities.h
	$(CC) $(CFLAGS) $(CDEBU) -c utilities.c
prompt.o: prompt.c prompt.h
	$(CC) $(CFLAGS) $(CDEBU) -c prompt.c

# Cancellazione dei files e delle cartelle generate
clean: cleanonly
	@/bin/rm -rf bin/ assets/
cleanonly:
	@/bin/rm -rf *~ .*~ *.BAK .*.BAK *.o
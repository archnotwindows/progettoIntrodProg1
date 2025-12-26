# Compilatore da utilizzare
CC = gcc

# Flag di compilazione: C99 standard, tutti i warning
CFLAGS = -std=c99 -Wall -Wextra -O2

# Nome dell'eseguibile finale
EXEC = gioco

# Lista dei file oggetto
OBJ = main.o nuovoGioco.o pulisciSchermo.o salvataggi.o

# Header files (dipendenze)
DEPS = nuovoGioco.h pulisciSchermo.h salvataggi.h

# Regola di default
all: $(EXEC)

# Linker
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilazione oggetti
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Pulizia (comando 'make clean')
clean:
	rm -f $(OBJ) $(EXEC)
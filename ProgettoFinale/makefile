# Compilatore da utilizzare
CC = gcc

# Flag di compilazione:
# -Wall -Wextra: Abilitano la maggior parte degli avvisi (warning) utili.
# -std=c99: Usa lo standard C99 come richiesto dal progetto.
# -pedantic: Assicura stretta aderenza allo standard.
CFLAGS = -Wall -Wextra -std=c99 -pedantic

# Nome dell'eseguibile finale
TARGET = GiocoRPG

# Lista di tutti i file sorgente (.c)
SRCS = main.c \
       nuovoGioco.c \
       salvataggi.c \
       menuvillaggio.c \
       menuMissioni.c \
       missione1espdun.c \
       missione2espdun.c \
       missione3espdun.c \
       missionefinale.c \
       negozio.c \
       inventario.c \
       tabellemissioni.c \
       systemclear.c

# Genera automaticamente la lista degli oggetti (.o) dai sorgenti
OBJS = $(SRCS:.c=.o)

# Regola predefinita (quella eseguita scrivendo solo "make")
all: $(TARGET)

# Regola per creare l'eseguibile linkando gli oggetti
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regola generica per compilare ogni file .c in .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per pulire i file compilati (comando: "make clean")
# Nota: Su Windows (cmd) potresti dover cambiare 'rm -f' con 'del'
clean:
	rm -f $(OBJS) $(TARGET)
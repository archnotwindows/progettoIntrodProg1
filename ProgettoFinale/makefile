# Compilatore da utilizzare
CC = gcc

# Flag di compilazione:
# -Wall -Wextra: Abilitano la maggior parte degli avvisi (warning) utili.
# -std=c99: Usa lo standard C99 come richiesto dal progetto.
# -pedantic: Assicura stretta aderenza allo standard.
CFLAGS = -Wall -Wextra -std=c99 -pedantic

# Nome dell'eseguibile finale
TARGET = Gioco

# --- RILEVAMENTO SISTEMA OPERATIVO PER APERTURA FILE ---
# Definisce il comando 'OPEN_CMD' in base al sistema operativo rilevato
ifdef OS
   # Windows (di solito definisce la variabile OS)
   OPEN_CMD = start
else
   UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Darwin)
      # macOS
      OPEN_CMD = open
   else
      # Linux / Altri Unix-like
      OPEN_CMD = xdg-open
   endif
endif
# -------------------------------------------------------

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
clean:
	rm -f $(OBJS) $(TARGET)

# --- GENERAZIONE DOCUMENTAZIONE ---
# Genera la documentazione con Doxygen e la apre automaticamente
doc:
	doxygen Doxyfile
	@echo "Apro la documentazione nel browser..."
	$(OPEN_CMD) html/index.html
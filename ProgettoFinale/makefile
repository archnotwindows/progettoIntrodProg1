# --- IMPOSTAZIONI GENERALI ---
CFLAGS = -Wall -Wextra -std=c99 -pedantic
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

# --- IMPOSTAZIONI LINUX ---
CC_LINUX = gcc
TARGET_LINUX = Gioco
OBJS_LINUX = $(SRCS:.c=.o)

# --- IMPOSTAZIONI WINDOWS ---
# Assicurati di avere mingw installato
CC_WIN = x86_64-w64-mingw32-gcc
TARGET_WIN = Gioco.exe
# Usiamo un'estensione diversa per gli oggetti Windows per non creare conflitti
OBJS_WIN = $(SRCS:.c=.win.o)

# --- RILEVAMENTO OS (Per comando 'make doc') ---
ifdef OS
   OPEN_CMD = start
else
   UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Darwin)
      OPEN_CMD = open
   else
      OPEN_CMD = xdg-open
   endif
endif

# --- REGOLE DI COMPILAZIONE ---

# Regola di default: compila TUTTO (Linux + Windows)
all: linux windows

# 1. Compilazione Linux
linux: $(TARGET_LINUX)

$(TARGET_LINUX): $(OBJS_LINUX)
	$(CC_LINUX) $(CFLAGS) -o $(TARGET_LINUX) $(OBJS_LINUX)

%.o: %.c
	$(CC_LINUX) $(CFLAGS) -c $< -o $@

# 2. Compilazione Windows
windows: $(TARGET_WIN)

$(TARGET_WIN): $(OBJS_WIN)
	$(CC_WIN) $(CFLAGS) -o $(TARGET_WIN) $(OBJS_WIN)

# Regola specifica per creare gli oggetti Windows (.win.o)
%.win.o: %.c
	$(CC_WIN) $(CFLAGS) -c $< -o $@

# --- PULIZIA E UTILITÀ ---

# Pulisce tutto (oggetti linux, oggetti windows ed eseguibili)
clean:
	rm -f *.o *.win.o $(TARGET_LINUX) $(TARGET_WIN)

# Genera documentazione
doc:
	doxygen Doxyfile
	@echo "Apro la documentazione..."
	$(OPEN_CMD) html/index.html
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
CC_WIN = x86_64-w64-mingw32-gcc
TARGET_WIN = Gioco.exe
OBJS_WIN = $(SRCS:.c=.win.o)

# --- RILEVAMENTO OS ---
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

# compila per tutto (Linux + Windows)
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

# per creare gli oggetti Windows (.win.o)
%.win.o: %.c
	$(CC_WIN) $(CFLAGS) -c $< -o $@

# --- PULIZIA E UTILITÀ ---
clean:  # Pulisce i file oggetto e gli eseguibili
	rm -f *.o *.win.o $(TARGET_LINUX) $(TARGET_WIN)

# Genera documentazione
doc:
	doxygen Doxyfile
	@echo "Apro la documentazione..."
	$(OPEN_CMD) html/index.html
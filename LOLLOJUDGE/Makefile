# Makefile per il progetto 

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = gioco

SOURCES = main.c \
          menuiniziale.c \
          menuvillaggio.c \
          menuMissioni.c \
          missione1espdun.c \
          missione2espdun.c \
          missione3espdun.c \
          missionefinale.c \
          inventario.c \
          negozio.c \
          systemclear.c \
          tabellemissioni.c \
          salvataggio.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
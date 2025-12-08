# Nome dell'eseguibile finale
TARGET = gioco

# Compilatore da usare
CC = gcc

# Opzioni di compilazione (-Wall mostra tutti gli avvisi)
CFLAGS = -Wall

# Lista dei file sorgente
SRCS = main.c menuMissioni.c missione1espdun.c negozio.c inventario.c systemclear.c tabellemissioni.c

# Regola principale: crea l'eseguibile
all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Regola per pulire i file generati (reset)
clean:
	rm -f $(TARGET) $(TARGET).exe
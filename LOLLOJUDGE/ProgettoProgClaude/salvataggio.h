#ifndef SALVATAGGIO_H
#define SALVATAGGIO_H

#include "giocatore.h"
#include <time.h>

#define MAX_SALVATAGGI 100

typedef struct {
    Giocatore giocatore;
    time_t timestamp;
    int attivo; // 1 se il salvataggio esiste, 0 se è stato eliminato
} Salvataggio;

// Array globale dei salvataggi
extern Salvataggio salvataggi[MAX_SALVATAGGI];
extern int num_salvataggi;

void salvaPartita(Giocatore* giocatore_ptr);
int menuCaricaSalvataggio(Giocatore* giocatore_ptr);
void eliminaSalvataggio(int indice);

#endif
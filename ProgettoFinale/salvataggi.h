#ifndef SALVATAGGI_H
#define SALVATAGGI_H
#include <stdbool.h>
#include "giocatore.h"

void nuovoSalvataggio(Giocatore* g);
int listaSalvataggi();
int caricaDatiSalvataggio(int n, Giocatore* g);
void eliminaSalvataggio(int n);
// NUOVA FUNZIONE
void modificaSalvataggio(int n); 
bool triggherTrucchi(char tasto);

#endif
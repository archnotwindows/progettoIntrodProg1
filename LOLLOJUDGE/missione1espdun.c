#include <stdio.h>
#include <stdlib.h> // per rand, srand
#include "missione1espdun.h"
#include "tabellemissioni.h"

// Funzione per lanciare un dado a 6 facce
int lanciaDado() {
    return rand() % 6 + 1;
}

void esplora1StanzaDungeon(Giocatore* giocatore_ptr) {
    printf("\n--- INIZIO MISSIONE: PALUDE PUTRESCENTE ---\n");
    printf("Obiettivo: Sconfiggi 3 Generali Orco.\n");

   
}
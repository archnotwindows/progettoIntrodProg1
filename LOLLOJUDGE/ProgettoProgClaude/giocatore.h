#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <stdbool.h>

typedef struct {
    int vita;       
    int monete;     
    int attacco;    
    bool ha_spada;          // Spada acquistata dal negozio
    bool ha_armatura;       // Armatura acquistata
    bool ha_spada_eroe;     // Spada dell'Eroe (dalla Grotta)
    bool ha_chiave;         // Chiave del Castello
    
    // Missioni completate
    bool missione_palude_completata;
    bool missione_magione_completata;
    bool missione_grotta_completata;
} Giocatore;

#endif
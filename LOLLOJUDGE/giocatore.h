#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <stdbool.h>

typedef struct {
    int vita;               // Punti vita del giocatore
    int monete;             // Monete possedute
    int attacco;            // Valore di attacco
    bool ha_spada;          // boolean Spada acquistata 
    bool ha_armatura;       // boolean Armatura acquistata
    bool ha_spada_eroe;     // boolean Spada dell'Eroe 
    bool ha_chiave;         // boolean Chiave del Castello
    
    // Missioni completate
    bool missione_palude_completata;  
    bool missione_magione_completata;
    bool missione_grotta_completata;
} Giocatore;

#endif
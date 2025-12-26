#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <stdbool.h>

typedef struct {
    int vita;               // Punti vita (Max 20)
    int monete;             // Monete possedute
    int attacco;            // Valore di attacco base
    
    // Equipaggiamento
    bool ha_spada;          // Spada del negozio (+1 Att)
    bool ha_armatura;       // Armatura del negozio (-1 Danno subito)
    bool ha_spada_eroe;     // Spada ottenuta dal Drago (+2 Att, sostituisce la spada normale)
    bool ha_chiave;         // Chiave del Castello (ottenuta nella Magione)
    
    // Missioni completate (Flag)
    bool missione_palude_completata;  
    bool missione_magione_completata;
    bool missione_grotta_completata;
    
} Giocatore;

// Helper per inizializzare un giocatore
static inline void initGiocatore(Giocatore* g) {
    g->vita = 20;
    g->monete = 0;
    g->attacco = 0;
    g->ha_spada = false;
    g->ha_armatura = false;
    g->ha_spada_eroe = false;
    g->ha_chiave = false;
    g->missione_palude_completata = false;
    g->missione_magione_completata = false;
    g->missione_grotta_completata = false;
}

#endif
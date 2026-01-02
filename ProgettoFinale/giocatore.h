#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <stdbool.h>

typedef struct {
    int vita;             
    int monete;             
    int attacco;            
    
  
    bool ha_spada;         
    bool ha_armatura;       
    bool ha_spada_eroe;    
    bool ha_chiave;         
    
   
    bool missione_palude_completata;  
    bool missione_magione_completata;
    bool missione_grotta_completata;
    
} Giocatore;


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
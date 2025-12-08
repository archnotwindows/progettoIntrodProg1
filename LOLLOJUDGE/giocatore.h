#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <stdbool.h>

typedef struct {
    int vita;       
    int monete;     
    int attacco;    
    bool missione_palude_finta; 
} Giocatore;

#endif
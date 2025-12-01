#include <stdbool.h>


#ifndef GIOCATORE_H
#define GIOCATORE_H

typedef struct {
    int vita;       // La vita (max 20)
    int monete;     // I soldi
    int attacco;    // Bonus attacco (es. spada +1)
    bool missione_palude_finta; 
} Giocatore;


#endif
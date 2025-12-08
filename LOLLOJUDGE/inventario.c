#include <stdio.h>
#include "inventario.h"

void Inventario(Giocatore* giocatore_ptr){
    printf("----- Inventario Giocatore -----\n");
    printf("Punti Vita: %d\n", giocatore_ptr->vita);
    printf("Monete: %d\n", giocatore_ptr->monete);
    printf("Attacco: %d\n", giocatore_ptr->attacco); // Aggiunto per completezza
    printf("-------------------------------\n");
}
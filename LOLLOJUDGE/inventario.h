#include <stdio.h>



void Inventario(Giocatore* giocatore_ptr){
    printf("----- Inventario Giocatore -----\n");
    printf("Punti Vita: %d\n", giocatore_ptr->vita);
    printf("Monete: %d\n", giocatore_ptr->monete);
    printf("-------------------------------\n");
}
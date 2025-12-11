#include <stdio.h>
#include "inventario.h"

void Inventario(Giocatore* giocatore_ptr){
    printf("----- Inventario Giocatore -----\n");
    printf("Punti Vita: %d\n", giocatore_ptr->vita);
    printf("Monete: %d\n", giocatore_ptr->monete);
    printf("Attacco Base: %d\n", giocatore_ptr->attacco);
    
    printf("\n--- Oggetti ---\n");
    if (giocatore_ptr->ha_spada) {
        printf("- Spada (+1 Attacco)\n");
    }
    if (giocatore_ptr->ha_armatura) {
        printf("- Armatura (-1 Danno)\n");
    }
    if (giocatore_ptr->ha_spada_eroe) {
        printf("- Spada dell'Eroe (+2 Attacco)\n");
    }
    if (giocatore_ptr->ha_chiave) {
        printf("- Chiave del Castello del Signore Oscuro\n");
    }
    
    printf("\n--- Missioni Completate ---\n");
    if (giocatore_ptr->missione_palude_completata) {
        printf("- Palude Putrescente\n");
    }
    if (giocatore_ptr->missione_magione_completata) {
        printf("- Magione Infestata\n");
    }
    if (giocatore_ptr->missione_grotta_completata) {
        printf("- Grotta di Cristallo\n");
    }
    
    printf("-------------------------------\n");
}
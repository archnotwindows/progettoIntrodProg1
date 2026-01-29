/**
 * @file inventario.c
 * @brief Implementazione della visualizzazione dell'inventario
 * @brief Mostra le statistiche del giocatore (vita, monete, attacco) e lo stato dell'inventario.
 */
#include <stdio.h>
#include "inventario.h"

void Inventario(Giocatore* g) {
    printf("===== INVENTARIO EROE =====\n");        
    printf("Salute:      %d/20\n", g->vita);        /**< punti vita default: 20 */
    printf("Monete:      %d\n", g->monete);          /**< monete iniziali: 0   */
    printf("Attacco:     %d (Base)\n", g->attacco);     /**< attacco base: 0     */
    
    printf("Equipaggiamento:\n");   
    if (!g->ha_spada && !g->ha_spada_eroe && !g->ha_armatura && !g->ha_chiave) {     /**< se le variabili degli oggetti sono tutte false,  allora lo zaino è vuoto */
        printf("  (Zaino vuoto)\n");                                               
    } else {
        if (g->ha_spada && !g->ha_spada_eroe) printf("  - Spada di Ferro (+1 Att)\n");        
        if (g->ha_spada_eroe)                 printf("  - SPADA DELL'EROE (+2 Att)\n");
        if (g->ha_armatura)                   printf("  - Armatura di Cuoio (-1 Danni subiti)\n");
        if (g->ha_chiave)                     printf("  - Chiave del Castello Oscuro\n");
    }
    
    printf("Missioni Completate:\n");
    printf("  - Palude:  %s\n", g->missione_palude_completata ? "[X]" : "[ ]");
    printf("  - Magione: %s\n", g->missione_magione_completata ? "[X]" : "[ ]");
    printf("  - Grotta:  %s\n", g->missione_grotta_completata ? "[X]" : "[ ]");
    
    printf("===========================\n");
}
#include <stdio.h>
#include "inventario.h"

void Inventario(Giocatore* g) {
    printf("===== INVENTARIO =====\n");
    printf("Vita: %d/20\n", g->vita);
    printf("Monete: %d\n", g->monete);
    printf("Attacco Base: %d\n", g->attacco);
    printf("Equipaggiamento:\n");
    if (g->ha_spada) printf("- Spada (+1 Att)\n");
    if (g->ha_spada_eroe) printf("- Spada Eroe (+2 Att)\n");
    if (g->ha_armatura) printf("- Armatura (-1 Danni)\n");
    if (g->ha_chiave) printf("- Chiave Castello\n");
    printf("======================\n");


}
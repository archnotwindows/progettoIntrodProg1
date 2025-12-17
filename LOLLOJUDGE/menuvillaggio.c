#include <stdio.h>
#include <stdlib.h>
#include "menuvillaggio.h"
#include "menuMissioni.h"
#include "inventario.h"
#include "systemclear.h"

void menuVillaggio(Giocatore* giocatore_ptr) {
    while (1) {
        puliscischermo();
        printf("===== VILLAGGIO =====\n");
        printf("1. Intraprendi missione\n");
        printf("2. Riposati (Ripristina vita)\n");
        printf("3. Inventario\n");
        printf("4. Salva (Non implementato in questo snippet)\n");
        printf("5. Esci dal gioco\n");
        printf("Scelta: ");
        
        int scelta;
        scanf("%d", &scelta);
        while(getchar() != '\n');

        if (scelta == 1) {
            Menu(giocatore_ptr); 
            if (giocatore_ptr->vita <= 0) return; // Esci se morto
        }
        else if (scelta == 2) {
            giocatore_ptr->vita = 20;
            printf("Ti sei riposato. Vita ripristinata.\n");
            getchar();
        }
        else if (scelta == 3) {
            Inventario(giocatore_ptr);
            getchar();
        }
        else if (scelta == 5) {
            return;
        }
    }
}
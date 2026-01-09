/**
 * @file menuvillaggio.c
 * @brief Implementazione delle funzionalità del villaggio.
 */
#include <stdio.h>
#include <stdlib.h>
#include "menuvillaggio.h"
#include "menuMissioni.h"
#include "inventario.h"
#include "systemclear.h"
#include "salvataggi.h"

void menuVillaggio(Giocatore* giocatore_ptr) {
    while (1) {
        puliscischermo();
        printf("===== VILLAGGIO =====\n");
        printf("1. Intraprendi missione\n");
        printf("2. Riposati (Ripristina vita) - (Costo: Gratis)\n");
        printf("3. Inventario\n");
        printf("4. Salva la partita\n");
        printf("5. Esci al Menu Principale\n");
        printf("Scelta: ");
        
        int scelta;
        if(scanf("%d", &scelta) != 1) { while(getchar()!='\n'); continue; }
        while(getchar() != '\n');

        if (scelta == 1) {
            Menu(giocatore_ptr);
            
            if (giocatore_ptr->vita <= 0) {
                puliscischermo();
                printf("\n=== GAME OVER ===\nSei morto.\n");
                printf("Premi INVIO per tornare al menu principale...");
                getchar(); 
                return; 
            }
        }
        else if (scelta == 2) {
            giocatore_ptr->vita = 20;
            printf("Ti sei riposato. HP ripristinati!\nPremi INVIO..."); 
            getchar();
        }
        else if (scelta == 3) {
            puliscischermo();
            Inventario(giocatore_ptr);
            printf("\nPremi INVIO...");
            getchar();
        }
        else if (scelta == 4) {
            nuovoSalvataggio(giocatore_ptr);
            printf("Premi INVIO...");
            getchar();
        }
        else if (scelta == 5) {
            printf("Stai tornando al menu principale. I progressi non salvati andranno persi.\n");
            printf("Confermi? (s/n): ");
            char c; scanf("%c", &c);
            if(c=='s' || c=='S') return;
        }
    }
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menuvillaggio.h"
#include "menuMissioni.h"
#include "inventario.h"
#include "salvataggio.h"
#include "systemclear.h"

void menuVillaggio(Giocatore* giocatore_ptr) {
    while (1) {
        puliscischermo();
        printf("===== MENU DEL VILLAGGIO =====\n");
        printf("1. Intraprendi una missione\n");
        printf("2. Riposati\n");
        printf("3. Inventario\n");
        printf("4. Salva la partita\n");
        printf("5. Esci\n");
        printf("Seleziona una delle opzioni del menu [1-5]: ");
        
        int scelta;
        scanf("%d", &scelta);
        while(getchar() != '\n');
        
        if (scelta == 1) {
            puliscischermo();
            Menu(giocatore_ptr);
        } else if (scelta == 2) {
            giocatore_ptr->vita = 20;
            printf("Ti sei riposato. Punti vita ripristinati a 20.\n");
            printf("Premi INVIO per continuare...");
            getchar();
        } else if (scelta == 3) {
            puliscischermo();
            Inventario(giocatore_ptr);
            printf("Premi INVIO per continuare...");
            getchar();
        } else if (scelta == 4) {
            salvaPartita(giocatore_ptr);
            printf("Premi INVIO per continuare...");
            getchar();
        } else if (scelta == 5) {
            printf("Stai uscendo dal gioco ricordati di salvare la partita per non perdere i tuoi progressi.\n");
            printf("Sei sicuro di voler procedere? [Si/No]: ");
            char risposta[10];
            scanf("%s", risposta);
            while(getchar() != '\n');
            
            if (strcmp(risposta, "Si") == 0 || strcmp(risposta, "si") == 0) {
                return;
            }
        }
    }
}
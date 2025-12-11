#include <stdio.h>
#include <stdlib.h>
#include "negozio.h"

int lanciaDado();

void negozio(Giocatore* giocatore_ptr) {
    printf("===== Benvenuto nel Negozio! =====\n");
    printf("1. Pozione Curativa (+1d6 Vita) - 4 Monete\n");
    printf("2. Spada (+1 Attacco) - 5 Monete%s\n", giocatore_ptr->ha_spada ? " [GIA' ACQUISTATA]" : "");
    printf("3. Armatura (-1 Danno) - 10 Monete%s\n", giocatore_ptr->ha_armatura ? " [GIA' ACQUISTATA]" : "");
    printf("0. Esci\n");
    printf("Scegli un'opzione [0-3]: ");

    int scelta_negozio;
    scanf("%d", &scelta_negozio);
    while(getchar() != '\n');

    switch(scelta_negozio) {
        case 1:
            if(giocatore_ptr->monete >= 4) {
                int cura = lanciaDado();
                int vecchia_vita = giocatore_ptr->vita;
                giocatore_ptr->vita += cura;
                if (giocatore_ptr->vita > 20) {
                    giocatore_ptr->vita = 20;
                }
                giocatore_ptr->monete -= 4;
                printf("Hai acquistato una Pozione Curativa. Recuperi %d punti vita.\n", giocatore_ptr->vita - vecchia_vita);
                printf("Vita attuale: %d.\n", giocatore_ptr->vita);
            } else {
                printf("Non hai abbastanza monete!\n");
            }
            break;
        case 2:
            if (giocatore_ptr->ha_spada) {
                printf("Hai gia' acquistato la Spada!\n");
            } else if(giocatore_ptr->monete >= 5) {
                giocatore_ptr->ha_spada = true;
                giocatore_ptr->attacco += 1;
                giocatore_ptr->monete -= 5;
                printf("Hai acquistato una Spada. Attacco: %d.\n", giocatore_ptr->attacco);
            } else {
                printf("Non hai abbastanza monete!\n");
            }
            break;
        case 3:
            if (giocatore_ptr->ha_armatura) {
                printf("Hai gia' acquistato l'Armatura!\n");
            } else if(giocatore_ptr->monete >= 10) {
                giocatore_ptr->ha_armatura = true;
                giocatore_ptr->monete -= 10;
                printf("Hai acquistato un'Armatura! Ora subisci -1 danno da ogni attacco.\n");
            } else {
                printf("Non hai abbastanza monete!\n");
            }
            break;
        case 0:
            printf("Uscita dal negozio.\n");
            break;
        default:
            printf("Opzione non valida.\n");
    }
    
    if (scelta_negozio != 0) {
        printf("Premi INVIO per continuare...");
        getchar();
    }
}
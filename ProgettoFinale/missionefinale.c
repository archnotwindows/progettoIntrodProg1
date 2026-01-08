/**
 * @file missionefinale.c
 * @brief Implementazione del combattimento finale (Sasso-Carta-Forbice).
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "missionefinale.h"
#include "systemclear.h"

int mossarandom() {
    return (rand() % 3) + 1;
}

void CombattimentoFinale(Giocatore* g) {
    char* nomi_mosse[3] = {"Scudo", "Magia", "Spada"};
    int vittorie_g = 0;
    int vittorie_s = 0;
    int round = 1;

    puliscischermo();
    printf("=== SCONTRO FINALE CON IL SIGNORE OSCURO ===\n");
    printf("Regole: Scudo batte Spada, Magia batte Scudo, Spada batte Magia.\n");
    printf("Devi vincere 3 round su 5!\n\n");

    while (round <= 5 && vittorie_g < 3 && vittorie_s < 3) {
        int scelta_g;
        printf("\n--- Round %d ---\n", round);
        printf("1. Scudo\n2. Magia\n3. Spada\nScegli: ");
        scanf("%d", &scelta_g);
        while(getchar()!='\n');

        if (scelta_g < 1 || scelta_g > 3) {
            printf("Mossa non valida!\n");
            continue;
        }

        int scelta_s = mossarandom();
        printf("Tu: %s vs Signore Oscuro: %s\n", nomi_mosse[scelta_g - 1], nomi_mosse[scelta_s - 1]);

        if (scelta_g == scelta_s) {
            printf("Pareggio! Il round si ripete.\n");
            continue; 
        }

        bool vince_g = (scelta_g == 1 && scelta_s == 3) ||
                       (scelta_g == 2 && scelta_s == 1) ||
                       (scelta_g == 3 && scelta_s == 2);

        if (vince_g) {
            printf(">> Hai vinto il round!\n");
            vittorie_g++;
        } else {
            printf(">> Il Signore Oscuro vince il round!\n");
            vittorie_s++;
        }
        round++;
    }

    if (vittorie_g >= 3) {
        printf("\n\n============================================\n");
        printf("   VITTORIA! IL SIGNORE OSCURO E' SCONFITTO!   \n");
        printf("============================================\n");
        printf("Hai salvato il villaggio e completato il gioco!\n");
    } else {
        printf("\n\n============================================\n");
        printf("   SCONFITTA... IL MONDO CADE NELLE TENEBRE   \n");
        printf("============================================\n");
        g->vita = 0; 
    }
    printf("Premi INVIO...");
    getchar();
}
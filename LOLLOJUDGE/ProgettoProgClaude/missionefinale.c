#include <stdio.h>
#include <stdlib.h>
#include "missionefinale.h"
#include "systemclear.h"

void missioneFinale(Giocatore* giocatore_ptr) {
    puliscischermo();
    printf("\n======================================\n");
    printf("  CASTELLO DEL SIGNORE OSCURO\n");
    printf("======================================\n");
    printf("\nSei giunto al cospetto del Signore Oscuro!\n");
    printf("Lo scontro finale sta per iniziare...\n\n");
    printf("Premi INVIO per continuare...");
    getchar();
    
    int vittorie_eroe = 0;
    int vittorie_nemico = 0;
    int round = 1;
    
    while (vittorie_eroe < 3 && vittorie_nemico < 3) {
        puliscischermo();
        printf("\n--- SCONTRO FINALE ---\n");
        printf("Round %d su 5 | Eroe %d - Signore Oscuro %d\n\n", round, vittorie_eroe, vittorie_nemico);
        
        printf("Mosse disponibili:\n");
        printf("1. Scudo\n");
        printf("2. Magia\n");
        printf("3. Spada\n");
        printf("Seleziona una delle opzioni [1-3]: ");
        
        int scelta_eroe;
        scanf("%d", &scelta_eroe);
        while(getchar() != '\n');
        
        if (scelta_eroe < 1 || scelta_eroe > 3) {
            printf("Mossa non valida! Perdi il round.\n");
            vittorie_nemico++;
            printf("Premi INVIO per continuare...");
            getchar();
            round++;
            continue;
        }
        
        int scelta_nemico = (rand() % 3) + 1;
        
        const char* mosse[] = {"", "Scudo", "Magia", "Spada"};
        printf("\nIl Signore Oscuro nel frattempo ha scelto %s.\n", mosse[scelta_nemico]);
        
        // Logica Rock-Paper-Scissors
        // Scudo (1) batte Spada (3)
        // Spada (3) batte Magia (2)
        // Magia (2) batte Scudo (1)
        
        if (scelta_eroe == scelta_nemico) {
            printf("Pareggio! Nessuno si aggiudica il round.\n");
        } else if ((scelta_eroe == 1 && scelta_nemico == 3) ||
                   (scelta_eroe == 3 && scelta_nemico == 2) ||
                   (scelta_eroe == 2 && scelta_nemico == 1)) {
            if (scelta_eroe == 1 && scelta_nemico == 3) {
                printf("L'eroe para e si difende dalla Spada del Signore Oscuro.\n");
            } else if (scelta_eroe == 3 && scelta_nemico == 2) {
                printf("L'eroe trafigge la Magia del Signore Oscuro con la Spada!\n");
            } else {
                printf("L'eroe scaglia una Magia che infrange lo Scudo del Signore Oscuro!\n");
            }
            printf("L'eroe si aggiudica il Round!\n");
            vittorie_eroe++;
        } else {
            if (scelta_nemico == 1 && scelta_eroe == 3) {
                printf("Il Signore Oscuro para il colpo con lo Scudo!\n");
            } else if (scelta_nemico == 3 && scelta_eroe == 2) {
                printf("Il Signore Oscuro trafigge la tua Magia con la Spada!\n");
            } else {
                printf("Il Signore Oscuro distrugge il tuo Scudo con una Magia!\n");
            }
            printf("Il Signore Oscuro si aggiudica il Round!\n");
            vittorie_nemico++;
        }
        
        printf("Premi INVIO per continuare...");
        getchar();
        round++;
    }
    
    puliscischermo();
    printf("\n======================================\n");
    if (vittorie_eroe >= 3) {
        printf("       VITTORIA!\n");
        printf("======================================\n");
        printf("\nIl Signore Oscuro e' stato sconfitto!\n");
        printf("La pace torna nel regno grazie al tuo coraggio!\n");
        printf("\n*** CONGRATULAZIONI HAI VINTO! ***\n");
        printf("\nStatistiche finali:\n");
        printf("- Punti Vita: %d\n", giocatore_ptr->vita);
        printf("- Monete: %d\n", giocatore_ptr->monete);
        printf("- Attacco: %d\n", giocatore_ptr->attacco);
        printf("\nGrazie per aver giocato!\n");
        printf("======================================\n");
    } else {
        printf("       SCONFITTA\n");
        printf("======================================\n");
        printf("\nIl Signore Oscuro ti ha sopraffatto...\n");
        printf("\n*** GAME OVER ***\n");
        printf("======================================\n");
    }
    
    printf("\nPremi INVIO per tornare al menu principale...");
    getchar();
}
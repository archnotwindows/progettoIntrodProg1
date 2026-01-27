/**
 * @file nuovoGioco.c
 * @brief Implementazione del menu principale.
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "systemclear.h" 
#include "nuovoGioco.h"
#include "salvataggi.h"
#include "menuvillaggio.h"
#include "giocatore.h"

/**
 * @brief Legge un intero da stdin in modo sicuro.
 * @return L'intero letto o "-1" in caso di errore.
 */
static int leggiIntero() {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; 
        return atoi(buffer);
    }
    return -1;
}

void stampaMenu(bool trucchiAttivi){
    puliscischermo();
    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    if ( trucchiAttivi ){
        printf("|       Il Dungeon Oscuro   (CHEAT MODE)                     |\n");
    } else {
        printf("|                  Il Dungeon Oscuro                |\n");
        printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    }
    printf("| 1) Nuova partita                                  |\n");
    printf("| 2) Carica salvataggio                             |\n");  
    printf("| 3) Esci                                           |\n");
    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
}

void nuovoGioco(){
    char action[100];
    bool trucchiAttivi = false; 
    bool uscita = false;
    Giocatore g; 

    while ( !uscita ){
        stampaMenu(trucchiAttivi);
        printf("Scegli un'opzione: ");    

        if (fgets(action, sizeof(action), stdin) == NULL) continue; 
        
        if (triggherTrucchi(action[0]) == true) {
            trucchiAttivi = true;
            printf("\n!!! TRUCCHI SBLOCCATI !!!\nPremi Invio...");
            getchar();
            continue;
        }

        int intAction = atoi(action);
            
        if ( intAction == 1 ) {
            initGiocatore(&g);
            
            if(trucchiAttivi) {
                g.monete = 1000;
                g.attacco = 10;
            }

            printf("Creazione nuova partita in corso...\n");
            printf("Premi Invio per entrare nel Villaggio...");
            getchar();
            
            menuVillaggio(&g);
        }

        else if ( intAction == 2 ){
            int elenco = listaSalvataggi();
            if (elenco == 0) {
                printf("Premi Invio...");
                getchar();
                continue;
            }

            printf("Scegli un salvataggio da caricare [1-%d] (0 per annullare): ", elenco);
            int nSalvataggio = leggiIntero();

            if (nSalvataggio > 0 && nSalvataggio <= elenco){
                int azione;
                printf("\n1) Carica e Gioca\n2) Elimina\n");
                
                if (trucchiAttivi) {
                    printf("3) MODIFICA (TRUCCHI)\n4) Annulla\n");
                } else {
                    printf("3) Annulla\n");
                }
            
                printf("Scegli: ");
                azione = leggiIntero();
                                
                if ( azione == 1 ){
                    if (caricaDatiSalvataggio(nSalvataggio, &g)) {
                        printf("\nSalvataggio caricato con successo!\n");
                        printf("Premi Invio per entrare nel Villaggio...");
                        getchar();
                        menuVillaggio(&g);
                    } else {
                        printf("Errore nel caricamento del file.\n");
                        printf("Premi Invio per continuare...");
                        getchar();
                    }
                } 
                else if ( azione == 2 ){
                    printf("Sicuro? (1=Si, 2=No): ");
                    if ( leggiIntero() == 1 ) eliminaSalvataggio(nSalvataggio);
                }
                else if ( trucchiAttivi && azione == 3 ) {
                    modificaSalvataggio(nSalvataggio);
                }
            }    
        }
        else if ( intAction == 3 ) uscita = true;
    }
}
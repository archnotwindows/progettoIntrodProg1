#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pulisciSchermo.h"
#include "nuovoGioco.h"
#include "salvataggi.h"

int leggiIntero() {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; 
        return atoi(buffer);
    }
    return -1;
}

void stampaMenu(bool trucchiAttivi){
    pulisciSchermo();

    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    if ( trucchiAttivi ){
        printf("|    La Fuga dal while(1)      [+]trucchi attivi    |\n");
    } else {
        printf("|            La Fuga dal while(1)                   |\n");
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

    while ( !uscita ){
        stampaMenu(trucchiAttivi);
        printf("Scegli un'opzione: ");    

        if (fgets(action, sizeof(action), stdin) == NULL) {
            continue; 
        }
        
        if (triggherTrucchi(action[0]) == true) {
            trucchiAttivi = true;
            printf("\n!!! TRUCCHI SBLOCCATI !!!\n");
            printf("Premi Invio...");
            getchar();
            continue;
        }

        int intAction = atoi(action);
            
        if ( intAction == 1 ) {
            time_t tempoNow = time(NULL);
            struct tm *infoTempo = localtime(&tempoNow);
                    
            char nomeFile[80];
            char percorsoFile[200];
            char data[80];
            
            strftime(nomeFile, sizeof(nomeFile), "%d-%m-%Y_%H-%M-%S", infoTempo);
            sprintf(percorsoFile, "salvataggi/%s.txt", nomeFile);
            strftime(data, sizeof(data), "%d-%m-%Y %H-%M-%S", infoTempo);

            nuovoSalvataggio(percorsoFile, data);
            
            printf("Premi Invio per tornare al menu...");
            getchar();
        }

        else if ( intAction == 2 ){
            int nSalvataggio;
                
            int elenco = listaSalvataggi();
            if (elenco == 0) {
                printf("Premi Invio...");
                getchar();
                continue;
            }

            printf("Scegli un salvataggio da caricare [1-%d]: ", elenco);
            nSalvataggio = leggiIntero();

            if ( nSalvataggio <= elenco && nSalvataggio > 0 ){
                int azione;

                printf("\n--- Gestione Salvataggio %d ---\n", nSalvataggio);
                printf("1) Carica Salvataggio\n");
                printf("2) Elimina salvataggio\n");
                
                if ( trucchiAttivi == true ){
                    printf("3) Modifica salvataggio\n");
                    printf("Scegli l'azione da compiere [1/3]: ");
                }
                else {
                    printf("Scegli l'azione da compiere [1/2]: ");
                }
                
                azione = leggiIntero();
                                
                if ( azione == 1 ){
                    printf("OK! TODO IMPLEMENTARE CARICA UN SALVATAGGIO\n");
                    printf("Premi Invio...");
                    getchar();
                } 
                else if ( azione == 2 ){
                    int decisione;
                    printf("Sicuro di voler eliminare il salvataggio? (1 = si / 2 = no) ");
                    decisione = leggiIntero();
                    
                    if ( decisione == 1 ){
                        eliminaSalvataggio(nSalvataggio);
                    } 
                }
                else if ( trucchiAttivi == true && azione == 3){
                    modificaSalvataggio(nSalvataggio);
                    printf("Premi Invio...");
                    getchar();
                }
            }    
        }
        
        else if ( intAction == 3 ){
            uscita = true;
        }
    }
}
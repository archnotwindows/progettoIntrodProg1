#include <stdio.h>
#include <stdlib.h>
#include "pulisciSchermo.h"
#include "nuovoGioco.h"
#include <time.h>
#include "salvataggi.h"


void stampaMenu(bool trucchiAttivi){
    pulisciSchermo();

    if ( trucchiAttivi == true ){
        printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
        printf("|    La Fuga dal while(1)      [+]trucchi attivi    |\n");
        printf("| 1) nuova partita                                  |\n");
        printf("| 2) carica salvataggio                             |\n");  
        printf("| 3) modifica salvataggio                           |\n");
        printf("| 4) esci                                           |\n");  
        printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    }
    else if ( trucchiAttivi == false ){
        printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
        printf("|            La Fuga dal while(1)                   |\n");
        printf("| 1) nuova partita                                  |\n");
        printf("| 2) carica salvataggio                             |\n");  
        printf("| 3) esci                                           |\n");
        printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    }
}

void nuovoGioco(){
    char action[10];
    bool trucchiAttivi = false; 
    bool exit = false;
    int contatoreTrucchi = 0;

    stampaMenu(trucchiAttivi);

    while ( exit != true ){
        printf("scegli un'opzione: \n");    

        if (fgets(action, sizeof(action), stdin) == NULL) {
            continue; // Errore di lettura, riprova
        }
        
        if (triggherTrucchi(action[0]) == true) {
            trucchiAttivi = true;
            printf("\n!!! TRUCCHI SBLOCCATI !!!\n");
            printf("Premi Invio...");
            getchar();
            stampaMenu(trucchiAttivi);
            continue;
        }

        int intAction = atoi(action);
            
        if ( intAction == 1 ) {
            // il nome del nuovo salvataggio è: giorno_mese_anno_ora_minuti
            time_t tempoNow = time(NULL);
            struct tm *infoTempo = localtime(&tempoNow);
                    
            char nomeFile[80];
            char percorsoFile[200];
            char data[80];
            strftime(nomeFile, sizeof(nomeFile), "%d-%m-%Y_%H-%M:%S", infoTempo);
            sprintf(percorsoFile, "../salvataggi/%s.txt", nomeFile);
            strftime(data, sizeof(data), "%d-%m-%Y %H-%M:%S", infoTempo);
            //printf("%s\n", nomeFile);

            nuovoSalvataggio(percorsoFile, data);
        }

        else if ( intAction == 2 ){
            int nSalvataggio;
                
            int elenco = listaSalvataggi();
            printf("scegli un salvataggio da caricare [1-%d]: ", elenco);
            scanf("%d", &nSalvataggio);

            if ( nSalvataggio <= elenco && nSalvataggio > 0 ){
                int azione;

                printf("\n1) carica Salvataggio\n");
                printf("2) elimina salvataggio\n");
                printf("Scegli l'azione da compiere [1/2] ");
                scanf("%d", &azione);
                                
                if ( azione == 1 ){
                    printf("OK! TODO IMPLEMENTARE CARICA UN SALVATAGGIO\n");
                } 

                if ( azione == 2 ){
                    int decisione;
                    printf("sicuro di voler eliminare il salvataggio? (1 = si / 2 = no) ");
                    scanf("%d", &decisione);
                    if ( decisione == 1 ) printf("ok TODO: implementare elimina salvataggio\n");
                    if ( decisione == 2 ) return;
                }
            }
        }



        if ( trucchiAttivi == false && intAction == 3 ){
            exit = true;
        }
        else if ( trucchiAttivi == true && intAction == 3){
            printf("TODO: implementare cosa fanno i trucchi");
        }
        else if ( trucchiAttivi == true && intAction == 4){
            exit = true;
        }
    }
}    




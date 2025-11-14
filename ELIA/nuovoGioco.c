#include <stdio.h>
#include <stdlib.h>
#include "pulisciSchermo.h"
#include "nuovoGioco.h"
#include <time.h>
#include "salvataggi.h"


void nuovoGioco(){
    int action;

    pulisciSchermo();

    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    printf("|               La Fuga dal while(1)                |\n");
    printf("| 1) nuova partita                                  |\n");
    printf("| 2) carica salvataggio                             |\n");  
    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    
    printf("scegli un'opzione: ");    
    scanf("%d", &action);       // la scelta deve essere 1/2 (int)

    if ( action != 1 && action != 2 ) {
        printf("Scelta non valida, inserisci 1 o 2! \n");
        nuovoGioco();  // richiamo la funzione per far scegliere di nuovo
    }
    else if ( action == 1 ) {
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

    else if ( action == 2 ){
        int nSalvataggio;

        listaSalvataggi();
        printf("scegli un salvataggio da caricare: ");
        scanf("%d", &nSalvataggio);
        
        printf("messaggio temporaneo, il codice esegue bene\n");
        // TODO: CARICA UNA PARTITA
        // TODO: implementa i trucchi
    
    }

    return;
}
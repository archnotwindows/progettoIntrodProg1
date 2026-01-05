#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menuMissioni.h"
#include "systemclear.h"
#include "missione1espdun.h"
#include "missione2espdun.h"
#include "missione3espdun.h"
#include "missionefinale.h" 
#include "inventario.h"
#include "negozio.h"

void Menu(Giocatore* giocatore_ptr) {   
    puliscischermo();
    

    int tutte_completate = giocatore_ptr->missione_palude_completata &&  
                           giocatore_ptr->missione_magione_completata &&
                           giocatore_ptr->missione_grotta_completata;
    
    printf("===== SELEZIONE MISSIONE =====\n");
    
    int opzione_numero = 1;
    int mappa_opzioni[4] = {0}; 

    if (!giocatore_ptr->missione_palude_completata) { 
        printf("%d. Palude Putrescente \n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 1;
        opzione_numero++;
    }
    
    if (!giocatore_ptr->missione_magione_completata) {
        printf("%d. Magione Infestata \n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 2;
        opzione_numero++;
    }
    
    if (!giocatore_ptr->missione_grotta_completata) {
        printf("%d. Grotta di Cristallo \n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 3;
        opzione_numero++;
    }
    
    if (tutte_completate) {      
        printf("\n*** MISSIONE FINALE ***\n");
        printf("%d. Castello del Signore Oscuro \n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 4;
        opzione_numero++;
    } 
    else if (opzione_numero == 1) {
        printf("Non ci sono missioni disponibili (Errore).\n");
        getchar();
        return;
    }
    
    printf("\n0. Annulla e torna al Villaggio\n");
    printf("Seleziona una missione: ");
    
    int scelta;
    if(scanf("%d", &scelta) != 1) { while(getchar()!='\n'); return; }
    while(getchar() != '\n');
    
    if(scelta == 0) return;
    if(scelta < 1 || scelta >= opzione_numero) return; 
    
    int missione_scelta = mappa_opzioni[scelta - 1]; 
    
    
    if (missione_scelta == 4) { // se é la missione finale passo subito alla funzione dedicata
        CombattimentoFinale(giocatore_ptr);
        return;
    }


    int stanza_corrente = 1; 
    int progressi_missione = 0; 

    while (true) { 
        puliscischermo();
        printf("===== MISSIONE IN CORSO (Stanza %d/10) =====\n", stanza_corrente);
        printf("1. Esplora stanza\n2. Negozio ambulante\n3. Inventario\n4. Fuggi al Villaggio (Costo: 50 monete o Gratis se finita)\n");
        printf("Scelta: ");
        
        int sceltammissione;
        scanf("%d", &sceltammissione);
        while(getchar() != '\n');

        if(sceltammissione == 1){    
            puliscischermo();
            
            if(stanza_corrente > 10) {
                 printf("Dungeon esplorato completamente. Torna al villaggio.\n");
                 getchar();
                 continue;
            }

  
            if(missione_scelta == 1){
                esplora1StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                if (giocatore_ptr->missione_palude_completata) {
                    printf("\n>>> COMPLIMENTI! MISSIONE PALUDE COMPLETATA! <<<\nINVIO per uscire...");
                    getchar();
                    return;
                }
            }
            else if(missione_scelta == 2){
                esplora2StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                if (giocatore_ptr->missione_magione_completata) {
                    printf("\n>>> COMPLIMENTI! MISSIONE MAGIONE COMPLETATA! <<<\nINVIO per uscire...");
                    getchar();
                    return;
                }
            }
            else if(missione_scelta == 3){
                esplora3StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                if (giocatore_ptr->missione_grotta_completata) {
                    printf("\n>>> COMPLIMENTI! MISSIONE GROTTA COMPLETATA! <<<\nINVIO per uscire...");
                    getchar();
                    return;
                }
            }

          
            if (giocatore_ptr->vita <= 0) return; 
        }
        else if(sceltammissione == 2) { 
            negozio(giocatore_ptr); 
        } 
        else if(sceltammissione == 3) { 
            Inventario(giocatore_ptr); 
            printf("Premi INVIO per tornare al menu..."); 
            getchar(); 
        } 
        else if(sceltammissione == 4) { 
            bool finita = (missione_scelta == 1 && giocatore_ptr->missione_palude_completata) ||
                          (missione_scelta == 2 && giocatore_ptr->missione_magione_completata) ||
                          (missione_scelta == 3 && giocatore_ptr->missione_grotta_completata);
            
            if (finita || giocatore_ptr->monete >= 50) {
                if(!finita) {
                    giocatore_ptr->monete -= 50;
                    printf("Hai pagato 50 monete per fuggire codardamente!\n");
                } else {
                    printf("Missione gia' compiuta, torni trionfante.\n");
                }
                getchar();
                return;
            } else {
                printf("Non hai abbastanza monete (50) per corrompere la guida e fuggire!\n");
                getchar();
            }
        }
    }
}
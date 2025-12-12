#include <stdio.h>
#include <stdlib.h>
#include "menuMissioni.h"
#include "systemclear.h"
#include "missione1espdun.h"
#include "missione2espdun.h"
#include "missione3espdun.h"
#include "inventario.h"
#include "negozio.h"

void Menu(Giocatore* giocatore_ptr){
    puliscischermo();
    
    // Controlla se tutte le missioni sono completate
    int tutte_completate = giocatore_ptr->missione_palude_completata &&
                          giocatore_ptr->missione_magione_completata &&
                          giocatore_ptr->missione_grotta_completata;
    
    printf("===== Menu Selezione Missione =====\n");
    
    int opzione_numero = 1;
    int mappa_opzioni[3] = {0}; // Mappa per tracciare quale numero corrisponde a quale missione
    
    if (!giocatore_ptr->missione_palude_completata) {
        printf("%d. Palude Putrescente\n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 1;
        opzione_numero++;
    }
    
    if (!giocatore_ptr->missione_magione_completata) {
        printf("%d. Magione Infestata\n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 2;
        opzione_numero++;
    }
    
    if (!giocatore_ptr->missione_grotta_completata) {
        printf("%d. Grotta di Cristallo\n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 3;
        opzione_numero++;
    }
    
    if (tutte_completate) {
        printf("Hai completato tutte le missioni disponibili. Torna al villaggio per riposare o controllare l'inventario.\n");
        printf("Premi INVIO per tornare...\n");
        getchar();
        return;
    }
    
    printf("Seleziona una missione [1-%d]: ", opzione_numero - 1);
    
    int scelta;
    scanf("%d", &scelta);
    while(getchar() != '\n');
    
    if(scelta < 1 || scelta >= opzione_numero){ 
        printf("Opzione non valida.\n");
        printf("Premi INVIO per continuare...");
        getchar();
        return;
    }
    
    int missione_scelta = mappa_opzioni[scelta - 1];
    
    // Nessuna azione per missione finale (rimosso)
    
    // Altrimenti mostra il menu di missione standard
    while (1) {
        puliscischermo();
        
        // Mostra obiettivo
        printf("===== MISSIONE: ");
        if (missione_scelta == 1) {
            printf("PALUDE PUTRESCENTE =====\n");
            printf("Obiettivo: Eliminare 3 Generale Orco.\n");
        } else if (missione_scelta == 2) {
            printf("MAGIONE INFESTATA =====\n");
            printf("Obiettivo: Recupera la chiave e sconfiggi un Vampiro Superiore.\n");
        } else if (missione_scelta == 3) {
            printf("GROTTA DI CRISTALLO =====\n");
            printf("Obiettivo: Recupera la Spada dell'Eroe.\n");
        }
        
        printf("\nMenu di Missione:\n");
        printf("1. Esplora stanza del Dungeon\n");
        printf("2. Negozio\n");
        printf("3. Inventario\n");
        printf("4. Torna al Villaggio (Paga 50 Monete)\n");
        printf("Seleziona un'opzione [1-4]: ");
        
        int sceltammissione;
        scanf("%d",&sceltammissione);
        while(getchar() != '\n');

        if(sceltammissione == 1){  
           puliscischermo();
           if(missione_scelta == 1){
                esplora1StanzaDungeon(giocatore_ptr);
                
                // Controlla se missione completata o game over
                if (giocatore_ptr->missione_palude_completata) {
                    printf("\nMissione completata! Torni al villaggio.\n");
                    printf("Premi INVIO per continuare...");
                    getchar();
                    return;
                }
                if (giocatore_ptr->vita <= 0) {
                    printf("\n*** GAME OVER ***\n");
                    printf("Premi INVIO per tornare al menu principale...");
                    getchar();
                    return;
                }
           }
           else if(missione_scelta == 2){
                esplora2StanzaDungeon(giocatore_ptr);
                
                if (giocatore_ptr->missione_magione_completata) {
                    printf("\nMissione completata! Torni al villaggio.\n");
                    printf("Premi INVIO per continuare...");
                    getchar();
                    return;
                }
                if (giocatore_ptr->vita <= 0) {
                    printf("\n*** GAME OVER ***\n");
                    printf("Premi INVIO per tornare al menu principale...");
                    getchar();
                    return;
                }
           }
           else if(missione_scelta == 3){
                esplora3StanzaDungeon(giocatore_ptr);
                
                if (giocatore_ptr->missione_grotta_completata) {
                    printf("\nMissione completata! Torni al villaggio.\n");
                    printf("Premi INVIO per continuare...");
                    getchar();
                    return;
                }
                if (giocatore_ptr->vita <= 0) {
                    printf("\n*** GAME OVER ***\n");
                    printf("Premi INVIO per tornare al menu principale...");
                    getchar();
                    return;
                }
           }
        }
        else if(sceltammissione == 2){ 
            puliscischermo();
            negozio(giocatore_ptr);
        }
        else if(sceltammissione == 3){ 
            puliscischermo();
            Inventario(giocatore_ptr);
            printf("Premi INVIO per continuare...");
            getchar();
        }
        else if(sceltammissione == 4){   
            puliscischermo();
            if(giocatore_ptr->monete >= 50){
                giocatore_ptr->monete -= 50;
                printf("Sei tornato al Villaggio pagando 50 monete.\n");
                printf("Premi INVIO per continuare...");
                getchar();
                return;
            } else {
                printf("Non hai abbastanza monete per tornare al Villaggio!\n");
                printf("Premi INVIO per continuare...");
                getchar();
            }
        }
        else{
            printf("Opzione non valida.\n");
            printf("Premi INVIO per continuare...");
            getchar();
        }
    }
}
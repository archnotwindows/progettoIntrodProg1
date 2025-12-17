#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menuMissioni.h"
#include "systemclear.h"
#include "missione1espdun.h"
#include "missione2espdun.h"
#include "missione3espdun.h"
#include "inventario.h"
#include "negozio.h"

// Nota: Assicurati di avere una funzione vuota o reale per la finale se la chiami
// void esploraFinale(Giocatore* g) { ... } 

void Menu(Giocatore* giocatore_ptr) {   
    puliscischermo();
    
    int tutte_completate = giocatore_ptr->missione_palude_completata &&
                           giocatore_ptr->missione_magione_completata &&
                           giocatore_ptr->missione_grotta_completata;
    
    printf("===== Menu Selezione Missione =====\n");
    
    int opzione_numero = 1;
    int mappa_opzioni[4] = {0};

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
    
    [cite_start]// SBLOCCO MISSIONE FINALE [cite: 82]
    if (tutte_completate) {
        printf("\n*** EVENTO SPECIALE ***\n");
        printf("%d. Castello del Signore Oscuro (MISSIONE FINALE)\n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 4;
        opzione_numero++;
    } else if (opzione_numero == 1) {
        printf("Non ci sono missioni disponibili.\n");
        getchar();
        return;
    }
    
    printf("\nSeleziona una missione [1-%d]: ", opzione_numero - 1);
    
    int scelta;
    scanf("%d", &scelta);
    while(getchar() != '\n');
    
    if(scelta < 1 || scelta >= opzione_numero) return;
    
    int missione_scelta = mappa_opzioni[scelta - 1];

    // STATO SESSIONE
    int stanza_corrente = 1; 
    int progressi_missione = 0; 

    while (true) {
        puliscischermo();
        printf("===== MISSIONE IN CORSO (Stanza %d/10) =====\n", stanza_corrente);
        printf("1. Esplora | 2. Negozio | 3. Inventario | 4. Torna al Villaggio\nScelta: ");
        
        int sceltammissione;
        scanf("%d", &sceltammissione);
        while(getchar() != '\n');

        if(sceltammissione == 1){    
            puliscischermo();
            
            // Limite Stanze
            if(missione_scelta != 4 && stanza_corrente > 10) {
                 printf("Dungeon finito. Torna al villaggio.\n");
                 getchar();
                 continue;
            }

            if(missione_scelta == 1){
                esplora1StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                if (giocatore_ptr->missione_palude_completata) {
                    printf("\n>>> MISSIONE PALUDE COMPLETATA! <<<\nINVIO per uscire...");
                    getchar();
                    return;
                }
            }
            else if(missione_scelta == 2){
                esplora2StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                if (giocatore_ptr->missione_magione_completata) {
                    printf("\n>>> MISSIONE MAGIONE COMPLETATA! <<<\nINVIO per uscire...");
                    getchar();
                    return;
                }
            }
            else if(missione_scelta == 3){
                esplora3StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                if (giocatore_ptr->missione_grotta_completata) {
                    printf("\n>>> MISSIONE GROTTA COMPLETATA! <<<\nINVIO per uscire...");
                    getchar();
                    return;
                }
            }
            else if(missione_scelta == 4){
                printf("Implementa qui la logica del Boss finale!\n");
                getchar();
                return;
            }

            if (giocatore_ptr->vita <= 0) return; // Game Over
        }
        else if(sceltammissione == 2) { negozio(giocatore_ptr); }
        else if(sceltammissione == 3) { Inventario(giocatore_ptr); getchar(); }
        else if(sceltammissione == 4) { 
            // Controllo fuga
            bool finita = (missione_scelta == 1 && giocatore_ptr->missione_palude_completata) ||
                          (missione_scelta == 2 && giocatore_ptr->missione_magione_completata) ||
                          (missione_scelta == 3 && giocatore_ptr->missione_grotta_completata);
            
            if (finita || giocatore_ptr->monete >= 50) {
                if(!finita) giocatore_ptr->monete -= 50;
                printf("Torni al villaggio.\n");
                getchar();
                return;
            } else {
                printf("Non hai 50 monete per fuggire!\n");
                getchar();
            }
        }
    }
}
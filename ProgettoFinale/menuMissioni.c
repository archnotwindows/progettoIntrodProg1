/**
 * @file menuMissioni.c
 * @brief Implementazione della selezione missioni e del loop di gioco principale.
 * * Questo file gestisce l'interfaccia utente per la scelta della missione
 * e il ciclo "while" che regola: l'avanzamento nelle stanze, l'accesso al negozio e all'inventario
 * durante una missione in corso
 */

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

/**
 * @brief Gestisce il menu di selezione delle missioni e il loop di esplorazione.
 * * La funzione verifica quali missioni sono state completate per mostrare dinamicamente
 * le opzioni. Una volta selezionata una missione, entra in un loop
 * che la gestisce fino al completamento.
 * * @param giocatore_ptr Puntatore alla struttura dati Giocatore.
 */
void Menu(Giocatore* giocatore_ptr) {   
    puliscischermo();
    
    /** * @brief Verifica lo stato di completamento.
     * Risulta true solo se tutte le missioni sono state completate.
     * Questo flag è necessario per sbloccare la missione finale.
     */
    int tutte_completate = giocatore_ptr->missione_palude_completata &&  
                           giocatore_ptr->missione_magione_completata &&
                           giocatore_ptr->missione_grotta_completata;
    
    printf("===== SELEZIONE MISSIONE =====\n");
    
    int opzione_numero = 1; // Contatore per numerare dinamicamente le opzioni del menu
    
    /**
     * @brief Array di mappatura opzioni -> ID missione.
     * Poiché le missioni spariscono dal menu una volta completate, l'opzione "1"
     * non corrisponde sempre alla missione 1. Questo array mappa la scelta dell'utente
     * (indice array) all'ID effettivo della missione (valore).
     * ID 1: Palude, 2: Magione, 3: Grotta, 4: Castello Finale.
     */
    int mappa_opzioni[4] = {0}; 

    /* --- Generazione dinamica del menu --- */

    /* Se la missione Palude non è completata, la aggiunge al menu */
    if (!giocatore_ptr->missione_palude_completata) { 
        printf("%d. Palude Putrescente \n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 1;
        opzione_numero++;
    }
    
    /* Se la missione Magione non è completata, la aggiunge al menu */
    if (!giocatore_ptr->missione_magione_completata) {
        printf("%d. Magione Infestata \n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 2;
        opzione_numero++;
    }
    
    /* Se la missione Grotta non è completata, la aggiunge al menu */
    if (!giocatore_ptr->missione_grotta_completata) {
        printf("%d. Grotta di Cristallo \n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 3;
        opzione_numero++;
    }
    
    /* Se tutte le missioni base sono completate, mostra la Missione Finale */
    if (tutte_completate) {      
        printf("\n*** MISSIONE FINALE ***\n");
        printf("%d. Castello del Signore Oscuro \n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 4;
        opzione_numero++;
    } 
    /* Gestione errore: nessuna missione disponibile  */
    else if (opzione_numero == 1) {
        printf("Non ci sono missioni disponibili (Errore).\n");
        getchar();
        return;
    }
    
    printf("\n0. Annulla e torna al Villaggio\n");
    printf("Seleziona una missione: ");
    
    /* --- Gestione Input Utente --- */
    int scelta;
    if(scanf("%d", &scelta) != 1) { while(getchar()!='\n'); return; } //  Controllo input non numerico 
    while(getchar() != '\n'); // Pulizia buffer 
    
    if(scelta == 0) return; //  Ritorna al menu precedente (Villaggio) 
    if(scelta < 1 || scelta >= opzione_numero) return; // Controllo input fuori range 
    
    /**
     * @brief Recupera l'ID reale della missione dalla mappa.
     */
    int missione_scelta = mappa_opzioni[scelta - 1]; 
    
    
    /** * @brief Gestione caso speciale: Missione Finale.
     * La Missione Finale ha una logica di combattimento dedicata e non usa il loop di esplorazione standard.
     */
    if (missione_scelta == 4) { 
        CombattimentoFinale(giocatore_ptr);
        return;
    }

    /* --- Inizio Loop Missione Standard --- */
    int stanza_corrente = 1; // Tiene traccia della stanza attuale nel dungeon  
    int progressi_missione = 0; // Variabile per tracciare eventi specifici della missione

    while (true) { 
        puliscischermo();
        printf("===== MISSIONE IN CORSO (Stanza %d/10) =====\n", stanza_corrente);
        printf("1. Esplora stanza\n2. Negozio \n3. Inventario\n4. Fuggi al Villaggio (Costo: 50 monete )\n");
        printf("Scelta: ");
        
        int sceltammissione;
        scanf("%d", &sceltammissione);
        while(getchar() != '\n');

        /* Opzione 1: Avanza nell'esplorazione */
        if(sceltammissione == 1){    
            puliscischermo();
            
            /* Controllo fine dungeon */
            if(stanza_corrente > 10) {
                 printf("Dungeon esplorato completamente. Torna al villaggio.\n");
                 getchar();
                 continue;
            }
  
            /* Chiama la funzione di esplorazione specifica per la missione scelta */
            if(missione_scelta == 1){
                esplora1StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                /* Verifica completamento missione Palude */
                if (giocatore_ptr->missione_palude_completata) {
                    printf("\n>>> COMPLIMENTI! MISSIONE PALUDE COMPLETATA! <<<\nINVIO per uscire...");
                    getchar();
                    return;
                }
            }
            else if(missione_scelta == 2){
                esplora2StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                /* Verifica completamento missione Magione */
                if (giocatore_ptr->missione_magione_completata) {
                    printf("\n>>> COMPLIMENTI! MISSIONE MAGIONE COMPLETATA! <<<\nINVIO per uscire...");
                    getchar();
                    return;
                }
            }
            else if(missione_scelta == 3){
                esplora3StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                /* Verifica completamento missione Grotta */
                if (giocatore_ptr->missione_grotta_completata) {
                    printf("\n>>> COMPLIMENTI! MISSIONE GROTTA COMPLETATA! <<<\nINVIO per uscire...");
                    getchar();
                    return;
                }
            }
          
            /** * @brief Controllo stato vitale.
             * Se la vita è <= 0, si esce dal menu
             */
            if (giocatore_ptr->vita <= 0) return; 
        }
        /* Opzione 2: Negozio */
        else if(sceltammissione == 2) { 
            negozio(giocatore_ptr); 
        } 
        /* Opzione 3: Gestione Inventario */
        else if(sceltammissione == 3) { 
            Inventario(giocatore_ptr); 
            printf("Premi INVIO per tornare al menu..."); 
            getchar(); 
        } 
        /* Opzione 4: Fuga dal dungeon */
        else if(sceltammissione == 4) { 
            /**
             * @brief Verifica se la missione attuale è già stata completata in precedenza.
             * Permette di capire se la fuga deve essere gratuita (missione già finita) o a pagamento.
             */
            bool finita = (missione_scelta == 1 && giocatore_ptr->missione_palude_completata) ||
                          (missione_scelta == 2 && giocatore_ptr->missione_magione_completata) ||
                          (missione_scelta == 3 && giocatore_ptr->missione_grotta_completata);
            
            /* Logica di pagamento per la fuga */
            if (finita || giocatore_ptr->monete >= 50) {
                if(!finita) {
                    giocatore_ptr->monete -= 50;
                    printf("Hai pagato 50 monete per fuggire!\n");
                } else {
                    printf("Missione gia' compiuta\n");
                }
                getchar();
                return; // Ritorna al menu principale 
            } else {
                printf("Non hai abbastanza monete (50) per fuggire!\n");
                getchar();
            }
        }
    }
}
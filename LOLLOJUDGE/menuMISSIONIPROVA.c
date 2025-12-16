#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Necessario per true/false
#include "menuMissioni.h"
#include "systemclear.h" // Assumo sia il tuo header per puliscischermo()
#include "missione1espdun.h"
#include "missione2espdun.h"
#include "missione3espdun.h"
#include "missionefinale.h" // Ipotetico header per la missione finale
#include "inventario.h"
#include "negozio.h"

void Menu(Giocatore* giocatore_ptr) {   
    puliscischermo();
    
    // Controllo se le 3 missioni principali sono state completate
    int tutte_completate = giocatore_ptr->missione_palude_completata &&
                           giocatore_ptr->missione_magione_completata &&
                           giocatore_ptr->missione_grotta_completata;
    
    printf("===== Menu Selezione Missione =====\n");
    
    int opzione_numero = 1;
    int mappa_opzioni[4] = {0}; // Dimensione aumentata a 4 per includere la finale

    // --- GENERAZIONE DINAMICA DEL MENU ---

    // Mostra le missioni solo se NON sono state completate [cite: 81]
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
    
    // Se tutte le missioni sono completate, SBLOCCA quella finale [cite: 82]
    if (tutte_completate) {
        printf("\n*** EVENTO SPECIALE SBLOCCATO ***\n");
        printf("%d. Castello del Signore Oscuro (MISSIONE FINALE)\n", opzione_numero);
        mappa_opzioni[opzione_numero - 1] = 4; // ID 4 assegnato alla missione finale
        opzione_numero++;
    } else if (opzione_numero == 1) {
        // Caso di sicurezza (non dovrebbe accadere se logica è corretta)
        printf("Non ci sono missioni disponibili.\n");
        getchar();
        return;
    }
    
    printf("\nSeleziona una missione [1-%d]: ", opzione_numero - 1);
    
    int scelta;
    scanf("%d", &scelta);
    while(getchar() != '\n'); // Pulisce buffer
    
    if(scelta < 1 || scelta >= opzione_numero){ 
        printf("Opzione non valida.\n");
        getchar();
        return;
    }
    
    int missione_scelta = mappa_opzioni[scelta - 1];

    // --- INIZIALIZZAZIONE STATO MISSIONE ---
    // Queste variabili tengono traccia del progresso SOLO per questa sessione.
    // Se torni al villaggio senza finire, si resetteranno alla prossima entrata.
    int stanza_corrente = 1; 
    int progressi_missione = 0; // Es: Generali uccisi, o flag per la chiave

    // --- CICLO INTERNO: MENU DI MISSIONE [cite: 85] ---
    while (true) {
        puliscischermo();
        
        printf("===== MISSIONE IN CORSO: ");  
        if (missione_scelta == 1) {
            printf("PALUDE PUTRESCENTE =====\n");
            printf("Obiettivo: Eliminare 3 Generali Orco.\n");
            printf("Avanzamento: Stanza %d/10 | Generali Sconfitti: %d/3\n", stanza_corrente, progressi_missione);
        } else if (missione_scelta == 2) {
            printf("MAGIONE INFESTATA =====\n");
            printf("Obiettivo: Recupera Chiave e sconfiggi Vampiro Superiore.\n");
            printf("Avanzamento: Stanza %d/10\n", stanza_corrente);
        } else if (missione_scelta == 3) {
            printf("GROTTA DI CRISTALLO =====\n");
            printf("Obiettivo: Recupera la Spada dell'Eroe.\n");
            printf("Avanzamento: Stanza %d/10\n", stanza_corrente);
        } else if (missione_scelta == 4) {
            printf("CASTELLO DEL SIGNORE OSCURO =====\n");
            printf("Obiettivo: Sconfiggi il Signore Oscuro.\n");
        }
        
        printf("\nMenu di Missione:\n");
        printf("1. Esplora stanza del Dungeon\n"); // [cite: 86]
        printf("2. Negozio\n"); // [cite: 87]
        printf("3. Inventario\n"); // [cite: 89]
        printf("4. Torna al Villaggio (Paga 50 Monete)\n"); // 
        printf("Seleziona un'opzione [1-4]: ");
        
        int sceltammissione;
        scanf("%d", &sceltammissione);
        while(getchar() != '\n');

        // --- 1. ESPLORA STANZA ---
        if(sceltammissione == 1){    
            puliscischermo();
            
            // Controllo limite stanze (massimo 10 per le missioni normali) [cite: 102]
            if(missione_scelta != 4 && stanza_corrente > 10) {
                 printf("Hai esplorato tutto il dungeon!\n");
                 printf("Devi tornare al villaggio (se non hai completato l'obiettivo, hai fallito).\n");
                 getchar();
                 continue;
            }

            if(missione_scelta == 1){
                // Passiamo gli indirizzi (&) per aggiornare stanza e progressi
                esplora1StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                
                if (giocatore_ptr->missione_palude_completata) {
                    printf("\n>>> MISSIONE COMPLETATA! <<<\n");
                    printf("Premi INVIO per tornare trionfante al villaggio...");
                    getchar();
                    return; // Torna al menu principale
                }
            }
            else if(missione_scelta == 2){
                esplora2StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                
                if (giocatore_ptr->missione_magione_completata) {
                    printf("\n>>> MISSIONE COMPLETATA! <<<\n");
                    getchar();
                    return;
                }
            }
            else if(missione_scelta == 3){
                esplora3StanzaDungeon(giocatore_ptr, &stanza_corrente, &progressi_missione);
                
                if (giocatore_ptr->missione_grotta_completata) {
                    printf("\n>>> MISSIONE COMPLETATA! <<<\n");
                    getchar();
                    return;
                }
            }
            else if(missione_scelta == 4){
                // Missione Finale (Logica diversa, spesso combattimento diretto o poche fasi)
                // esploraFinale(giocatore_ptr);
                // if (giocatore_ptr->vittoria_finale) ...
            }

            // Controllo Game Over globale dopo ogni esplorazione
            if (giocatore_ptr->vita <= 0) {
                // Il messaggio GAME OVER è gestito nella funzione di esplorazione solitamente,
                // ma qui assicuriamo l'uscita dal ciclo.
                return;
            }
        }
        // --- 2. NEGOZIO ---
        else if(sceltammissione == 2){ 
            puliscischermo();
            negozio(giocatore_ptr);
        }
        // --- 3. INVENTARIO ---
        else if(sceltammissione == 3){ 
            puliscischermo();
            Inventario(giocatore_ptr);
            printf("Premi INVIO per continuare...");
            getchar();
        }
        // --- 4. TORNA AL VILLAGGIO ---
        else if(sceltammissione == 4){ 
            puliscischermo();
            
            // Verifica se l'obiettivo è stato raggiunto (gratis) o no (paga 50) 
            bool missione_finita = false;
            if (missione_scelta == 1 && giocatore_ptr->missione_palude_completata) missione_finita = true;
            else if (missione_scelta == 2 && giocatore_ptr->missione_magione_completata) missione_finita = true;
            else if (missione_scelta == 3 && giocatore_ptr->missione_grotta_completata) missione_finita = true;

            if (missione_finita) {
                printf("Torni al villaggio vittorioso. (Nessun costo)\n");
                getchar();
                return;
            } else {
                if(giocatore_ptr->monete >= 50){
                    giocatore_ptr->monete -= 50;
                    printf("Fuggi dal dungeon pagando 50 monete di penalità.\n");
                    printf("Premi INVIO per continuare...");
                    getchar();
                    return;
                } else {
                    printf("Non hai abbastanza monete (50) per fuggire! Devi continuare a combattere.\n");
                    printf("Premi INVIO per continuare...");
                    getchar();
                }
            }
        }
        else{
            printf("Opzione non valida.\n");
            getchar();
        }
    }
}
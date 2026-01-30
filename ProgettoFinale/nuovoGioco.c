/**
 * @file nuovoGioco.c
 * @brief Implementazione del menu principale e gestione della sessione.
 * * Questo file funge gestisce:
 * 1. Il menu iniziale .
 * 2. L'attivazione della modalità trucchi .
 * 3. L'inizializzazione di una nuova partita o il caricamento di una esistente.
 */

#define _POSIX_C_SOURCE 200809L // Macro per garantire compatibilità POSIX  
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
 * * Sostituisce la classica `scanf` per evitare problemi
 * * @return L'intero letto o "-1" in caso di errore/input non valido.
 */
static int leggiIntero() {
    char buffer[100];
    /* fgets legge tutta la riga, inclusi spazi, prevenendo residui nel buffer */
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; /* Rimuove il newline finale */
        return atoi(buffer); /* Converte stringa in intero */
    }
    return -1;
}

/**
 * @brief Stampa l'interfaccia grafica del menu principale.
 * @param trucchiAttivi Flag booleano: true se i trucchi sono stati attivati.
 */
void stampaMenu(bool trucchiAttivi){
    puliscischermo();
    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    if ( trucchiAttivi ){
        printf("|       Il Dungeon Oscuro   (CHEAT MODE)              |\n");
    } else {
        printf("|                  Il Dungeon Oscuro                  |\n");
        printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    }
    printf("| 1) Nuova partita                                    |\n");
    printf("| 2) Carica salvataggio                               |\n");  
    printf("| 3) Esci                                             |\n");
    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
}

/**
 * @brief Funzione principale di gestione del flusso di gioco.
 * * Contiene il loop principale che permette di avviare il gioco o gestire i file.
 * * Gestisce se l'utente inserisce un input specifico (definito in triggherTrucchi),
 * attiva funzionalità nascoste.
 */
void nuovoGioco(){
    char action[100];       // Buffer per l'input grezzo dell'utente 
    bool trucchiAttivi = false; 
    bool uscita = false;
    Giocatore g;            // Istanza temporanea del giocatore 

    while ( !uscita ){
        stampaMenu(trucchiAttivi);
        printf("Scegli un'opzione: ");    

        /* Lettura input menu principale */
        if (fgets(action, sizeof(action), stdin) == NULL) continue; 
        
        /**
         * @brief Controllo attivazione Trucchi.
         * Controlla se la sequenza di caratteri corrisponde alla sequenza segreta.
         * Se sì, ricarica il loop mostrando il menu "CHEAT MODE".
         */
        if (triggherTrucchi(action[0]) == true) {
            trucchiAttivi = true;
            printf("\n!!! TRUCCHI SBLOCCATI !!!\nPremi Invio...");
            getchar();
            continue; /* Ricarica il menu per mostrare il titolo aggiornato */
        }

        int intAction = atoi(action);
            
        /* --- Opzione 1: NUOVA PARTITA --- */
        if ( intAction == 1 ) {
            initGiocatore(&g); /* Inizializza struct con valori base */
            
            /** * @brief Bonus Cheat Mode.
             * Se i trucchi sono attivi, il giocatore inizia con valori aumentati.
             */
            if(trucchiAttivi) {
                g.monete = 1000;
                g.attacco = 10;
            }

            printf("Creazione nuova partita in corso...\n");
            printf("Premi Invio per entrare nel Villaggio...");
            getchar();
            
            /* Passa il controllo al menu del villaggio */
            menuVillaggio(&g);
        }

        /* --- Opzione 2: CARICA / GESTISCI SALVATAGGI --- */
        else if ( intAction == 2 ){
            /* Mostra la lista dei file disponibili */
            int elenco = listaSalvataggi();
            
            /* Se non ci sono file, torna al menu */
            if (elenco == 0) {
                printf("Premi Invio...");
                getchar();
                continue;
            }

            printf("Scegli un salvataggio da caricare [1-%d] (0 per annullare): ", elenco);
            int nSalvataggio = leggiIntero();

            /* Se la selezione è valida, apre il sottomenu del file */
            if (nSalvataggio > 0 && nSalvataggio <= elenco){
                int azione;
                printf("\n1) Carica e Gioca\n2) Elimina\n");
                
                /* Opzione extra visibile solo con i trucchi */
                if (trucchiAttivi) {
                    printf("3) MODIFICA (TRUCCHI)\n4) Annulla\n");
                } else {
                    printf("3) Annulla\n");
                }
            
                printf("Scegli: ");
                azione = leggiIntero();
                                
                /* Sottomenu 1: Carica */
                if ( azione == 1 ){
                    if (caricaDatiSalvataggio(nSalvataggio, &g)) {
                        printf("\nSalvataggio caricato con successo!\n");
                        printf("Premi Invio per entrare nel Villaggio...");
                        getchar();
                        menuVillaggio(&g); // Entra nel gioco con i dati caricati 
                    } else {
                        printf("Errore nel caricamento del file.\n");
                        printf("Premi Invio per continuare...");
                        getchar();
                    }
                } 
                /* Sottomenu 2: Elimina */
                else if ( azione == 2 ){
                    printf("Sicuro? (1=Si, 2=No): ");
                    if ( leggiIntero() == 1 ) eliminaSalvataggio(nSalvataggio);
                }
                /* Sottomenu 3: Modifica (Solo con Cheat Mode) */
                else if ( trucchiAttivi && azione == 3 ) {
                    /** @brief Permette di modificare manualmente i valori del file di salvataggio. */
                    modificaSalvataggio(nSalvataggio);
                }
            }    
        }
        /* --- Opzione 3: ESCI --- */
        else if ( intAction == 3 ) uscita = true;
    }
}
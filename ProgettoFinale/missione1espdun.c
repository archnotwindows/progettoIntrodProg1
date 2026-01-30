/**
 * @file missione1espdun.c
 * @brief Implementazione della missione "Palude Putrescente".
 * * Questo file contiene la logica specifica per la prima missione.
 * L'obiettivo è sconfiggere 3 Generali Orchi entro 10 stanze.
 * Il sistema utilizza la TabellaPalude definita in 
 * tabellemissioni.h per determinare cosa accade in base al lancio del dado.
 */

#include <stdio.h>
#include <stdlib.h>
#include "missione1espdun.h"
#include "tabellemissioni.h" 

/**
 * @brief Funzione per simulare il lancio di un dado a 6 facce.
 * @return Un intero casuale tra 1 e 6.
 */
static int lanciaDado() {
    return rand() % 6 + 1;
}

/**
 * @brief Gestisce l'esplorazione di una singola stanza nella Palude
 * * La funzione determina l'evento della stanza basandosi
 * sul caso o sulla necessità di completare l'obiettivo. Gestisce il combattimento,
 * il calcolo dei danni, le ricompense e l'aggiornamento degli obiettivi.
 * * @param giocatore_ptr Puntatore alla struttura dati del giocatore.
 * @param stanza_corrente Puntatore al contatore della stanza attuale (1-10).
 * @param generali_uccisi Puntatore al contatore degli obiettivi completati per questa missione.
 */
void esplora1StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* generali_uccisi) {
    const int OBIETTIVO_GENERALI = 3; // Numero di Generali da sconfiggere per vincere. 
    const int MAX_STANZE = 10;        // Lunghezza massima del dungeon. 
    
    /* Calcolo delle probabilità residue per garantire il completamento */
    int stanze_rimanenti = MAX_STANZE - *stanza_corrente + 1;
    int generali_mancanti = OBIETTIVO_GENERALI - *generali_uccisi;
    int indice_tabella;

    printf("\n--- PALUDE PUTRESCENTE: Stanza %d ---\n", *stanza_corrente);
    printf("Obiettivo: %d/3 Generali Orchi sconfitti\n", *generali_uccisi);

    /** * @brief Logica per forzare l'incontro con il Generale Orco.
     * Se il numero di Generali mancanti è uguale al numero di stanze rimaste,
     * il gioco forza l'uscita del Generale (indice 5) invece di tirare il dado.
     * Questo impedisce al giocatore di fallire la missione solo per sfortuna coi dadi.
     */
    if (generali_mancanti > 0 && generali_mancanti >= stanze_rimanenti) {
        indice_tabella = 5; 
    } else {
        int tiro = lanciaDado();
        printf("Esplori la palude... (Dado: %d)\n", tiro);
        indice_tabella = tiro - 1; /* Converte 1-6 in indice array 0-5 */
    }

    /* Recupera i dati dell'evento dalla tabella globale */
    struct RigaDungeon stanza = TabellaPalude[indice_tabella];

    /* --- GESTIONE TRAPPOLE --- */
    if (stanza.tipo == TIPO_TRAPPOLA) {
        printf("TRAPPOLA! Ti imbatti in: %s\n", stanza.nome);
        int danno = stanza.danno;

        /** * @brief Gestione danni variabili.
         * il danno viene calcolato tirando un dado al momento.
         */
        if (danno == -1 || indice_tabella == 4) { 
            danno = lanciaDado();
            printf("L'acquitrino ti risucchia! Subisci %d danni.\n", danno);
        }

        /* Riduzione danno tramite armatura */
        if (giocatore_ptr->ha_armatura && danno > 0) {
            danno--; 
            printf("(Armatura riduce il danno di 1)\n");
        }

        /* Applicazione danno */
        if (danno < 0) danno = 0;
        giocatore_ptr->vita -= danno;
        printf("Vita residua: %d\n", giocatore_ptr->vita);
    }
    /* --- GESTIONE COMBATTIMENTI --- */
    else if (stanza.tipo == TIPO_COMBATTIMENTO) {
        printf("COMBATTIMENTO! Nemico: %s\n", stanza.nome);
        
        int nemico_vivo = 1;
        int colpo_fatale = stanza.colpo_fatale; // Valore da superare col dado per colpire 

        /** * @brief Bonus Oggetto Speciale: Spada dell'Eroe.
         * Se il giocatore possiede l'oggetto speciale e affronta il Generale,
         * la difficoltà del combattimento si abbassa (il colpo fatale scende a 5).
         */
        if (indice_tabella == 5 && giocatore_ptr->ha_spada_eroe) {
            colpo_fatale = 5;
            printf("La tua Spada dell'Eroe funziona! Il Generale sembra piu' debole (Colpo Fatale 5).\n");
        }

        /* Loop di combattimento */
        while (nemico_vivo && giocatore_ptr->vita > 0) {
            printf("\n[TU: %d HP] vs [%s] (Tira > %d per colpire)\n", giocatore_ptr->vita, stanza.nome, colpo_fatale);
            printf("Premi INVIO per attaccare...");
            while(getchar() != '\n'); 

            int dado_attacco = lanciaDado();
            int attacco_totale = dado_attacco + giocatore_ptr->attacco; 

            printf("Hai fatto %d (+%d bonus) = %d. ", dado_attacco, giocatore_ptr->attacco, attacco_totale);

            /* Verifica esito attacco */
            if (attacco_totale > colpo_fatale) {
                printf("COLPITO! Nemico sconfitto!\n");
                nemico_vivo = 0;
                
                /* Assegnazione ricompensa */
                printf("Ottieni %d monete.\n", stanza.monete);
                giocatore_ptr->monete += stanza.monete;

                /* Aggiornamento obiettivo missione se il nemico era un Generale */
                if (indice_tabella == 5) {
                    (*generali_uccisi)++;
                    printf(">>> OBIETTIVO AGGIORNATO: Generali uccisi %d/3 <<<\n", *generali_uccisi);
                }
            } else {
                printf("MANCATO!\n");
                
                /* Calcolo danno nemico con riduzione armatura */
                int danno_nemico = stanza.danno;
                if (giocatore_ptr->ha_armatura && danno_nemico > 0) {
                    danno_nemico--;
                }
                
                printf("Il nemico contrattacca! Subisci %d danni.\n", danno_nemico);
                giocatore_ptr->vita -= danno_nemico;
            }
        }
    }
    
    /* Avanzamento stanza */
    (*stanza_corrente)++; 

    /** * @brief Verifica condizione di vittoria.
     * Se il giocatore ha ucciso 3 generali, imposta il flag globale di completamento missione.
     */
    if (*generali_uccisi >= OBIETTIVO_GENERALI) {
        giocatore_ptr->missione_palude_completata = true;
    }

    printf("\nPremi INVIO per continuare...");
    while(getchar() != '\n');
}
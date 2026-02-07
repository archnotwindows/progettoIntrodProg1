#include <stdio.h>
#include <stdlib.h>
#include "missione2espdun.h"
#include "tabellemissioni.h"

// Funzione che lancia un dado a 6 facce
static int lanciaDado() { return rand() % 6 + 1; }

/**
 // DOCUMENTAZIONE DOXYGEN
 * * @param giocatore_ptr: Puntatore alla struttura dati del giocatore (vita, attacco, ecc.)
 * @param stanza_corrente: Puntatore al contatore della stanza attuale (1-10)
 * @param progressi: Puntatore a un intero bitmask che traccia gli obiettivi:

 */


void esplora2StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* progressi) {
    const int MAX_STANZE = 10;
    
    // --- GESTIONE STATO MISSIONE  ---
    //  & Confronto bit a bit tra progressi e 00000001  >> se ottengo 1 allora il giocatore ha la chiave
    int ha_chiave = (*progressi & 1);     
    //  & Confronto bit a bit tra progressi e 00000010  >> se ottengo 2 allora il vampiro è morto
    int vampiro_morto = (*progressi & 2); 

  
    printf("\n--- MAGIONE INFESTATA: STANZA %d/%d ---\n", *stanza_corrente, MAX_STANZE);
    printf("Stato Missione: Chiave [%s] - Vampiro Sconfitto [%s]\n", 
           ha_chiave ? "PRESA" : "MANCANTE", 
           vampiro_morto ? "SI" : "NO");


    
    int stanze_rimanenti = MAX_STANZE - *stanza_corrente + 1;
    int obiettivi_mancanti = (!ha_chiave) + (!vampiro_morto ? 1 : 0);
    int indice_tabella;


    // --- LOGICA DI FORZATURA STANZE ---
    // SE mancano obiettivi E le stanze rimaste sono poche
    // (forzo l'incontro con l'obiettivo)
    if (obiettivi_mancanti > 0 && obiettivi_mancanti >= stanze_rimanenti) {
        printf(">>> Presenza oscura rilevata! (Incontro Forzato)\n");
        // Se manca la chiave, forza l'incontro con il nemico che ha la chiave
        if (!ha_chiave) indice_tabella = 5; 
        // Altrimenti forza l'incontro con il Vampiro 
        else indice_tabella = 4;            

    } else {  // Altrimenti, esplorazione casuale normale
        int tiro = lanciaDado();
        indice_tabella = tiro - 1; // Adatta il dado all'indice array
    }

    // Carica i dati della stanza dalla tabella 
    struct RigaDungeon stanza = TabellaMagione[indice_tabella];
    printf("Ti imbatti in: %s\n", stanza.nome);

    // --- CASO 1: STANZA TRAPPOLA ---
    if (stanza.tipo == TIPO_TRAPPOLA) {
        int danno = stanza.danno;
        // L'armatura riduce il danno delle trappole di 1
        if (giocatore_ptr->ha_armatura && danno > 0) danno--;
        printf("Trappola scatta! Subisci %d danni.\n", danno);
        giocatore_ptr->vita -= danno;
    }

    // --- CASO 2: STANZA COMBATTIMENTO ---
    else if (stanza.tipo == TIPO_COMBATTIMENTO) {
        int nemico_vivo = 1;
        
        // Ciclo di combattimento: continua finché uno dei due arriva a  0 vita
        while (nemico_vivo && giocatore_ptr->vita > 0) {
            printf("\nTU: %d HP | NEMICO (%d Fatale)\nINVIO per attaccare...", giocatore_ptr->vita, stanza.colpo_fatale);
            while(getchar() != '\n'); 

            // Calcolo attacco giocatore
            int attacco = lanciaDado() + giocatore_ptr->attacco;
            
            // Se l'attacco supera la soglia di difesa del nemico (colpo_fatale)
            if (attacco > stanza.colpo_fatale) {
                printf("COLPITO! Vittoria!\n");
                nemico_vivo = 0; // Esci dal ciclo while
                giocatore_ptr->monete += stanza.monete; // Assegna ricompensa

                // --- VERIFICA OBIETTIVI DI MISSIONE ---
                if (stanza.is_obiettivo == 1) { 
                    if (!vampiro_morto) {
                        *progressi |= 2; // Accende il 2° bit
                        printf(">>> Vampiro Superiore Sconfitto! <<<\n");
                    }
                } 
                else if (stanza.is_obiettivo == 2) { 
                    if (!ha_chiave) {
                        *progressi |= 1; // Accende il 1° bit 
                        giocatore_ptr->ha_chiave = true; // Aggiorna la struct giocatore
                        printf(">>> Chiave del Castello Recuperata! <<<\n");
                    }
                }
            } else {
                // Se manchi il nemico, lui ti colpisce
                int danno = stanza.danno;
                // L'armatura riduce il danno subito
                if (giocatore_ptr->ha_armatura && danno > 0) danno--;
                
                printf("MANCATO! Subisci %d danni.\n", danno);
                giocatore_ptr->vita -= danno;
            }
        }
    }

    // Avanzamento alla prossima stanza
    (*stanza_corrente)++;
    
    // --- CONTROLLO COMPLETAMENTO MISSIONE ---
    // Se i bit sono entrambi a 1 (binario 11 = decimale 3), la missione è finita
    if ((*progressi & 3) == 3) {
        giocatore_ptr->missione_magione_completata = true;
    }

    printf("Premi INVIO...");
    while(getchar() != '\n');
}
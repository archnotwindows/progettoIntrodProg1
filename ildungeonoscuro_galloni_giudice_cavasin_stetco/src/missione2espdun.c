/**
* @file missione2espdun.c
* @brief Implementazione della missione "Magione Infestata".
* * Questo file gestisce la logica della seconda missione.
* Si utilizzano
* dei flag binari (bitwise) per tracciare due obiettivi distinti:
* - trovare la Chiave 
* - uccidere il Vampiro.
*/

#include <stdio.h>
#include <stdlib.h>
#include "missione2espdun.h"
#include "tabellemissioni.h"

/**
* @brief Genera un numero casuale da 1 a 6.
* @return Intero casuale [1, 6].
*/
static int lanciaDado() { return rand() % 6 + 1; }

/**
* @brief Gestisce l'esplorazione di una stanza nella Magione.
* * Utilizza un intero (`progressi`) come maschera di bit per tracciare lo stato:
* - Bit 0 (valore 1): Chiave trovata.
* - Bit 1 (valore 2): Vampiro sconfitto.
* * La funzione garantisce che entrambi gli obiettivi vengano incontrati entro le 10 stanze.
* * @param giocatore_ptr Puntatore ai dati del giocatore.
* @param stanza_corrente Puntatore al numero della stanza attuale.
* @param progressi Puntatore alla variabile bitmask che conserva lo stato degli obiettivi.
*/
void esplora2StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* progressi) {
    const int MAX_STANZE = 10;
    
    /** * @brief Decodifica della bitmask.
    * Utilizza l'operatore AND (&) per verificare se i flag sono attivi.
    */
    int ha_chiave = (*progressi & 1);     
    int vampiro_morto = (*progressi & 2); 
  
    printf("\n--- MAGIONE INFESTATA: STANZA %d/%d ---\n", *stanza_corrente, MAX_STANZE);
    printf("Obiettivi: Chiave [%s] - Vampiro [%s]\n", 
           ha_chiave ? "TROVATA" : "NON TROVATA", 
           vampiro_morto ? "SCONFITTO" : "VIVO");

    /* Calcolo delle necessità per la logica di forzatura*/
    int stanze_rimanenti = MAX_STANZE - *stanza_corrente + 1;
    /* Calcola quanti obiettivi mancano (0, 1 o 2) */
    int obiettivi_mancanti = (!ha_chiave) + (!vampiro_morto ? 1 : 0);
    int indice_tabella;

    /** * @brief Logica di forzatura obiettivi.
    * Se il numero di stanze rimanenti è uguale o inferiore agli obiettivi mancanti,
    * il gioco smette di tirare i dadi e forza l'uscita degli eventi necessari.
    * Priorità: Prima la Chiave (indice 5), poi il Vampiro (indice 4).
    */
    if (obiettivi_mancanti > 0 && obiettivi_mancanti >= stanze_rimanenti) {
        if (!ha_chiave) indice_tabella = 5; /* Forza evento Chiave */
        else indice_tabella = 4;           /* Forza evento Vampiro */
    } else {
        int tiro = lanciaDado();
        indice_tabella = tiro - 1; /* Normale estrazione casuale */
    }

    struct RigaDungeon stanza = TabellaMagione[indice_tabella];
    printf("Ti imbatti in: %s\n", stanza.nome);

    /* --- GESTIONE TRAPPOLE --- */
    if (stanza.tipo == TIPO_TRAPPOLA) {
        int danno = stanza.danno;
        
        /* Riduzione danno armatura */
        if (giocatore_ptr->ha_armatura && danno > 0) danno--;
        
        printf("La trappola scatta! Subisci %d danni.\n", danno);
        giocatore_ptr->vita -= danno;
    }
    /* --- GESTIONE COMBATTIMENTO --- */
    else if (stanza.tipo == TIPO_COMBATTIMENTO) {
        int nemico_vivo = 1;
        
        while (nemico_vivo && giocatore_ptr->vita > 0) {
            printf("\nTU: %d HP | NEMICO (Difesa %d)\nINVIO per attaccare...", giocatore_ptr->vita, stanza.colpo_fatale);
            while(getchar() != '\n'); 

            int attacco = lanciaDado() + giocatore_ptr->attacco;
            
            /* Verifica colpo */
            if (attacco > stanza.colpo_fatale) {
                printf("COLPITO! Vittoria!\n");
                nemico_vivo = 0; 
                giocatore_ptr->monete += stanza.monete; 

                /** * @brief Aggiornamento obiettivi (Bitwise OR).
                * Se il nemico sconfitto è un obiettivo, attiviamo il bit corrispondente.
                * is_obiettivo == 1 -> Vampiro (Bit 2)
                * is_obiettivo == 2 -> Chiave (Bit 1)
                */
                if (stanza.is_obiettivo == 1 && !vampiro_morto) { 
                    *progressi |= 2; /* Accende il 2° bit */
                    printf(">>> Vampiro Superiore Sconfitto! <<<\n");
                } 
                else if (stanza.is_obiettivo == 2 && !ha_chiave) { 
                    *progressi |= 1; /* Accende il 1° bit */
                    giocatore_ptr->ha_chiave = true; /* Aggiorna anche la struct del giocatore */
                    printf(">>> Hai trovato la Chiave del Castello! <<<\n");
                }
            } else {
                /* Calcolo danno subito */
                int danno = stanza.danno;
                if (giocatore_ptr->ha_armatura && danno > 0) danno--;
                printf("MANCATO! Subisci %d danni.\n", danno);
                giocatore_ptr->vita -= danno;
            }
        }
    }

    (*stanza_corrente)++;
    
    /** * @brief Verifica completamento missione.
    * Controlla se entrambi i bit (1 e 2) sono attivi.
    * 1 (01 binario) + 2 (10 binario) = 3 (11 binario).
    */
    if ((*progressi & 3) == 3) {
        giocatore_ptr->missione_magione_completata = true;
    }

    printf("Premi INVIO...");
    while(getchar() != '\n');
}
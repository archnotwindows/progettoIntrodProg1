/**
 * @file giocatore.h
 * @brief Definizione della struttura Giocatore e funzioni di inizializzazione.
 */

#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <stdbool.h>

/**
 * @struct Giocatore
 * @brief Rappresenta lo stato del personaggio giocante.
 * * Contiene le statistiche vitali, l'inventario e i progressi delle missioni.
 */
typedef struct {
    int vita;             /**< Punti vita attuali del giocatore (Max 20). */
    int monete;           /**< Quantità di monete possedute. */
    int attacco;          /**< Valore di attacco base. */
    
    // Equipaggiamento
    bool ha_spada;        /**< true se possiede la Spada di Ferro (+1 Att). */
    bool ha_armatura;     /**< true se possiede l'Armatura (-1 Danno subito). */
    bool ha_spada_eroe;   /**< true se possiede la Spada Leggendaria (+2 Att). */
    bool ha_chiave;       /**< true se ha trovato la Chiave del Castello. */
    
    // Progressi
    bool missione_palude_completata;  /**< Flag completamento missione Palude. */
    bool missione_magione_completata; /**< Flag completamento missione Magione. */
    bool missione_grotta_completata;  /**< Flag completamento missione Grotta. */
    
} Giocatore;

/**
 * @brief Inizializza un nuovo giocatore con valori di default.
 * * Imposta HP a 20, monete a 0, inventario vuoto e nessuna missione completata.
 * @param g Puntatore alla struttura Giocatore da inizializzare.
 */
static inline void initGiocatore(Giocatore* g) {
    g->vita = 20;
    g->monete = 0;
    g->attacco = 0;
    g->ha_spada = false;
    g->ha_armatura = false;
    g->ha_spada_eroe = false;
    g->ha_chiave = false;
    g->missione_palude_completata = false;
    g->missione_magione_completata = false;
    g->missione_grotta_completata = false;
}

#endif
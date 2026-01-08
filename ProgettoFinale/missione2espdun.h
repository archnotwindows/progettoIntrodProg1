/**
 * @file missione2espdun.h
 * @brief Header per la missione Magione.
 */
#ifndef MISSIONE2ESPDUN_H
#define MISSIONE2ESPDUN_H

#include "giocatore.h"

/**
 * @brief Logica di esplorazione per la Magione Infestata.
 * @param giocatore_ptr Puntatore al giocatore.
 * @param stanza_corrente Puntatore all'indice della stanza.
 * @param progressi Bitmask (bit 1: Chiave trovata, bit 2: Vampiro ucciso).
 */
void esplora2StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* progressi);

#endif
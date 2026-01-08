/**
 * @file missione3espdun.h
 * @brief Header per la missione Grotta.
 */
#ifndef MISSIONE3ESPDUN_H
#define MISSIONE3ESPDUN_H

#include "giocatore.h"

/**
 * @brief Logica di esplorazione per la Grotta di Cristallo.
 * @param giocatore_ptr Puntatore al giocatore.
 * @param stanza_corrente Puntatore all'indice della stanza.
 * @param progressi Puntatore flag (1 = Drago sconfitto).
 */
void esplora3StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* progressi);

#endif
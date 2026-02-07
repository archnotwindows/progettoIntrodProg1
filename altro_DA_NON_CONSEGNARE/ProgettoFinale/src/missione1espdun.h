/**
* @file missione1espdun.h
* @brief Header per la missione Palude.
*/
#ifndef MISSIONE1ESPDUN_H
#define MISSIONE1ESPDUN_H

#include "giocatore.h"

/**
* @brief Logica di esplorazione per la Palude Putrescente.
* @param giocatore_ptr Puntatore al giocatore.
* @param stanza_corrente Puntatore all'indice della stanza attuale.
* @param generali_uccisi Puntatore al contatore dei boss sconfitti.
*/
void esplora1StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* generali_uccisi);

#endif
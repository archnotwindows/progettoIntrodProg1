/**
 * @file menuvillaggio.h
 * @brief Header per la gestione dell'hub centrale (Villaggio).
 */
#ifndef MENUVILLAGGIO_H
#define MENUVILLAGGIO_H

#include "giocatore.h"

/**
 * @brief Gestisce il menu del villaggio.
 * * Permette di accedere alle missioni, riposare, vedere l'inventario o salvare.
 * @param giocatore_ptr Puntatore al giocatore.
 */
void menuVillaggio(Giocatore* giocatore_ptr);

#endif
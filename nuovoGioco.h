/**
 * @file nuovoGioco.h
 * @brief Header per la gestione del menu principale e avvio gioco.
 */
#ifndef NUOVOGIOCO_H
#define NUOVOGIOCO_H

#include <stdbool.h>

/**
 * @brief Gestisce il loop del menu principale (Nuova Partita, Carica, Esci).
 */
void nuovoGioco();

/**
 * @brief Stampa a video il menu principale.
 * @param trucchiAttivi Flag che indica se la modalità cheat è attiva.
 */
void stampaMenu(bool trucchiAttivi);

#endif
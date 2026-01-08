/**
 * @file salvataggi.h
 * @brief Header per la gestione del salvataggio e caricamento.
 */
#ifndef SALVATAGGI_H
#define SALVATAGGI_H
#include <stdbool.h>
#include "giocatore.h"

/**
 * @brief Crea un nuovo salvataggio su file.
 * @param g Puntatore allo stato del giocatore da salvare.
 */
void nuovoSalvataggio(Giocatore* g);

/**
 * @brief Restituisce il numero di salvataggi disponibili e li stampa a video.
 * @return Numero di file trovati.
 */
int listaSalvataggi();

/**
 * @brief Carica i dati da un file di salvataggio.
 * @param n Indice del salvataggio scelto.
 * @param g Puntatore alla struttura Giocatore da popolare.
 * @return 1 se successo, 0 se errore.
 */
int caricaDatiSalvataggio(int n, Giocatore* g);

/**
 * @brief Elimina un file di salvataggio.
 * @param n Indice del salvataggio da eliminare.
 */
void eliminaSalvataggio(int n);

/**
 * @brief Modifica un salvataggio (Menu Trucchi).
 * @param n Indice del salvataggio da modificare.
 */
void modificaSalvataggio(int n); 

/**
 * @brief Verifica l'inserimento del Konami Code.
 * @param tasto Carattere appena digitato.
 * @return true se il codice è completo, false altrimenti.
 */
bool triggherTrucchi(char tasto);

#endif
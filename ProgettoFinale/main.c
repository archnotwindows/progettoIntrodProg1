/**
 * @file main.c
 * @brief Inizio del programma "Il Dungeon Oscuro".
 * @author Lorenzo Giudice, Elia Cavasin, Lorenzo Galloni, Denis Stetco 
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nuovoGioco.h"
#include "systemclear.h"

/**
 * @mainpage Documentazione del progetto "Il Dungeon Oscuro"
 * @section intro_sec Introduzione
 * Benvenuto nella documentazione del gioco "Il Dungeon Oscuro".
 * Questo progetto è stato sviluppato come parte del corso di Introduzione alla Programmazione 1.
*/

/**
 * @brief Funzione principale.
 * * Inizializza il generatore di numeri casuali e avvia il menu.
 */
int main(void) {
    srand(time(NULL)); 
    puliscischermo();
    
    nuovoGioco();
    
    return 0;
}
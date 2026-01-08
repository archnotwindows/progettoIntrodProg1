/**
 * @file main.c
 * @brief Punto di ingresso del programma "Il Dungeon Oscuro".
 * @author Utente
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
 * Questo progetto è un'avventura testuale scritta in C.
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
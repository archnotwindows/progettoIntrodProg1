#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "giocatore.h"
#include "menuiniziale.h"

int main(){
    // Inizializza il generatore di numeri casuali
    srand(time(NULL));
    
    // Avvio del gioco
    menuIniziale();

    return 0;
}
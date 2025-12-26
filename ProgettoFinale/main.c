#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nuovoGioco.h"
#include "systemclear.h"

int main(void) {
    srand(time(NULL)); // Inizializzazione seed random globale
    puliscischermo();
    
    // Avvia il ciclo del Menu Iniziale
    nuovoGioco();
    
    return 0;
}
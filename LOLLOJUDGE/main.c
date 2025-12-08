#include "giocatore.h"      
#include "menuMissioni.h"
// opzionale: #include <time.h> e <stdlib.h> se sposti srand() qui

int main(){
    // Inizializzazione giocatore
    Giocatore g = {20, 60, 0, false};

    // Avvio del gioco
    Menu(&g);

    return 0;
}
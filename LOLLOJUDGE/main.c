#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "giocatore.h"
#include "menuvillaggio.h"

int main() {
    srand(time(NULL)); 

    
    Giocatore eroe = {0};
    eroe.vita = 20;
    eroe.monete = 0;
    eroe.attacco = 0; 

    
    menuVillaggio(&eroe);

    printf("Grazie per aver giocato!\n");
    return 0;
}
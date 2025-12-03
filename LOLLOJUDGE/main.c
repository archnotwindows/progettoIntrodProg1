#include <stdio.h>
#include <stdlib.h>
#include "giocatore.h"      
#include "menuMissioni.h"

int main(){


    Giocatore g = {20, 60, 0, false};


    Menu(&g);

    return 0;
}
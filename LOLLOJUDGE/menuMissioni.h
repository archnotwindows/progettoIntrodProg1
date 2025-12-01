#include <stdio.h>

#include <stdlib.h>

#include "systemclear.h"

#include "missione1espdun.h"

#include <time.h>




void Menu(Giocatore* giocatore_ptr){



    int scelta;

    printf("Menù scelta missioni \n");
    printf("Scegli una missione: \n");
    printf("1 >>> Palude Putrescente \n");
    printf("2 >>> Magione Infestata\n");
    printf("3 >>> Grotta di Cristallo\n");
    printf("Scegli una delle opzioni (1-3)\n");

    scanf("%d",&scelta);

   

    if(scelta ==1){
        puliscischermo();

        int sceltammissione;
        printf("Menu di missione \n");
        printf("1 >>> Esplora stanza Dungeon\n");
        printf("Scegli una delle opzioni (1-3)\n");
        scanf("%d",&sceltammissione);
     


        if(sceltammissione == 1){
           puliscischermo();
           
            esploraStanzaDungeon(giocatore_ptr);

            




        }
    }


}
#include <stdio.h>

#include <stdlib.h>

void Menu(){



    int scelta;

    printf("Menù scelta missioni \n");
    printf("Scegli una missione: \n");
    printf("1 >>> Palude Putrescente \n");
    printf("2 >>> Magione Infestata\n");
    printf("3 >>> Grotta di Cristallo\n");
    printf("Scegli una delle opzioni (1-3)\n");

    scanf("%d",&scelta);

   

    if(scelta ==1){
        system("clear");

        int sceltammissione;
        printf("Menu di missione \n");
        printf("1 >>> Esplora stanza Dungeon\n");
        printf("Scegli una delle opzioni (1-3)\n");
        scanf("%d",&sceltammissione);
     


        if(sceltammissione == 1){
            system("clear");
           
            srand(time(NULL));

            

            int risdado = rand() % 6 + 1;



        }
    }


}
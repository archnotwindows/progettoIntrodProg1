#include <stdio.h>
#include <stdlib.h>
#include "menuMissioni.h"
#include "systemclear.h"
#include "missione1espdun.h"
#include "inventario.h"
#include "negozio.h"

void Menu(Giocatore* giocatore_ptr){
    int scelta;

    printf("Menu scelta missioni \n");
    printf("1 >>> Palude Putrescente \n");
    printf("2 >>> Magione Infestata\n");
    printf("3 >>> Grotta di Cristallo\n");
    printf("Scegli una delle opzioni (1-3)\n");

    scanf("%d",&scelta);

    if(scelta >= 1 && scelta <= 3){ 
        puliscischermo();

        int sceltammissione;
        printf("Menu di missione \n");
        printf("1 >>> Esplora stanza Dungeon\n");
        printf("2 >>> Negozio\n");
        printf("3 >>> Inventario\n");
        printf("4 >>> Torna al Villaggio (Paga 50 Monete)\n");
        printf("Scegli una delle opzioni (1-4)\n");
        scanf("%d",&sceltammissione);

        if(sceltammissione == 1){  
           puliscischermo();
           if(scelta == 1){
                esplora1StanzaDungeon(giocatore_ptr);
           }
           else {
                 printf("Missione in sviluppo...\n");
           }
        }
        else if(sceltammissione == 2){ 
            puliscischermo();
            negozio(giocatore_ptr);
        }
        else if(sceltammissione == 3){ 
            puliscischermo();
            Inventario(giocatore_ptr);
        }
        else if(sceltammissione == 4){   
            puliscischermo();
            if(giocatore_ptr->monete >= 50){
                giocatore_ptr->monete -= 50;
                printf("Sei tornato al Villaggio pagando 50 monete.\n");
                // Richiamata ricorsiva del Menu
                Menu(giocatore_ptr); 
            } else {
                printf("Non hai abbastanza monete per tornare al Villaggio!\n");
            }
        }
        else{
            printf("Opzione non valida \n");
        }
    }
}
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
        printf("2 >>> Negozio\n");
        printf("3 >>> Inventario\n");
        printf("4 >>> Torna al Villaggio(Paga 50 Monete\n");
        printf("Scegli una delle opzioni (1-3)\n");
        scanf("%d",&sceltammissione);
     


        if(sceltammissione == 1){
           puliscischermo();
           
            esplora1StanzaDungeon(giocatore_ptr);


        }
        else if(sceltammissione ==2){

            puliscischermo();
            printf("Benvenuto nel negozio della Palude Putrescente!\n");
            printf("Qui puoi acquistare potenziamenti per il tuo personaggio.\n");
            printf("1. Pozione Curativa (+6 Vita) - 4 Monete\n");
            printf("2. Spada (+1 Attacco) - 5 Monete\n");
            printf("3. Armatura (+1 Difesa) - 10 Monete\n");
            printf("Scegli un'opzione (1-3) o 0 per uscire:\n");

            int scelta_negozio;
            scanf("%d", &scelta_negozio);

            switch(scelta_negozio) {
                case 1:
                    if(giocatore_ptr->monete >= 4) {
                        giocatore_ptr->vita += 6;
                        giocatore_ptr->monete -= 4;
                        printf("Hai acquistato una Pozione Curativa La tua vita è ora %d.\n", giocatore_ptr->vita);
                    } else {
                        printf("Non hai abbastanza monete!\n");
                    }
                    break;
                case 2:
                    if(giocatore_ptr->monete >= 5) {
                        giocatore_ptr->attacco += 1;
                        giocatore_ptr->monete -= 5;
                        printf("Hai acquistato una Spada Il tuo attacco è ora %d.\n", giocatore_ptr->attacco);
                    } else {
                        printf("Non hai abbastanza monete!\n");
                    }
                    break;
                case 3:
                    if(giocatore_ptr->monete >= 10) {
               
                        giocatore_ptr->difesa += 1; 
                        giocatore_ptr->monete -= 10;
                        printf("Hai acquistato un'Armatura!\n");
                    } else {
                        printf("Non hai abbastanza monete!\n");
                    }
                    break;
                case 0:
                    printf("Uscita dal negozio.\n");
                    break;
                default:
                    printf("Opzione non valida.\n");
            }
        }
    }


}
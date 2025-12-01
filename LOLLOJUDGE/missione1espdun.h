#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "giocatore.h"
#include "tabellemissioni.c"


void esploraStanzaDungeon(Giocatore* giocatore_ptr){
    

    srand(time(NULL));

    int risdado = rand() % 6 + 1;

    printf("è uscito: %d\n",risdado);

    printf("Giocatore vita prima della stanza: %d\n", giocatore_ptr->vita);

    if(risdado == 5){
        printf("Hai trovato una trappola speciale! Non succede nulla!\n");
    } else {
        struct RigaDungeon nemico = Palude[risdado - 1];

        printf("Hai incontrato: %s\n", nemico.nome);

        int colpo_necessario = nemico.colpo_fatale;
        int dado_combat = rand() % 6 + 1;

        printf("Devi fare almeno %d per sconfiggerlo. Hai fatto: %d\n", colpo_necessario, dado_combat);

        if(dado_combat >= colpo_necessario){
            printf("Hai sconfitto il nemico e guadagni %d monete!\n", nemico.monete_vittoria);
            giocatore_ptr->monete += nemico.monete_vittoria;
        } else {
            printf("Hai perso contro il nemico e subisci %d danni!\n", nemico.danno_nemico);
            giocatore_ptr->vita -= nemico.danno_nemico;
        }
    }



}
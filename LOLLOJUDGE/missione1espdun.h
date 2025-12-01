#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "giocatore.h"
#include "tabellemissioni.c"


void esplora1StanzaDungeon(Giocatore* giocatore_ptr){
    

    srand(time(NULL));

    int risdado = rand() % 6 + 1;

    printf("è uscito: %d\n",risdado);

    printf("Giocatore vita prima della stanza: %d\n", giocatore_ptr->vita);

    if(risdado == 5){
        printf("Hai trovato una trappola speciale! Non succede nulla!\n");  // caso trappola
    } else {
        struct RigaDungeon nemico = Palude[risdado - 1]; // salvo il nemico corrispondente

        printf("Hai incontrato: %s\n", nemico.nome);  // stampo nome nemico

        int colpo_necessario = nemico.colpo_fatale; // calcolo colpo necessario al giocatore
        int dado_combat = rand() % 6 + 1; // tiro il dado per il combattimento

        printf("Devi fare almeno %d per sconfiggerlo. Hai fatto: %d\n", colpo_necessario, dado_combat); // stampo Resoconto

        if(dado_combat >= colpo_necessario){
            printf("Hai sconfitto il nemico e guadagni %d monete!\n", nemico.monete_vittoria);
            giocatore_ptr->monete += nemico.monete_vittoria;  // aggiungo le monete di vittoria al giocatore
        } else {
            printf("Hai perso contro il nemico e subisci %d danni!\n", nemico.danno_nemico);
            giocatore_ptr->vita -= nemico.danno_nemico; // tolto vita al giocatore
        }
    }



}
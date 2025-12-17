#include <stdio.h>
#include <stdlib.h>
#include "missione1espdun.h"
#include "tabellemissioni.h" 

static int lanciaDado() {
    return rand() % 6 + 1;
}

void esplora1StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* generali_uccisi) {
    const int OBIETTIVO_GENERALI = 3;
    const int MAX_STANZE = 10;
    
  
    int stanze_rimanenti = MAX_STANZE - *stanza_corrente + 1;
    int generali_mancanti = OBIETTIVO_GENERALI - *generali_uccisi;
    int indice_tabella;

    printf("\n----------------------------------------\n");
    printf("ESPLORAZIONE STANZA %d (Obiettivo: %d/3 Generali)\n", *stanza_corrente, *generali_uccisi);

    if (generali_mancanti > 0 && generali_mancanti >= stanze_rimanenti) {
        printf(">>> L'aria si fa pesante... senti la presenza di un Generale! (Incontro Forzato)\n");
        indice_tabella = 5; // Indice 5 = Generale Orco
    } else {
        int tiro = lanciaDado();
        printf("Tiri il dado per generare la stanza: %d\n", tiro);
        indice_tabella = tiro - 1; 
    }

    struct RigaDungeon stanza = TabellaPalude[indice_tabella];

    if (stanza.tipo == TIPO_TRAPPOLA) {
        printf("Ti imbatti in: %s\n", stanza.nome);
        int danno = stanza.danno;

      
        if (danno == -1 || indice_tabella == 4) { 
            danno = lanciaDado();
            printf("L'acquitrino è instabile! Il dado decide il danno: %d\n", danno);
        }

       
        if (giocatore_ptr->ha_armatura && danno > 0) {
            danno--;
            printf("La tua armatura assorbe parte del colpo (-1 danno).\n");
        }

        if (danno < 0) danno = 0;
        printf("Subisci %d danni dalla trappola.\n", danno);
        giocatore_ptr->vita -= danno;
    }

 
    else if (stanza.tipo == TIPO_COMBATTIMENTO) {
        printf("COMBATTIMENTO! Hai incontrato: %s\n", stanza.nome);
        
        int nemico_vivo = 1;
        int colpo_fatale = stanza.colpo_fatale;

    
        if (indice_tabella == 5 && giocatore_ptr->ha_spada_eroe) {
            colpo_fatale = 5;
            printf("Grazie alla Spada dell'Eroe, il Generale è più debole! (Colpo Fatale ridotto a 5)\n");
        }

        while (nemico_vivo && giocatore_ptr->vita > 0) {
            printf("\n[TU: %d HP] vs [%s] (Serve > %d per vincere)\n", giocatore_ptr->vita, stanza.nome, colpo_fatale);
            printf("Premi INVIO per attaccare...");
            while(getchar() != '\n'); 

            int dado_attacco = lanciaDado();
            int attacco_totale = dado_attacco + giocatore_ptr->attacco; 

            printf("Hai rollato %d (+%d bonus) = %d. ", dado_attacco, giocatore_ptr->attacco, attacco_totale);

            if (attacco_totale > colpo_fatale) {
                printf("COLPITO! Nemico sconfitto!\n");
                nemico_vivo = 0;
                printf("Ottieni %d monete.\n", stanza.monete);
                giocatore_ptr->monete += stanza.monete;

                if (indice_tabella == 5) {
                    (*generali_uccisi)++;
                    printf(">>> OBIETTIVO AGGIORNATO: Generali uccisi %d/3 <<<\n", *generali_uccisi);
                }

            } else {
                printf("MANCATO!\n");
                int danno_nemico = stanza.danno;
                if (giocatore_ptr->ha_armatura) {
                    danno_nemico = (danno_nemico - 1 > 0) ? danno_nemico - 1 : 0;
                }
                printf("Il nemico contrattacca! Subisci %d danni.\n", danno_nemico);
                giocatore_ptr->vita -= danno_nemico;
            }
        }
    }
    
    (*stanza_corrente)++; 

    if (*generali_uccisi >= OBIETTIVO_GENERALI) {
        giocatore_ptr->missione_palude_completata = 1;
    }

    printf("----------------------------------------\n");
    printf("Premi INVIO per continuare...");
    while(getchar() != '\n');
}
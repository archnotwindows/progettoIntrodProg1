/**
 * @file missione1espdun.c
 * @brief Implementazione della missione Palude Putrescente.
 */
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

    printf("\n--- PALUDE PUTRESCENTE: Stanza %d ---\n", *stanza_corrente);
    printf("Obiettivo: %d/3 Generali Orchi sconfitti\n", *generali_uccisi);

    // Force encounter if running out of rooms
    if (generali_mancanti > 0 && generali_mancanti >= stanze_rimanenti) {
        printf(">>> Senti dei passi pesanti... Un Generale si avvicina! (Incontro Forzato)\n");
        indice_tabella = 5;
    } else {
        int tiro = lanciaDado();
        printf("Esplori la palude... (Dado: %d)\n", tiro);
        indice_tabella = tiro - 1;
    }

    struct RigaDungeon stanza = TabellaPalude[indice_tabella];

    if (stanza.tipo == TIPO_TRAPPOLA) {
        printf("TRAPPOLA! Ti imbatti in: %s\n", stanza.nome);
        int danno = stanza.danno;

        if (danno == -1 || indice_tabella == 4) { 
            danno = lanciaDado();
            printf("L'acquitrino ti risucchia! Subisci %d danni.\n", danno);
        }

        if (giocatore_ptr->ha_armatura && danno > 0) {
            danno--; 
            printf("(Armatura riduce il danno di 1)\n");
        }

        if (danno < 0) danno = 0;
        giocatore_ptr->vita -= danno;
        printf("Vita residua: %d\n", giocatore_ptr->vita);
    }
    else if (stanza.tipo == TIPO_COMBATTIMENTO) {
        printf("COMBATTIMENTO! Nemico: %s\n", stanza.nome);
        
        int nemico_vivo = 1;
        int colpo_fatale = stanza.colpo_fatale;

        if (indice_tabella == 5 && giocatore_ptr->ha_spada_eroe) {
            colpo_fatale = 5;
            printf("La tua Spada dell'Eroe brilla! Il Generale sembra piu' debole (Colpo Fatale 5).\n");
        }

        while (nemico_vivo && giocatore_ptr->vita > 0) {
            printf("\n[TU: %d HP] vs [%s] (Tira > %d per colpire)\n", giocatore_ptr->vita, stanza.nome, colpo_fatale);
            printf("Premi INVIO per attaccare...");
            while(getchar() != '\n'); 

            int dado_attacco = lanciaDado();
            int attacco_totale = dado_attacco + giocatore_ptr->attacco; 

            printf("Hai fatto %d (+%d bonus) = %d. ", dado_attacco, giocatore_ptr->attacco, attacco_totale);

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
                if (giocatore_ptr->ha_armatura && danno_nemico > 0) {
                    danno_nemico--;
                }
                
                printf("Il nemico contrattacca! Subisci %d danni.\n", danno_nemico);
                giocatore_ptr->vita -= danno_nemico;
            }
        }
    }
    
    (*stanza_corrente)++; 

    if (*generali_uccisi >= OBIETTIVO_GENERALI) {
        giocatore_ptr->missione_palude_completata = true;
    }

    printf("\nPremi INVIO per continuare...");
    while(getchar() != '\n');
}
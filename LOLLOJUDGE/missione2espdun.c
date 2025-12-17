#include <stdio.h>
#include <stdlib.h>
#include "missione2espdun.h"
#include "tabellemissioni.h"

static int lanciaDado() { return rand() % 6 + 1; }

void esplora2StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* progressi) {
    const int MAX_STANZE = 10;
    
    
    int ha_chiave = (*progressi & 1);     
    int vampiro_morto = (*progressi & 2); 

    printf("\n--- MAGIONE INFESTATA: STANZA %d/%d ---\n", *stanza_corrente, MAX_STANZE);
    printf("Stato Missione: Chiave [%s] - Vampiro Sconfitto [%s]\n", 
           ha_chiave ? "PRESA" : "MANCANTE", 
           vampiro_morto ? "SI" : "NO");

    
    int stanze_rimanenti = MAX_STANZE - *stanza_corrente + 1;
    int obiettivi_mancanti = (!ha_chiave) + (!vampiro_morto ? 1 : 0);
    int indice_tabella;

    if (obiettivi_mancanti > 0 && obiettivi_mancanti >= stanze_rimanenti) {
        printf(">>> Presenza oscura rilevata! (Incontro Forzato)\n");
        if (!ha_chiave) indice_tabella = 5; 
        else indice_tabella = 4;            
    } else {
        int tiro = lanciaDado();
        indice_tabella = tiro - 1;
    }

    struct RigaDungeon stanza = TabellaMagione[indice_tabella];
    printf("Ti imbatti in: %s\n", stanza.nome);

    
    if (stanza.tipo == TIPO_TRAPPOLA) {
        int danno = stanza.danno;
        if (giocatore_ptr->ha_armatura && danno > 0) danno--;
        printf("Trappola scatta! Subisci %d danni.\n", danno);
        giocatore_ptr->vita -= danno;
    }
    
    else if (stanza.tipo == TIPO_COMBATTIMENTO) {
        int nemico_vivo = 1;
        while (nemico_vivo && giocatore_ptr->vita > 0) {
            printf("\nTU: %d HP | NEMICO (%d Fatale)\nINVIO per attaccare...", giocatore_ptr->vita, stanza.colpo_fatale);
            while(getchar() != '\n');

            int attacco = lanciaDado() + giocatore_ptr->attacco;
            if (attacco > stanza.colpo_fatale) {
                printf("COLPITO! Vittoria!\n");
                nemico_vivo = 0;
                giocatore_ptr->monete += stanza.monete;

                
                if (stanza.is_obiettivo == 1) { 
                    if (!vampiro_morto) {
                        *progressi |= 2; 
                        printf(">>> Vampiro Superiore Sconfitto! <<<\n");
                    }
                } 
                else if (stanza.is_obiettivo == 2) { 
                    if (!ha_chiave) {
                        *progressi |= 1; 
                        giocatore_ptr->ha_chiave = true;
                        printf(">>> Chiave del Castello Recuperata! <<<\n");
                    }
                }
            } else {
                int danno = stanza.danno;
                if (giocatore_ptr->ha_armatura && danno > 0) danno--;
                printf("MANCATO! Subisci %d danni.\n", danno);
                giocatore_ptr->vita -= danno;
            }
        }
    }

    (*stanza_corrente)++;
    
    
    if ((*progressi & 3) == 3) {
        giocatore_ptr->missione_magione_completata = true;
    }

    printf("Premi INVIO...");
    while(getchar() != '\n');
}
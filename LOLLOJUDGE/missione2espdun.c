#include <stdio.h>
#include <stdlib.h>
#include "missione2espdun.h"
#include "tabellemissioni.h"

int lanciaDado();

void esplora2StanzaDungeon(Giocatore* giocatore_ptr) {
    printf("\n--- INIZIO MISSIONE: MAGIONE INFESTATA ---\n");
    printf("Obiettivo: Recupera la chiave del Castello e sconfiggi un Vampiro Superiore.\n");

    int vampiro_sconfitto = 0;
    int chiave_ottenuta = 0;
    const int MAX_STANZE = 10;

    for (int i = 1; i <= MAX_STANZE; i++) {
        // Controllo vittoria
        if (vampiro_sconfitto && chiave_ottenuta) {
            printf("\n>>> MISSIONE COMPLETATA! <<<\n");
            giocatore_ptr->missione_magione_completata = true;
            giocatore_ptr->ha_chiave = true;
            return;
        }

        if (giocatore_ptr->vita <= 0) {
            printf("Sei stato sconfitto... GAME OVER.\n");
            return;
        }

        printf("\n--- STANZA %d/%d ---\n", i, MAX_STANZE);

        int indice_tabella;
        int stanze_rimanenti = MAX_STANZE - i + 1;
        int obiettivi_mancanti = (vampiro_sconfitto ? 0 : 1) + (chiave_ottenuta ? 0 : 1);

        // Forzatura se necessario
        if (obiettivi_mancanti >= stanze_rimanenti) {
            printf("(Il destino ti guida...)\n");
            if (!vampiro_sconfitto) {
                indice_tabella = 4; // Vampiro Superiore
            } else {
                indice_tabella = 5; // Demone Custode (con chiave)
            }
        } else {
            int tiro = lanciaDado();
            indice_tabella = tiro - 1;
        }

        struct RigaDungeon stanza = TabellaMagione[indice_tabella];
        printf("Incontri: %s\n", stanza.nome);

        // TRAPPOLA
        if (stanza.tipo == TIPO_TRAPPOLA) {
            int danno = stanza.danno;
            if (giocatore_ptr->ha_armatura && danno > 0) {
                danno = (danno - 1 > 0) ? danno - 1 : 0;
            }
            printf("E' una trappola! Subisci %d danni.\n", danno);
            giocatore_ptr->vita -= danno;
        }
        // COMBATTIMENTO
        else if (stanza.tipo == TIPO_COMBATTIMENTO) {
            int nemico_vivo = 1;
            
            while (nemico_vivo && giocatore_ptr->vita > 0) {
                printf("Tua Vita: %d | Premi INVIO per attaccare...", giocatore_ptr->vita);
                getchar();
                
                int dado_eroe = lanciaDado();
                int attacco_totale = dado_eroe + giocatore_ptr->attacco;
                
                printf("Hai rollato %d (+%d bonus) = %d. Colpo Fatale: %d\n", 
                       dado_eroe, giocatore_ptr->attacco, attacco_totale, stanza.colpo_fatale);

                if (attacco_totale >= stanza.colpo_fatale) {
                    printf("Nemico sconfitto! Guadagni %d monete.\n", stanza.monete);
                    giocatore_ptr->monete += stanza.monete;
                    nemico_vivo = 0;
                    
                    if (stanza.is_obiettivo == 1) {
                        vampiro_sconfitto = 1;
                        printf(">>> Vampiro Superiore eliminato! <<<\n");
                    } else if (stanza.is_obiettivo == 2) {
                        chiave_ottenuta = 1;
                        printf(">>> Hai ottenuto la Chiave del Castello del Signore Oscuro! <<<\n");
                    }
                } else {
                    int danno = stanza.danno;
                    if (giocatore_ptr->ha_armatura) {
                        danno = (danno - 1 > 0) ? danno - 1 : 0;
                    }
                    printf("Attacco fallito! Il nemico infligge %d danni.\n", danno);
                    giocatore_ptr->vita -= danno;
                    
                    if (giocatore_ptr->vita <= 0) {
                        printf("Sei stato sconfitto... GAME OVER.\n");
                        return;
                    }
                }
            }
        }
    }

    if (vampiro_sconfitto && chiave_ottenuta) {
        printf("\n>>> MISSIONE COMPLETATA! <<<\n");
        giocatore_ptr->missione_magione_completata = true;
        giocatore_ptr->ha_chiave = true;
    } else {
        printf("Sei uscito senza completare l'obiettivo.\n");
    }
}
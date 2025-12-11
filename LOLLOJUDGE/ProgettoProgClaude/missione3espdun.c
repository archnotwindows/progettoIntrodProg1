#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "missione3espdun.h"
#include "tabellemissioni.h"

int lanciaDado();

// Funzione ricorsiva per calcolare la sequenza di Padovan
int padovan(int n) {
    if (n == 0 || n == 1 || n == 2) {
        return 1;
    }
    return padovan(n - 2) + padovan(n - 3);
}

// Verifica se un numero appartiene alla sequenza di Padovan
int appartienePadovan(int numero) {
    if (numero < 1) return 0;
    
    int i = 0;
    int p;
    while ((p = padovan(i)) <= numero) {
        if (p == numero) return 1;
        i++;
    }
    return 0;
}

void esplora3StanzaDungeon(Giocatore* giocatore_ptr) {
    printf("\n--- INIZIO MISSIONE: GROTTA DI CRISTALLO ---\n");
    printf("Obiettivo: Recupera la Spada dell'Eroe.\n");

    int spada_ottenuta = 0;
    const int MAX_STANZE = 10;

    for (int i = 1; i <= MAX_STANZE; i++) {
        if (spada_ottenuta) {
            printf("\n>>> MISSIONE COMPLETATA! Hai ottenuto la Spada dell'Eroe! <<<\n");
            giocatore_ptr->missione_grotta_completata = true;
            giocatore_ptr->ha_spada_eroe = true;
            giocatore_ptr->attacco += 2;
            return;
        }

        if (giocatore_ptr->vita <= 0) {
            printf("Sei stato sconfitto... GAME OVER.\n");
            return;
        }

        printf("\n--- STANZA %d/%d ---\n", i, MAX_STANZE);

        int indice_tabella;
        int stanze_rimanenti = MAX_STANZE - i + 1;

        // Forzatura Drago nell'ultima stanza se necessario
        if (!spada_ottenuta && stanze_rimanenti == 1) {
            printf("(Un'aura potente emana dall'oscurita'...)\n");
            indice_tabella = 5; // Drago Antico
        } else {
            int tiro = lanciaDado();
            indice_tabella = tiro - 1;
        }

        struct RigaDungeon stanza = TabellaGrotta[indice_tabella];
        printf("Incontri: %s\n", stanza.nome);

        // STANZA VUOTA
        if (stanza.tipo == TIPO_VUOTA) {
            printf("La stanza e' vuota. Prosegui.\n");
        }
        // TRAPPOLA
        else if (stanza.tipo == TIPO_TRAPPOLA) {
            // Ponte Pericolante (perde monete)
            if (stanza.danno == 0 && stanza.monete == -3) {
                int perdita = 3;
                if (giocatore_ptr->monete < perdita) {
                    perdita = giocatore_ptr->monete;
                }
                giocatore_ptr->monete -= perdita;
                printf("Il ponte crolla! Perdi %d monete.\n", perdita);
            }
            // Forziere Misterioso (lancia moneta)
            else if (stanza.danno == -2) {
                int moneta = rand() % 2; // 0 = croce, 1 = testa
                if (moneta == 1) {
                    giocatore_ptr->monete += stanza.monete;
                    printf("Fortuna! Il forziere contiene %d monete!\n", stanza.monete);
                } else {
                    int danno = 2;
                    if (giocatore_ptr->ha_armatura) {
                        danno = (danno - 1 > 0) ? danno - 1 : 0;
                    }
                    giocatore_ptr->vita -= danno;
                    printf("Sfortuna! Il forziere era intrappolato. Subisci %d danni.\n", danno);
                }
            }
            // Rupe scoscesa (danno 1d6)
            else if (stanza.danno == -1) {
                int danno = lanciaDado();
                if (giocatore_ptr->ha_armatura) {
                    danno = (danno - 1 > 0) ? danno - 1 : 0;
                }
                giocatore_ptr->vita -= danno;
                printf("Cadi dalla rupe! Subisci %d danni.\n", danno);
            }
            // Trappola normale
            else {
                int danno = stanza.danno;
                if (giocatore_ptr->ha_armatura && danno > 0) {
                    danno = (danno - 1 > 0) ? danno - 1 : 0;
                }
                giocatore_ptr->vita -= danno;
                printf("E' una trappola! Subisci %d danni.\n", danno);
            }
        }
        // COMBATTIMENTO (solo Drago)
        else if (stanza.tipo == TIPO_COMBATTIMENTO) {
            int nemico_vivo = 1;
            
            // Quiz Padovan prima del combattimento
            int numero_quiz = (rand() % 500) + 1;
            printf("\n--- ENIGMA DEL DRAGO ---\n");
            printf("Il Drago ti sfida: 'Il numero %d appartiene alla sequenza di Padovan?'\n", numero_quiz);
            printf("Rispondi [Si/No]: ");
            
            char risposta[10];
            scanf("%s", risposta);
            while(getchar() != '\n');
            
            int risposta_corretta = appartienePadovan(numero_quiz);
            int giocatore_risponde_si = (strcmp(risposta, "Si") == 0 || strcmp(risposta, "si") == 0);
            
            int danno_drago = stanza.danno;
            if ((risposta_corretta && giocatore_risponde_si) || (!risposta_corretta && !giocatore_risponde_si)) {
                printf("Risposta corretta! Il Drago e' impressionato e non attacca subito.\n");
                danno_drago = 0;
            } else {
                printf("Risposta sbagliata! Il Drago si infuria!\n");
            }
            
            while (nemico_vivo && giocatore_ptr->vita > 0) {
                printf("Tua Vita: %d | Premi INVIO per attaccare...", giocatore_ptr->vita);
                getchar();
                
                int dado_eroe = lanciaDado();
                int attacco_totale = dado_eroe + giocatore_ptr->attacco;
                
                printf("Hai rollato %d (+%d bonus) = %d. Colpo Fatale: %d\n", 
                       dado_eroe, giocatore_ptr->attacco, attacco_totale, stanza.colpo_fatale);

                if (attacco_totale >= stanza.colpo_fatale) {
                    printf("Drago Antico sconfitto! Guadagni %d monete.\n", stanza.monete);
                    giocatore_ptr->monete += stanza.monete;
                    nemico_vivo = 0;
                    spada_ottenuta = 1;
                    printf(">>> Hai ottenuto la SPADA DELL'EROE! (+2 Attacco) <<<\n");
                } else {
                    if (danno_drago > 0) {
                        int danno = danno_drago;
                        if (giocatore_ptr->ha_armatura) {
                            danno = (danno - 1 > 0) ? danno - 1 : 0;
                        }
                        giocatore_ptr->vita -= danno;
                        printf("Attacco fallito! Il Drago infligge %d danni.\n", danno);
                        danno_drago = stanza.danno; // Ripristina danno normale
                    } else {
                        printf("Attacco fallito! Ma il Drago risparmia il primo colpo.\n");
                        danno_drago = stanza.danno;
                    }
                    
                    if (giocatore_ptr->vita <= 0) {
                        printf("Sei stato sconfitto... GAME OVER.\n");
                        return;
                    }
                }
            }
        }
    }

    if (spada_ottenuta) {
        printf("\n>>> MISSIONE COMPLETATA! <<<\n");
        giocatore_ptr->missione_grotta_completata = true;
        giocatore_ptr->ha_spada_eroe = true;
    } else {
        printf("Sei uscito senza completare l'obiettivo.\n");
    }
}
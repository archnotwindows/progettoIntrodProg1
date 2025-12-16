#include <stdio.h>
#include <stdlib.h>
#include "missione1espdun.h"
#include "tabellemissioni.h"

// Funzione per lanciare il dado
int lanciaDado() {
    return rand() % 6 + 1;
}


void esplora1StanzaDungeon(Giocatore* giocatore_ptr) {
    printf("\n--- INIZIO MISSIONE: PALUDE PUTRESCENTE ---\n");
    printf("Obiettivo: Sconfiggi 3 Generali Orco.\n");

    int generali_sconfitti = 0;
    int obiettivo_richiesto = 3;
    const int MAX_STANZE = 10;

    
    for (int i = 1; i <= MAX_STANZE; i++) {
       
        // Controllo se la missione è già completata
        if (generali_sconfitti >= obiettivo_richiesto) {
            printf("\n>>> MISSIONE COMPLETATA! Hai sconfitto 3 Generali Orco! <<<\n");
            giocatore_ptr->missione_palude_completata = true;
            return;
        }


        // Controllo vita giocatore
        if (giocatore_ptr->vita <= 0) {
            printf("Sei stato sconfitto... GAME OVER.\n");
            return;
        }

        // Stampo il numero della stanza attuale
        printf("\n--- STANZA %d/%d ---\n", i, MAX_STANZE);


        // Variabili
        int indice_tabella;
        int stanze_rimanenti = MAX_STANZE - i + 1;
        int generali_mancanti = obiettivo_richiesto - generali_sconfitti;

        // Logica di forzatura
        if (generali_mancanti >= stanze_rimanenti) {
            printf("(Il destino ti guida verso il tuo obiettivo...)\n");
            indice_tabella = 5; // Indice del Generale Orco nella tabella
        } else {
            // Generazione randomica standard 
            int tiro = lanciaDado();
            indice_tabella = tiro - 1;
        }

        // Recupero la stanza dalla tabella
        struct RigaDungeon stanza = TabellaPalude[indice_tabella];
        printf("Incontri: %s\n", stanza.nome);

        // Getione caso stanza TRAPPOLA
        if (stanza.tipo == TIPO_TRAPPOLA) {
            int danno_trappola = stanza.danno;
            
            // Caso speciale Acquitrino: danno 1-6
            if (danno_trappola == -1) {
                danno_trappola = lanciaDado();
            }
            
            // Applica riduzione armatura
            if (giocatore_ptr->ha_armatura && danno_trappola > 0) {
                danno_trappola = (danno_trappola - 1 > 0) ? danno_trappola - 1 : 0;
            }

            printf("E' una trappola! Subisci %d danni.\n", danno_trappola);
            giocatore_ptr->vita -= danno_trappola;
        } 
        
        // Gestione caso stanza COMBATTIMENTO
        else if (stanza.tipo == TIPO_COMBATTIMENTO) {
            int nemico_vivo = 1;
            
            // Controlla se ha la Spada dell'Eroe per Generale Orco
            int colpo_fatale_richiesto = stanza.colpo_fatale;
            if (stanza.is_obiettivo == 1 && giocatore_ptr->ha_spada_eroe) {
                colpo_fatale_richiesto = 5;
            }
            
            // Loop di combattimento 
            while (nemico_vivo && giocatore_ptr->vita > 0) {
                printf("Tua Vita: %d | Premi INVIO per attaccare...", giocatore_ptr->vita);
                getchar();
                
                int dado_eroe = lanciaDado();
                int attacco_totale = dado_eroe + giocatore_ptr->attacco;
                
                printf("Hai rollato %d (+%d bonus) = %d. Colpo Fatale richiesto: %d\n", 
                       dado_eroe, giocatore_ptr->attacco, attacco_totale, colpo_fatale_richiesto);

                if (attacco_totale >= colpo_fatale_richiesto) {
                    printf("Nemico sconfitto! Guadagni %d monete.\n", stanza.monete);
                    giocatore_ptr->monete += stanza.monete;
                    nemico_vivo = 0;
                    
                    // Se era un Generale Orco, incrementiamo il contatore
                    if (stanza.is_obiettivo == 1) {
                        generali_sconfitti++;
                        printf(">>> Generale Orco ucciso! (%d/%d) <<<\n", generali_sconfitti, obiettivo_richiesto);
                    }
                } else {
                    int danno = stanza.danno;
                    
                    // Applica riduzione armatura
                    if (giocatore_ptr->ha_armatura) {
                        danno = (danno - 1 > 0) ? danno - 1 : 0;
                    }
                    
                    printf("Attacco fallito! Il nemico contrattacca e infligge %d danni.\n", danno);
                    giocatore_ptr->vita -= danno;
                    
                    if (giocatore_ptr->vita <= 0) {
                        printf("Sei stato sconfitto... GAME OVER.\n");
                        return;
                    }
                }
            }
        }
    }

    // Se finisco le 10 stanze
    if (generali_sconfitti >= obiettivo_richiesto) {
        printf("\n>>> MISSIONE COMPLETATA! <<<\n");
        giocatore_ptr->missione_palude_completata = true;
    } else {
        printf("Sei uscito dal dungeon senza completare l'obiettivo.\n");
    }
}
#include <stdio.h>
#include <stdlib.h> // per rand, srand
#include "missione1espdun.h"
#include "tabellemissioni.h"

// Funzione per lanciare un dado a 6 facce
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

        
        // Controllo vittoria immediata
        if (generali_sconfitti >= obiettivo_richiesto) {
            printf("\n>>> MISSIONE COMPLETATA! Hai sconfitto 3 Generali Orco! <<<\n");
            // Aggiungere logica per segnare missione come completata nella struct giocatore
            return;
        }

        if (giocatore_ptr->vita <= 0) return; // Game Over gestito altrove o qui

        printf("\n--- STANZA %d/%d ---\n", i, MAX_STANZE);

        int indice_tabella;
        int stanze_rimanenti = MAX_STANZE - i + 1;
        int generali_mancanti = obiettivo_richiesto - generali_sconfitti;

        // --- LOGICA DI FORZATURA [cite: 113] ---
        // Se i nemici mancanti sono uguali alle stanze rimanenti, NON tiriamo il dado.
        // Forziamo l'uscita del Generale Orco (indice 5 nella tabella, cioè dado 6)
        if (generali_mancanti >= stanze_rimanenti) {
            printf("(Il destino ti guida verso il tuo obiettivo...)\n");
            indice_tabella = 5; // Indice del Generale Orco
        } else {
            // Generazione procedurale standard 
            int tiro = lanciaDado();
            indice_tabella = tiro - 1; // Array parte da 0
        }

        struct RigaDungeon stanza = TabellaPalude[indice_tabella];
        printf("Incontri: %s\n", stanza.nome);

        // --- GESTIONE TRAPPOLA ---
        if (stanza.tipo == TIPO_TRAPPOLA) {
            int danno_trappola = stanza.danno;
            
            // Caso speciale Acquitrino: danno 1-6 [cite: 134]
            if (danno_trappola == -1) {
                danno_trappola = lanciaDado();
            }

            printf("E' una trappola! Subisci %d danni.\n", danno_trappola);
            giocatore_ptr->vita -= danno_trappola;
        } 
        
        // --- GESTIONE COMBATTIMENTO ---
        else if (stanza.tipo == TIPO_COMBATTIMENTO) {
            int nemico_vivo = 1;
            
            // Loop di combattimento 
            while (nemico_vivo && giocatore_ptr->vita > 0) {
                printf("Tua Vita: %d | Premi INVIO per attaccare...", giocatore_ptr->vita);
                while(getchar() != '\n'); // Attende input utente
                
                int dado_eroe = lanciaDado();
                int attacco_totale = dado_eroe + giocatore_ptr->attacco; // [cite: 175]
                
                printf("Hai rollato %d (+%d bonus) = %d. Colpo Fatale richiesto: %d\n", 
                       dado_eroe, giocatore_ptr->attacco, attacco_totale, stanza.colpo_fatale);

                if (attacco_totale >= stanza.colpo_fatale) {
                    printf("Nemico sconfitto! Guadagni %d monete.\n", stanza.monete);
                    giocatore_ptr->monete += stanza.monete;
                    nemico_vivo = 0;
                    
                    // Se era un Generale Orco, incrementiamo il contatore
                    if (stanza.is_obiettivo == 1) {
                        generali_sconfitti++;
                        printf(">>> Generale Orco ucciso! (%d/%d) <<<\n", generali_sconfitti, obiettivo_richiesto);
                    }
                } else {
                    printf("Attacco fallito! Il nemico contrattacca e infligge %d danni.\n", stanza.danno);
                    giocatore_ptr->vita -= stanza.danno;
                    if (giocatore_ptr->vita <= 0) {
                        printf("Sei stato sconfitto... GAME OVER.\n");
                        // Qui dovresti gestire il ritorno al menu principale o flag di morte
                        return;
                    }
                }
            }
        }
    }

    // Se finisci le 10 stanze e non hai ucciso i generali (impossibile con la forzatura, ma per sicurezza)
    if (generali_sconfitti < obiettivo_richiesto && giocatore_ptr->vita > 0) {
        printf("Sei uscito dal dungeon senza completare l'obiettivo.\n");
    } else if (generali_sconfitti >= obiettivo_richiesto) {
         printf("\n>>> MISSIONE COMPLETATA! <<<\n");
    }
}
#include <stdio.h>
#include <stdlib.h>
#include "missione1espdun.h"
#include "tabellemissioni.h" 

// funzione che lancia un dado a 6 facce
static int lanciaDado() {
    return rand() % 6 + 1;
}

void esplora1StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* generali_uccisi) {
    // Configurazioni della missione Palude
    const int OBIETTIVO_GENERALI = 3;
    const int MAX_STANZE = 10;
    
    // Calcoliamo quante stanze mancano alla fine del dungeon
    int stanze_rimanenti = MAX_STANZE - *stanza_corrente + 1;
    int generali_mancanti = OBIETTIVO_GENERALI - *generali_uccisi;
    int indice_tabella;

    printf("\n----------------------------------------\n");
    printf("ESPLORAZIONE STANZA %d (Obiettivo: %d/3 Generali)\n", *stanza_corrente, *generali_uccisi);

    // --- LOGICA DI FORZATURA STANZE ---
    // Se mancano ancora Generali da uccidere e le stanze stanno finendo,
    // (forzo l'apparizione di un Generale)
    if (generali_mancanti > 0 && generali_mancanti >= stanze_rimanenti) {
        printf(">>> L'aria si fa pesante... senti la presenza di un Generale! (Incontro Forzato)\n");
        indice_tabella = 5; // L'indice 5 corrisponde al GENERALE ORCO 
    } else {
        // Altrimenti, esplorazione normale con lancio di dado
        int tiro = lanciaDado();
        printf("Tiri il dado per generare la stanza: %d\n", tiro);
        indice_tabella = tiro - 1; // L'Array parte da 0, dado da 1
    }

    // Carico i dati della stanza dalla tabella globale della Palude
    struct RigaDungeon stanza = TabellaPalude[indice_tabella];

    // --- CASO 1: STANZA TRAPPOLA ---
    if (stanza.tipo == TIPO_TRAPPOLA) {
        printf("Ti imbatti in: %s\n", stanza.nome);
        int danno = stanza.danno;

        // Gestione danni variabili
        if (danno == -1 || indice_tabella == 4) { 
            danno = lanciaDado();
            printf("L'acquitrino è instabile! Il dado decide il danno: %d\n", danno);
        }

        // Riduzione del danno se il giocatore ha l'armatura
        if (giocatore_ptr->ha_armatura && danno > 0) {
            danno--; 
            printf("La tua armatura assorbe parte del colpo (-1 danno).\n");
        }

        // Applicazione del danno
        if (danno < 0) danno = 0;
        printf("Subisci %d danni dalla trappola.\n", danno);
        giocatore_ptr->vita -= danno;
    }

    // --- CASO 2: STANZA COMBATTIMENTO ---
    else if (stanza.tipo == TIPO_COMBATTIMENTO) {
        printf("COMBATTIMENTO! Hai incontrato: %s\n", stanza.nome);
        
        int nemico_vivo = 1;
        int colpo_fatale = stanza.colpo_fatale; // Valore da superare con il lancio del dado per vincere

        // Caso speciale: Se è un Generale e il giocatore ha la Spada dell'Eroe
        // (basta fare 5 col dado )
        if (indice_tabella == 5 && giocatore_ptr->ha_spada_eroe) {
            colpo_fatale = 5;
            printf("Grazie alla Spada dell'Eroe, il Generale è più debole! (Colpo Fatale ridotto a 5)\n");
        }

        // Ciclo di combattimento: continua finché uno dei due arriva a  0 vita
        while (nemico_vivo && giocatore_ptr->vita > 0) {
            printf("\n[TU: %d HP] vs [%s] (Serve > %d per vincere)\n", giocatore_ptr->vita, stanza.nome, colpo_fatale);
            printf("Premi INVIO per attaccare...");
            while(getchar() != '\n'); 

            // Calcolo attacco giocatore
            int dado_attacco = lanciaDado();
            int attacco_totale = dado_attacco + giocatore_ptr->attacco; 

            printf("Hai rollato %d (+%d bonus) = %d. ", dado_attacco, giocatore_ptr->attacco, attacco_totale);

            // Verifica successo dell'attacco
            if (attacco_totale > colpo_fatale) {
                // VITTORIA
                printf("COLPITO! Nemico sconfitto!\n");
                nemico_vivo = 0;
                
                // Ricompensa
                printf("Ottieni %d monete.\n", stanza.monete);
                giocatore_ptr->monete += stanza.monete;

                // Se é un Generale, aggiorno il contatore per la missione
                if (indice_tabella == 5) {
                    (*generali_uccisi)++;
                    printf(">>> OBIETTIVO AGGIORNATO: Generali uccisi %d/3 <<<\n", *generali_uccisi);
                }

            } else {
                // SCONFITTA -> Il nemico contrattacca
                printf("MANCATO!\n");
                int danno_nemico = stanza.danno;
                
                // L'armatura riduce il danno subito dal nemico
                if (giocatore_ptr->ha_armatura) {
                    danno_nemico = (danno_nemico - 1 > 0) ? danno_nemico - 1 : 0;
                }
                
                printf("Il nemico contrattacca! Subisci %d danni.\n", danno_nemico);
                giocatore_ptr->vita -= danno_nemico;
            }
        }
    }
    
    // Avanzamento alla prossima stanza 
    (*stanza_corrente)++; 

    // Verifica finale del completamento della missione
    if (*generali_uccisi >= OBIETTIVO_GENERALI) {
        giocatore_ptr->missione_palude_completata = 1;
    }

    printf("----------------------------------------\n");
    printf("Premi INVIO per continuare...");
    while(getchar() != '\n');
}
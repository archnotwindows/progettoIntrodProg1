#include <stdio.h>
#include <stdlib.h>
#include "missione1espdun.h"
#include "tabellemissioni.h" 
// Assicurati di includere gli header dove sono definiti Giocatore e le struct delle Tabelle

// Funzione helper per il dado (se non l'hai già in un file utility)
static int lanciaDado() {
    return rand() % 6 + 1;
}

void esplora1StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* generali_uccisi) {
    
    const int OBIETTIVO_GENERALI = 3;
    const int MAX_STANZE = 10;
    
    [cite_start]// 1. CALCOLO DELLA "FORZATURA" [cite: 104]
    // Calcoliamo quante stanze mancano e quanti generali mancano
    int stanze_rimanenti = MAX_STANZE - *stanza_corrente + 1;
    int generali_mancanti = OBIETTIVO_GENERALI - *generali_uccisi;
    int indice_tabella;

    printf("\n----------------------------------------\n");
    printf("ESPLORAZIONE STANZA %d (Obiettivo: %d/3 Generali)\n", *stanza_corrente, *generali_uccisi);

    // Se i mostri che mancano sono >= delle stanze rimaste, devo forzare l'uscita
    if (generali_mancanti > 0 && generali_mancanti >= stanze_rimanenti) {
        printf(">>> L'aria si fa pesante... senti la presenza di un Generale! (Incontro Forzato)\n");
        indice_tabella = 5; [cite_start]// Indice 5 = Generale Orco (nella tabella è il valore 6 del dado) [cite: 134]
    } else {
        // Altrimenti tiro il dado normalmente
        int tiro = lanciaDado();
        printf("Tiri il dado per generare la stanza: %d\n", tiro);
        indice_tabella = tiro - 1; // Perché l'array parte da 0
    }

    // Recuperiamo i dati dalla tabella (Tabella 2: Palude Putrescente)
    // Assumiamo che TabellaPalude sia un array globale o definito in tabellemissioni.h
    struct RigaDungeon stanza = TabellaPalude[indice_tabella];

    // --- GESTIONE TRAPPOLA ---
    if (stanza.tipo == TIPO_TRAPPOLA) {
        printf("Ti imbatti in: %s\n", stanza.nome);
        int danno = stanza.danno;

        [cite_start]// Caso speciale: Acquitrino Velenoso fa 1-6 danni [cite: 134]
        // Nella struct potresti aver messo -1 o un flag per indicare danno variabile
        if (danno == -1 || indice_tabella == 4) { 
            danno = lanciaDado();
            printf("L'acquitrino è instabile! Il dado decide il danno: %d\n", danno);
        }

        [cite_start]// Armatura: riduce il danno di 1 [cite: 91]
        if (giocatore_ptr->ha_armatura && danno > 0) {
            danno--;
            printf("La tua armatura assorbe parte del colpo (-1 danno).\n");
        }

        if (danno < 0) danno = 0; // Non curiamo il giocatore

        printf("Subisci %d danni dalla trappola.\n", danno);
        giocatore_ptr->vita -= danno;
    }

    // --- GESTIONE COMBATTIMENTO ---
    else if (stanza.tipo == TIPO_COMBATTIMENTO) {
        printf("COMBATTIMENTO! Hai incontrato: %s\n", stanza.nome);
        
        int nemico_vivo = 1;
        int colpo_fatale = stanza.colpo_fatale;

        [cite_start]// Regola speciale Generale Orco: se hai la Spada dell'Eroe il colpo fatale è 5 invece di 6 [cite: 135]
        if (indice_tabella == 5 && giocatore_ptr->ha_spada_eroe) {
            colpo_fatale = 5;
            printf("Grazie alla Spada dell'Eroe, il Generale è più debole! (Colpo Fatale ridotto a 5)\n");
        }

        while (nemico_vivo && giocatore_ptr->vita > 0) {
            printf("\n[TU: %d HP] vs [%s] (Serve > %d per vincere)\n", giocatore_ptr->vita, stanza.nome, colpo_fatale);
            printf("Premi INVIO per attaccare...");
            while(getchar() != '\n'); 

            int dado_attacco = lanciaDado();
            [cite_start]// Spada: +1 all'attacco [cite: 91]
            int attacco_totale = dado_attacco + giocatore_ptr->attacco; 

            printf("Hai rollato %d (+%d bonus) = %d. ", dado_attacco, giocatore_ptr->attacco, attacco_totale);

            [cite_start]// Attenzione: Vince se il risultato è "più alto" (>) non "uguale" (>=) [cite: 122, 133]
            if (attacco_totale > colpo_fatale) {
                printf("COLPITO! Nemico sconfitto!\n");
                nemico_vivo = 0;
                
                // Ricompensa
                printf("Ottieni %d monete.\n", stanza.monete);
                giocatore_ptr->monete += stanza.monete;

                // Se era un Generale, aggiorno il progresso missione
                if (indice_tabella == 5) {
                    (*generali_uccisi)++;
                    printf(">>> OBIETTIVO AGGIORNATO: Generali uccisi %d/3 <<<\n", *generali_uccisi);
                }

            } else {
                printf("MANCATO!\n");
                int danno_nemico = stanza.danno;
                
                [cite_start]// Armatura [cite: 91]
                if (giocatore_ptr->ha_armatura) {
                    danno_nemico = (danno_nemico - 1 > 0) ? danno_nemico - 1 : 0;
                    printf("(Armatura riduce il danno subito)\n");
                }
                
                printf("Il nemico contrattacca! Subisci %d danni.\n", danno_nemico);
                giocatore_ptr->vita -= danno_nemico;
            }
        }
    }

    // --- FINE DELL'ESPLORAZIONE DI QUESTA STANZA ---
    
    [cite_start]// Aggiorno il puntatore della stanza corrente per il Menu [cite: 120]
    (*stanza_corrente)++; 

    // Controllo finale: se ho ucciso 3 generali, segno la missione come completata nella struct del giocatore
    if (*generali_uccisi >= OBIETTIVO_GENERALI) {
        giocatore_ptr->missione_palude_completata = 1;
    }

    printf("----------------------------------------\n");
    printf("Premi INVIO per tornare al menu missione...");
    while(getchar() != '\n');
}
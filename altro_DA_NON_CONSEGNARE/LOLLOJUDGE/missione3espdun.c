#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "missione3espdun.h"
#include "tabellemissioni.h"

static int lanciaDado() { return rand() % 6 + 1; }


// funzione ricorsiva per calcolare il n-esimo numero di Padovan
int padovan(int n) {
    if (n == 0 || n == 1 || n == 2) return 1;
    return padovan(n - 2) + padovan(n - 3);
}


// funzione che verifica se un numero appartiene alla sequenza di Padovan
int appartienePadovan(int numero) {
    if (numero < 1) return 0;
    int i = 0, p;
  
    while ((p = padovan(i)) <= numero) {
        if (p == numero) return 1;
        i++;
    }
    return 0;
}

void esplora3StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* progressi) {
    const int MAX_STANZE = 10;
    
    printf("\n--- GROTTA DI CRISTALLO: STANZA %d/%d ---\n", *stanza_corrente, MAX_STANZE);

  
    int indice_tabella;
  
    // forzatura incontro con il drago 
    if (*progressi == 0 && *stanza_corrente == MAX_STANZE) {
        printf(">>> Un ruggito fa tremare le pareti... DRAGO! (Incontro Forzato)\n");
        indice_tabella = 5;
    } else {
        int tiro = lanciaDado();
        indice_tabella = tiro - 1;
    }

    struct RigaDungeon stanza = TabellaGrotta[indice_tabella];
    printf("Incontri: %s\n", stanza.nome);

    // CASO STANZA VUOTA
    if (stanza.tipo == TIPO_VUOTA) {
        printf("Stanza vuota.\n");
    } // CASO STANZA TRAPPOLA
    else if (stanza.tipo == TIPO_TRAPPOLA) {
      
        int danno = stanza.danno;
        int monete = stanza.monete;

    
        if (monete < 0 && danno == 0) {
            printf("Perdi monete cadendo dal ponte!\n");
            giocatore_ptr->monete += monete; 
            if (giocatore_ptr->monete < 0) giocatore_ptr->monete = 0;
        }
      
        else if (danno == -2) {
            if (rand() % 2 == 0) {
                printf("Fortuna! Trovi 10 monete.\n");
                giocatore_ptr->monete += 10;
            } else {
                printf("Trappola nel forziere! Subisci 2 danni.\n");
                if (giocatore_ptr->ha_armatura) giocatore_ptr->vita -= 1;
                else giocatore_ptr->vita -= 2;
            }
        }
       
        else if (danno == -1) {
            danno = lanciaDado();
            if (giocatore_ptr->ha_armatura && danno > 0) danno--;
            printf("Cadi dalla rupe! Subisci %d danni.\n", danno);
            giocatore_ptr->vita -= danno;
        }
    
        else {
            if (giocatore_ptr->ha_armatura && danno > 0) danno--;
            printf("Subisci %d danni.\n", danno);
            giocatore_ptr->vita -= danno;
        }
    }   // CASO STANZA COMBATTIMENTO
    else if (stanza.tipo == TIPO_COMBATTIMENTO) {
       
        int danno_primo_turno = stanza.danno;

      
        int numero_quiz = (rand() % 100) + 1; 
        printf("\nIL DRAGO CHIEDE: 'Il numero %d appartiene alla sequenza di Padovan?' [s/n]: ", numero_quiz);
        char risp;
        scanf(" %c", &risp);
        while(getchar() != '\n');

        int is_padovan = appartienePadovan(numero_quiz);
        int risposta_utente = (risp == 's' || risp == 'S');

        if (is_padovan == risposta_utente) {
            printf("DRAGO: 'Risposta corretta. Ti risparmio il primo soffio.'\n");
            danno_primo_turno = 0;
        } else {
            printf("DRAGO: 'Errato! Brucia!'\n");
        }

        int nemico_vivo = 1;
        int turno = 0;
        while (nemico_vivo && giocatore_ptr->vita > 0) {
            printf("TU: %d HP | DRAGO: Fatale %d\nINVIO...", giocatore_ptr->vita, stanza.colpo_fatale);
            while(getchar() != '\n');

            int attacco = lanciaDado() + giocatore_ptr->attacco;
            if (attacco > stanza.colpo_fatale) {
                printf("DRAGO SCONFITTO! Hai ottenuto la SPADA DELL'EROE (+2 ATT)!\n");
                giocatore_ptr->monete += stanza.monete;
                nemico_vivo = 0;
                
                
                giocatore_ptr->ha_spada_eroe = true;
                giocatore_ptr->attacco += 2;
                *progressi = 1;
            } else {
                int danno = (turno == 0) ? danno_primo_turno : stanza.danno;
                if (giocatore_ptr->ha_armatura && danno > 0) danno--;
                printf("Subisci %d danni dal Drago.\n", danno);
                giocatore_ptr->vita -= danno;
            }
            turno++;
        }
    }

    (*stanza_corrente)++;
    
    if (*progressi == 1) {
        giocatore_ptr->missione_grotta_completata = true;
    }

    printf("Premi INVIO...");
    while(getchar() != '\n');
}
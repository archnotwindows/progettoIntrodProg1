/**
* @file missione3espdun.c
* @brief Implementazione della missione "Grotta di Cristallo".
* * Questa missione introduce il Boss finale dei dungeon secondari: il Drago.
* Il combattimento include una meccanica unica basata sulla Sequenza di Padovan.
*/

#include <stdio.h>
#include <stdlib.h>
#include "missione3espdun.h"
#include "tabellemissioni.h"

/**
* @brief Funzione per il lancio dei dadi.
* @return Intero casuale [1, 6].
*/
static int lanciaDado() { return rand() % 6 + 1; }

/**
* @brief Calcola l'n-esimo numero della successione di Padovan P(n).
* * La successione è definita dalla relazione di ricorrenza: $P(n) = P(n-2) + P(n-3)$ con condizioni iniziali $P(0)=P(1)=P(2)=1$.
* @param n L'indice della sequenza da calcolare.
* @return Il valore di P(n).
*/
int padovan(int n) {
    if (n == 0 || n == 1 || n == 2) return 1;
    return padovan(n - 2) + padovan(n - 3);
}



/**
* @brief Verifica se un numero appartiene alla sequenza di Padovan.
* * La funzione genera numeri di Padovan crescenti finché non raggiunge
* o supera il numero target.
* * @param numero Il numero intero da verificare (generato casualmente dal Drago).
* @return 1 (true) se il numero appartiene alla sequenza, 0 (false) altrimenti.
*/
int appartienePadovan(int numero) {
    if (numero < 1) return 0;
    int i = 0, p;
    
    /* Genera la sequenza finché p <= numero */
    while ((p = padovan(i)) <= numero) {
        if (p == numero) return 1; /* Trovato! */
        i++;
    }
    return 0; /* Superato senza trovare il numero */
}

/**
* @brief Gestisce l'esplorazione di una stanza nella Grotta.
* * @param giocatore_ptr Puntatore ai dati del giocatore.
* @param stanza_corrente Puntatore al contatore stanze.
* @param progressi Puntatore flag (0 = Drago vivo, 1 = Drago morto).
*/
void esplora3StanzaDungeon(Giocatore* giocatore_ptr, int* stanza_corrente, int* progressi) {
    const int MAX_STANZE = 10;
    printf("\n--- GROTTA DI CRISTALLO: STANZA %d/%d ---\n", *stanza_corrente, MAX_STANZE);
    int indice_tabella;
  
    /** * @brief Logica di forzatura del Drago
    * Se siamo all'ultima stanza e il Drago non è ancora stato sconfitto (progressi == 0),
    * forza l'incontro (indice 5)
    */
    if (*progressi == 0 && *stanza_corrente == MAX_STANZE) {
        indice_tabella = 5;
    } else {
        int tiro = lanciaDado();
        indice_tabella = tiro - 1;
    }

    struct RigaDungeon stanza = TabellaGrotta[indice_tabella];
    printf("Incontri: %s\n", stanza.nome);

    /* --- GESTIONE TRAPPOLE E IMPREVISTI --- */
    if (stanza.tipo == TIPO_TRAPPOLA) {
        int danno = stanza.danno;
        int monete = stanza.monete;

        /* Caso 1: Caduta nel vuoto (Perdita monete) */
        if (monete < 0 && danno == 0) {
            printf("Perdi monete cadendo nel vuoto!\n");
            
            giocatore_ptr->monete += monete; /* monete è negativo, quindi sottrae */
            if (giocatore_ptr->monete < 0) giocatore_ptr->monete = 0;
        }
        /* Caso 2: Forziere trappola - Codice danno -2 */
        else if (danno == -2) {
            /* 50% probabilità: o ottieni oro o subisci danno */
            if (rand() % 2 == 0) {
                printf("Fortuna sfacciata! Trovi 10 monete nel forziere.\n");
                giocatore_ptr->monete += 10;
            } else {
                printf("Il forziere ha i denti! Subisci 2 danni.\n");
                /* Il danno del forziere ignora parzialmente l'armatura (o fa danno fisso) */
                if (giocatore_ptr->ha_armatura) giocatore_ptr->vita -= 1;
                else giocatore_ptr->vita -= 2;
            }
        }
        /* Caso 3: Burrone - Codice danno -1 */
        else if (danno == -1) {
            danno = lanciaDado();
            if (giocatore_ptr->ha_armatura && danno > 0) danno--;
            printf("Scivoli in un burrone! Subisci %d danni.\n", danno);
            giocatore_ptr->vita -= danno;
        }
        /* Caso 4: Danno standard */
        else {
            if (giocatore_ptr->ha_armatura && danno > 0) danno--;
            printf("Subisci %d danni.\n", danno);
            giocatore_ptr->vita -= danno;
        }
    }   
    /* --- GESTIONE COMBATTIMENTO E QUIZ DEL DRAGO --- */
    else if (stanza.tipo == TIPO_COMBATTIMENTO) {
        int danno_primo_turno = stanza.danno;

        /* Generazione Quiz Matematico */
        int numero_quiz = (rand() % 50) + 1; /* Numero random 1-50 */
        printf("\nIL DRAGO PARLA: 'Rispondi mortale! Il numero %d appartiene alla sequenza di Padovan?' [s/n]: ", numero_quiz);
        
        char risp;
        scanf(" %c", &risp);
        while(getchar() != '\n');

        /* Verifica correttezza logica */
        int is_padovan = appartienePadovan(numero_quiz);
        int risposta_utente_si = (risp == 's' || risp == 'S');
        
        /* XOR Logico invertito: Vero se (Utente dice Si E è Padovan) O (Utente dice No E non è Padovan) */
        int risposta_corretta = (risposta_utente_si && is_padovan) || (!risposta_utente_si && !is_padovan);

        if (risposta_corretta) {
            printf("DRAGO: 'Bravo... Ti risparmio di bruciarti subito.' (0 danni primo turno)\n");
            danno_primo_turno = 0; /* Annulla il danno iniziale */
        } else {
            printf("DRAGO: 'Stolto! Brucia!'\n");
        }

        int nemico_vivo = 1;
        int turno = 0;
        
        /* Loop Combattimento */
        while (nemico_vivo && giocatore_ptr->vita > 0) {
            printf("TU: %d HP | DRAGO (Difesa %d)\nINVIO per colpire...", giocatore_ptr->vita, stanza.colpo_fatale);
            while(getchar() != '\n');

            int attacco = lanciaDado() + giocatore_ptr->attacco;
            if (attacco > stanza.colpo_fatale) {
                printf("\n>>> DRAGO SCONFITTO! <<<\n"); 
                
                /* Ricompensa Leggendaria: +2 Attacco permanente */
                printf("Hai ottenuto la LEGGENDARIA SPADA DELL'EROE (+2 ATT)!\n");
                giocatore_ptr->monete += stanza.monete;
                nemico_vivo = 0;
                
                giocatore_ptr->ha_spada_eroe = true;
                giocatore_ptr->attacco += 2; /* Potenziamento statistiche */
                *progressi = 1; /* Segna missione come completa */
            } else {
                /* Applica danno (ridotto al primo turno se il quiz é corretto) */
                int danno = (turno == 0) ? danno_primo_turno : stanza.danno;
                if (giocatore_ptr->ha_armatura && danno > 0) danno--;
                
                printf("Il Drago ti colpisce! Subisci %d danni.\n", danno);
                giocatore_ptr->vita -= danno;
            }
            turno++;
        }
    }

    (*stanza_corrente)++;
    
    /* Verifica fine missione */
    if (*progressi == 1) {
        giocatore_ptr->missione_grotta_completata = true;
    }

    printf("Premi INVIO...");
    while(getchar() != '\n');
}
/**
 * @file menuvillaggio.c
 * @brief Implementazione delle funzionalità del menu del villaggio.
 * * Questo file gestisce il villaggio, da cui il giocatore
 * può accedere alle missioni, ripristinare la salute, gestire l'inventario,
 * salvare la partita o uscire.
 */

#include <stdio.h>
#include <stdlib.h>
#include "menuvillaggio.h"
#include "menuMissioni.h"
#include "inventario.h"
#include "systemclear.h"
#include "salvataggi.h"

/**
 * @brief Gestisce il loop principale del Villaggio.
 * * Questa funzione mostra un menu ciclico che permette al giocatore di prepararsi
 * prima di una missione. Gestisce anche il controllo del "Game Over" al ritorno
 * dalle missioni.
 * * @param giocatore_ptr Puntatore alla struttura dati Giocatore per
 * modificare vita, inventario e stato missioni.
 */
void menuVillaggio(Giocatore* giocatore_ptr) {
    
    /** * @brief Loop infinito del villaggio.
     * Il giocatore rimane in questo ciclo finché non sceglie di uscire (opzione 5)
     * o muore in missione (Game Over).
     */
    while (1) {
        puliscischermo();
        printf("===== VILLAGGIO =====\n");
        printf("1. Intraprendi missione\n");
        printf("2. Riposati (Ripristina vita) - (Costo: Gratis)\n");
        printf("3. Inventario\n");
        printf("4. Salva la partita\n");
        printf("5. Esci al Menu Principale\n");
        printf("Scelta: ");
        
        /* --- Gestione Input Utente --- */
        int scelta;
        /* Controllo validità input: se non è un intero, pulisce il buffer e ricarica il menu */
        if(scanf("%d", &scelta) != 1) { while(getchar()!='\n'); continue; }
        while(getchar() != '\n'); /**< Pulizia buffer */

        /* Opzione 1: Vai alle Missioni */
        if (scelta == 1) {
            /** * @brief Entra nel menu di selezione missioni.
             * Il controllo passa al modulo menuMissioni.c.
             */
            Menu(giocatore_ptr);
            
            /** * @brief Controllo stato vitale post-missione.
             * Quando la funzione Menu() ritorna, verifichiamo se il giocatore è vivo.
             * Se la vita è <= 0, il gioco termina
             */
            if (giocatore_ptr->vita <= 0) {
                puliscischermo();
                printf("\n=== GAME OVER ===\nSei morto.\n");
                printf("Premi INVIO per tornare al menu principale...");
                getchar(); 
                return; 
            }
        }
        /* Opzione 2: Riposo  */
        else if (scelta == 2) {
            /** * @brief Ripristino salute.
             * Imposta la vita del giocatore al valore massimo
             */
            giocatore_ptr->vita = 20;
            printf("Ti sei riposato. HP ripristinati!\nPremi INVIO..."); 
            getchar();
        }
        /* Opzione 3: Visualizza Inventario */
        else if (scelta == 3) {
            puliscischermo();
            Inventario(giocatore_ptr);
            printf("\nPremi INVIO...");
            getchar();
        }
        /* Opzione 4: Salvataggio */
        else if (scelta == 4) {
            /** * @brief Salva lo stato corrente del gioco su file.
             * Chiama la funzione definita in salvataggi.h.
             */
            nuovoSalvataggio(giocatore_ptr);
            printf("Premi INVIO...");
            getchar();
        }
        /* Opzione 5: Uscita */
        else if (scelta == 5) {
            printf("Stai tornando al menu principale. I progressi non salvati andranno persi.\n");
            printf("Confermi? (s/n): ");
            
            char c; 
            scanf("%c", &c);
            
            /* Conferma uscita*/
            if(c=='s' || c=='S') return;
        }
    }
}
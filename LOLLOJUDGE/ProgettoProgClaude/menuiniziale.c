#include <stdio.h>
#include <string.h>
#include "menuiniziale.h"
#include "menuvillaggio.h"
#include "salvataggio.h"
#include "systemclear.h"

static int trucchi_sbloccati = 0;

int verificaCodiceKonami() {
    // Sequenza Konami: w w s s a d a d b a [Spazio]
    char sequenza_konami[] = {'w', 'w', 's', 's', 'a', 'd', 'a', 'd', 'b', 'a', ' '};
    static char buffer[11] = {0};
    static int posizione = 0;
    
    char input;
    scanf("%c", &input);
    
    buffer[posizione] = input;
    posizione++;
    
    if (posizione == 11) {
        int match = 1;
        for (int i = 0; i < 11; i++) {
            if (buffer[i] != sequenza_konami[i]) {
                match = 0;
                break;
            }
        }
        
        if (match) {
            trucchi_sbloccati = 1;
            posizione = 0;
            memset(buffer, 0, 11);
            return 1;
        }
        
        // Shift del buffer
        for (int i = 0; i < 10; i++) {
            buffer[i] = buffer[i + 1];
        }
        posizione = 10;
    }
    
    return 0;
}

void menuTrucchi() {
    puliscischermo();
    printf("===== MENU TRUCCHI =====\n");
    
    if (num_salvataggi == 0) {
        printf("Nessun salvataggio disponibile per modificare.\n");
        printf("Premi INVIO per continuare...");
        while(getchar() != '\n');
        getchar();
        return;
    }
    
    printf("Seleziona un salvataggio da modificare:\n");
    for (int i = 0; i < num_salvataggi; i++) {
        if (salvataggi[i].attivo) {
            printf("%d. Salvataggio %d\n", i + 1, i + 1);
        }
    }
    
    printf("\nSeleziona [1-%d]: ", num_salvataggi);
    int scelta;
    scanf("%d", &scelta);
    while(getchar() != '\n');
    
    if (scelta < 1 || scelta > num_salvataggi || !salvataggi[scelta - 1].attivo) {
        printf("Salvataggio non valido.\n");
        return;
    }
    
    Giocatore* g = &salvataggi[scelta - 1].giocatore;
    
    printf("\n--- Modifica Statistiche ---\n");
    printf("Nuovi Punti Vita: ");
    scanf("%d", &g->vita);
    printf("Nuove Monete: ");
    scanf("%d", &g->monete);
    while(getchar() != '\n');
    
    printf("Sbloccare Missione Finale? [Si/No]: ");
    char risposta[10];
    scanf("%s", risposta);
    while(getchar() != '\n');
    
    if (strcmp(risposta, "Si") == 0 || strcmp(risposta, "si") == 0) {
        g->missione_palude_completata = true;
        g->missione_magione_completata = true;
        g->missione_grotta_completata = true;
        g->ha_chiave = true;
        g->ha_spada_eroe = true;
        printf("Missione finale sbloccata!\n");
    }
    
    printf("Modifiche salvate!\n");
}

void menuIniziale() {
    while (1) {
        puliscischermo();
        printf("===== MENU PRINCIPALE =====\n");
        printf("1. Nuova Partita\n");
        printf("2. Carica Salvataggio\n");
        if (trucchi_sbloccati) {
            printf("3. Trucchi\n");
            printf("Seleziona una delle opzioni del menu [1-3]: ");
        } else {
            printf("Seleziona una delle opzioni del menu [1-2]: ");
        }
        
        char input[10];
        if (!fgets(input, 10, stdin)) {
            continue;
        }
        
        // Verifica codice Konami
        if (!trucchi_sbloccati && strlen(input) == 2) {
            char ch = input[0];
            static char buffer_konami[11] = {0};
            static int pos_konami = 0;
            
            buffer_konami[pos_konami++] = ch;
            
            if (pos_konami == 11) {
                char seq[] = {'w', 'w', 's', 's', 'a', 'd', 'a', 'd', 'b', 'a', ' '};
                int match = 1;
                for (int i = 0; i < 11; i++) {
                    if (buffer_konami[i] != seq[i]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    trucchi_sbloccati = 1;
                    pos_konami = 0;
                    memset(buffer_konami, 0, 11);
                    continue;
                }
                for (int i = 0; i < 10; i++) {
                    buffer_konami[i] = buffer_konami[i + 1];
                }
                pos_konami = 10;
            }
            continue;
        }
        
        int scelta = atoi(input);
        
        if (scelta == 1) {
            // Nuova Partita
            Giocatore g = {20, 0, 0, false, false, false, false, false, false, false};
            puliscischermo();
            printf("Nuova avventura iniziata!\n");
            menuVillaggio(&g);
        } else if (scelta == 2) {
            // Carica Salvataggio
            Giocatore g;
            if (menuCaricaSalvataggio(&g)) {
                menuVillaggio(&g);
            }
        } else if (scelta == 3 && trucchi_sbloccati) {
            menuTrucchi();
        }
    }
}
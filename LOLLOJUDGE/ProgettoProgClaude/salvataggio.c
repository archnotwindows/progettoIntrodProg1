#include <stdio.h>
#include <string.h>
#include "salvataggio.h"
#include "systemclear.h"

Salvataggio salvataggi[MAX_SALVATAGGI];
int num_salvataggi = 0;

void salvaPartita(Giocatore* giocatore_ptr) {
    if (num_salvataggi >= MAX_SALVATAGGI) {
        printf("Limite di salvataggi raggiunto!\n");
        return;
    }
    
    salvataggi[num_salvataggi].giocatore = *giocatore_ptr;
    salvataggi[num_salvataggi].timestamp = time(NULL);
    salvataggi[num_salvataggi].attivo = 1;
    num_salvataggi++;
    
    printf("Partita salvata con successo!\n");
}

int menuCaricaSalvataggio(Giocatore* giocatore_ptr) {
    if (num_salvataggi == 0) {
        printf("Nessun salvataggio disponibile.\n");
        printf("Premi INVIO per continuare...");
        while(getchar() != '\n');
        getchar();
        return 0;
    }
    
    puliscischermo();
    printf("===== Carica Salvataggio =====\n");
    
    int count = 0;
    for (int i = 0; i < num_salvataggi; i++) {
        if (salvataggi[i].attivo) {
            count++;
            struct tm* timeinfo = localtime(&salvataggi[i].timestamp);
            char buffer[80];
            strftime(buffer, 80, "%d-%m-%Y %H:%M:%S", timeinfo);
            
            int missioni_completate = 0;
            if (salvataggi[i].giocatore.missione_palude_completata) missioni_completate++;
            if (salvataggi[i].giocatore.missione_magione_completata) missioni_completate++;
            if (salvataggi[i].giocatore.missione_grotta_completata) missioni_completate++;
            
            int oggetti = 0;
            if (salvataggi[i].giocatore.ha_spada) oggetti++;
            if (salvataggi[i].giocatore.ha_armatura) oggetti++;
            if (salvataggi[i].giocatore.ha_spada_eroe) oggetti++;
            if (salvataggi[i].giocatore.ha_chiave) oggetti++;
            
            printf("%d. %s, %d P.VITA, %d MONETE, %d OGGETTI, %d MISSIONI COMPLETATE\n",
                   i + 1, buffer, salvataggi[i].giocatore.vita, 
                   salvataggi[i].giocatore.monete, oggetti, missioni_completate);
        }
    }
    
    if (count == 0) {
        printf("Nessun salvataggio disponibile.\n");
        printf("Premi INVIO per continuare...");
        while(getchar() != '\n');
        getchar();
        return 0;
    }
    
    printf("\nSeleziona un salvataggio [1-%d]: ", num_salvataggi);
    int scelta;
    scanf("%d", &scelta);
    while(getchar() != '\n');
    
    if (scelta < 1 || scelta > num_salvataggi || !salvataggi[scelta - 1].attivo) {
        printf("Salvataggio non valido.\n");
        return 0;
    }
    
    printf("\nSeleziona un'opzione per il salvataggio %d:\n", scelta);
    printf("1. Carica\n");
    printf("2. Elimina\n");
    printf("Seleziona opzione [1-2]: ");
    
    int opzione;
    scanf("%d", &opzione);
    while(getchar() != '\n');
    
    if (opzione == 1) {
        *giocatore_ptr = salvataggi[scelta - 1].giocatore;
        printf("Salvataggio caricato con successo!\n");
        return 1;
    } else if (opzione == 2) {
        eliminaSalvataggio(scelta - 1);
        return 0;
    }
    
    return 0;
}

void eliminaSalvataggio(int indice) {
    printf("Sei sicuro di voler eliminare definitivamente il salvataggio? [Si/No]: ");
    char risposta[10];
    scanf("%s", risposta);
    while(getchar() != '\n');
    
    if (strcmp(risposta, "Si") == 0 || strcmp(risposta, "si") == 0) {
        salvataggi[indice].attivo = 0;
        printf("Salvataggio eliminato.\n");
    } else {
        printf("Operazione annullata.\n");
    }
}
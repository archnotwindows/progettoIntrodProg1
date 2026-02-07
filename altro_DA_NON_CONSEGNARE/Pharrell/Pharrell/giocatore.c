#include <stdio.h>
#include <stdlib.h>
#include "giocatore.h"

giocatore nuovo_giocatore(void){

   giocatore n;

   n.pv=20;
   n.missioni=0;
   n.monete=0;
   n.oggetti=0;
   
   return n;
} //funzione per la creazione di un nuovo giocatore

int giocatore_vivo(giocatore*g){

   if(g==NULL) return 0;
   if (*g).pv>0
   {

   }
}

void reset_salute (giocatore*g){

   if (g!=NULL){
      (*g).pv=20;
   } //funzione per ripristinare la salute
}

void completa_missione(giocatore*g){


}

void aggiungi_monete(giocatore*g, int m){


}

void aggiungi_oggetto(giocatore*g){


}

void print_giocaore (giocatore*g){


}




} archivio; //struttura contenente l'archivio dei diversi giocatori

archivio nuovo_archivio(){
   
   archivio a;
   a.elenco=NULL;
   a.totale=0;
   a.spazio=0;
   return a;
   
}

void aggiungi_salvataggio(archivio* a, giocatore g) {
    if (a == NULL) return;

    if (a->totale == a->spazio) {
        a->spazio = (a->spazio == 0) ? 1 : a->spazio * 2;
        a->elenco = realloc(a->elenco, a->spazio * sizeof(giocatore));
        if (a->elenco == NULL) {
            printf("Errore allocazione memoria!\n");
            exit(1);
        }
    }

    a->elenco[a->totale] = g;
    a->totale++;
}

void libera_archivio(archivio* a) {
    if (a != NULL) {
        free(a->elenco);
        a->elenco = NULL;
        a->totale = 0;
        a->spazio = 0;
    }
}

int main() {

int main() {
    archivio arch = nuovo_archivio();
    giocatore g1 = nuovo_giocatore();

    // Controllo se può fare missioni (riporta PV a 20 se vivo)
    if (puo_completare_missione(&g1))
        printf("Il giocatore può completare missioni.\n");
    else
        printf("Il giocatore non può fare missioni.\n");

    // Controllo se può ricevere monete
    if (puo_aggiungere_monete(&g1))
        printf("Il giocatore può ricevere monete.\n");

    // Controllo se può ricevere oggetti
    if (puo_aggiungere_oggetto(&g1))
        printf("Il giocatore può ricevere oggetti.\n");

    // Aggiungo il giocatore all'archivio
    aggiungi_salvataggio(&arch, g1);

    // Stampo i giocatori presenti nell'archivio
    for (int i = 0; i < arch.totale; i++) {
        printf("Giocatore %d: ", i + 1);
        print_giocatore(arch.elenco[i]);
    }

    // Libero la memoria dell'archivio
    libera_archivio(&arch);

    return 0;
   

    return 0;
}
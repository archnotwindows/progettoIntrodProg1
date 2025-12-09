#include <stdio.h>
#include <stdlib.h>


typedef struct {

	int punti_vita;
   int monete;
	int oggetti;
	int missioni; 
} giocatore; //struttura contenente viariabili del giocatore

giocatore nuovo_giocatore(){

   giocatore n;

   n.punti_vita=20;
   n.monete=0;
   n.oggetti=0;
   n.missioni=0;
   return n;
} //funzione per la creazione di un nuovo giocatore

typedef struct {

   giocatore*elenco;
   int totale;
   int spazio;

} archivio; //struttura contenente l'archivio dei diversi giocatori

archivio nuovo_archvio(){
   
   archivio a;
   a.elenco=NULL;
   a.totale=0;
   a.spazio=0;
   return a;
   
}

int main() {

   

    return 0;
}
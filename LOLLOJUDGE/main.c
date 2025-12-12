
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "giocatore.h"
#include "menuvillaggio.h"

int main(void) {
	srand((unsigned)time(NULL));

	Giocatore player;
	// inizializza giocatore con valori di default
	player.vita = 20;
	player.monete = 100;
	player.attacco = 1;
	player.ha_spada = 0;
	player.ha_armatura = 0;
	player.ha_spada_eroe = 0;
	player.ha_chiave = 0;
	player.missione_palude_completata = 0;
	player.missione_magione_completata = 0;
	player.missione_grotta_completata = 0;

	menuVillaggio(&player);

	printf("Grazie per aver giocato. Stato finale: Vita=%d Monete=%d\n", player.vita, player.monete);
	return 0;
}

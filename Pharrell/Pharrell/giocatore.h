#ifndef giocatore_h
#define giocatore_h

//Struttura del giocatore

typedef struct {

	int pv;
	int missioni;
	int monete;
	int oggetti;

} giocatore; 

//Funzioni del giocatore

	giocatore nuovo_giocatore (void);

	void reset_salute (giocatore*g);
	void completa_missioni (giocatore*g);
	void aggiungi_monete (giocatore*g, int monete);
	void aggiungi_oggetto (giocatore*g);
	void print_giocatore (giocatore g);

//Struttura dell'archvio

typedef struct {

	giocatore*elenco;
	int totale;
	int spazio;

} archivio; 

//Funzioni dell'archivio

	archivio nuovo_archivio (void);

	void aggiungi_salvataggio (archivio*n, giocatore g);
	void libera_archivio (archivio*a);

#endif

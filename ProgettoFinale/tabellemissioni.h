/**
 * @file tabellemissioni.h
 * @brief Definizioni per la generazione procedurale dei dungeon.
 * * Contiene le strutture dati per definire nemici, trappole e stanze.
 */

#ifndef TABELLEMISSIONI_H
#define TABELLEMISSIONI_H

/**
 * @enum TipoStanza
 * @brief Identifica la tipologia di incontro in una stanza.
 */
typedef enum {
    TIPO_COMBATTIMENTO, /**< Incontro con un nemico. */
    TIPO_TRAPPOLA,      /**< Evento che causa danno o penalità. */
    TIPO_VUOTA          /**< Stanza senza eventi. */
} TipoStanza;

/**
 * @struct RigaDungeon
 * @brief Rappresenta una possibile configurazione di una stanza del dungeon.
 */
struct RigaDungeon {
    char* nome;         /**< Nome del nemico o della trappola. */
    TipoStanza tipo;    /**< Tipo di evento (Combattimento o Trappola). */
    int colpo_fatale;   /**< Difficoltà per colpire (nemico) o evitare (trappola). */
    int danno;          /**< Danno inflitto in caso di fallimento/attacco nemico. */
    int monete;         /**< Ricompensa in monete o penalità (se negativo). */
    int is_obiettivo;   /**< 1=Boss/Obiettivo primario, 2=Obiettivo secondario, 0=Normale. */
};

/* Tabelle globali definite in tabellemissioni.c */
extern struct RigaDungeon TabellaPalude[];   /**< Tabella incontri per la Palude. */
extern struct RigaDungeon TabellaMagione[];  /**< Tabella incontri per la Magione. */
extern struct RigaDungeon TabellaGrotta[];   /**< Tabella incontri per la Grotta. */

#endif
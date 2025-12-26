#include "tabellemissioni.h"
#include <stddef.h> 

// Tabella 1: Palude Putrescente
struct RigaDungeon TabellaPalude[] = {
    {"Cane Selvaggio",      TIPO_COMBATTIMENTO, 2, 1, 0, 0},  
    {"Goblin",              TIPO_COMBATTIMENTO, 3, 2, 2, 0},  
    {"Scheletro",           TIPO_COMBATTIMENTO, 4, 2, 4, 0},  
    {"Orco",                TIPO_COMBATTIMENTO, 3, 4, 6, 0},  
    {"Acquitrino Velenoso", TIPO_TRAPPOLA,      0, -1, 0, 0}, 
    {"Generale Orco",       TIPO_COMBATTIMENTO, 6, 3, 12, 1}  
};

// Tabella 2: Magione Infestata
struct RigaDungeon TabellaMagione[] = {
    {"Botola Buia",        TIPO_TRAPPOLA,       0, 3, 0, 0},  
    {"Pipistrello",        TIPO_COMBATTIMENTO,  2, 2, 1, 0},  
    {"Zombie",             TIPO_COMBATTIMENTO,  3, 2, 2, 0},  
    {"Fantasma",           TIPO_COMBATTIMENTO,  5, 2, 4, 0},  
    {"Vampiro Superiore",  TIPO_COMBATTIMENTO,  4, 4, 7, 1},  
    {"Demone Custode",     TIPO_COMBATTIMENTO,  4, 6, 10, 2}  
};

// Tabella 3: Grotta di Cristallo
struct RigaDungeon TabellaGrotta[] = {
    {"Stanza Vuota",       TIPO_VUOTA,          0, 0, 0, 0},   
    {"Cristalli Cadenti",  TIPO_TRAPPOLA,       0, 2, 0, 0},   
    {"Ponte Pericolante",  TIPO_TRAPPOLA,       0, 0, -3, 0},  
    {"Forziere Misterioso",TIPO_TRAPPOLA,       0, -2, 10, 0}, 
    {"Rupe Scoscesa",      TIPO_TRAPPOLA,       0, -1, 0, 0},  
    {"Drago Antico",       TIPO_COMBATTIMENTO,  5, 10, 12, 1}  
};
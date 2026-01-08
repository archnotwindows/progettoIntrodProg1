/**
 * @file systemclear.h
 * @brief Header per la gestione della pulizia dello schermo multipiattaforma.
 */
#ifndef SYSTEMCLEAR_H
#define SYSTEMCLEAR_H

/**
 * @brief Pulisce la console (terminale).
 * * Esegue il comando di sistema appropriato in base al sistema operativo
 * ("cls" per Windows, "clear" per Linux/Mac).
 */
void puliscischermo();

#endif
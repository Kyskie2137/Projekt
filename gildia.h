#ifndef GILDIA_H
#define GILDIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_TEXT 50

typedef enum {
    AKTYWNY = 0,
    NA_MISJI,
    RANNY,
    ZAGINIONY,
    ZAWIESZONY
} StatusBohatera;

typedef struct Bohater {
    char imie[MAX_NAME + 1];
    char rasa[MAX_TEXT + 1];
    char klasa[MAX_TEXT + 1];
    int poziom;
    int reputacja;
    StatusBohatera status;
    struct Bohater* nastepny;
} Bohater;

// Prototypy Krok 2
void dodajBohatera(Bohater** glowa);
void wyswietlWszystkich(Bohater* glowa);
void usunBohatera(Bohater** glowa);
void zwolnijPamiec(Bohater* glowa);
const char* statusToString(StatusBohatera s);
void wyczyscBufor();
int pobierzInt();
void pobierzTekst(char* bufor, int rozmiar);

#endif
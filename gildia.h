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

void dodajBohatera(Bohater** glowa);
void edytujBohatera(Bohater* glowa);
void usunBohatera(Bohater** glowa);
void zwolnijPamiec(Bohater* glowa);

void wyswietlWszystkich(Bohater* glowa);
void wyszukajBohatera(Bohater* glowa);
void sortujBohaterow(Bohater** glowa);

void zapiszDoPliku(Bohater* glowa, const char* nazwaPliku);
void wczytajZPliku(Bohater** glowa, const char* nazwaPliku);

const char* statusToString(StatusBohatera s);
void wyczyscBufor();
int pobierzInt();

#endif
#include "gildia.h"

void wyczyscBufor() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int pobierzInt() {
    int liczba;
    while (scanf("%d", &liczba) != 1) {
        printf("Blad! Podaj liczbe: ");
        wyczyscBufor();
    }
    wyczyscBufor();
    return liczba;
}

void pobierzTekst(char* bufor, int rozmiar) {
    if (fgets(bufor, rozmiar, stdin) != NULL) {
        size_t len = strlen(bufor);
        if (len > 0 && bufor[len - 1] == '\n') bufor[len - 1] = '\0';
    } else {
        wyczyscBufor();
    }
}

const char* statusToString(StatusBohatera s) {
    switch(s) {
        case AKTYWNY: return "Aktywny";
        case NA_MISJI: return "Na misji";
        case RANNY: return "Ranny";
        case ZAGINIONY: return "Zaginiony";
        case ZAWIESZONY: return "Zawieszony";
        default: return "Nieznany";
    }
}

void dodajBohatera(Bohater** glowa) {
    Bohater* nowy = (Bohater*)malloc(sizeof(Bohater));
    if (!nowy) { printf("Blad pamieci!\n"); return; }

    printf("\n--- NOWY BOHATER ---\n");
    // Walidacja unikalnosci
    printf("Podaj imie: "); pobierzTekst(nowy->imie, MAX_NAME);
    printf("Podaj rase: "); pobierzTekst(nowy->rasa, MAX_TEXT);
    printf("Podaj klase: "); pobierzTekst(nowy->klasa, MAX_TEXT);
    printf("Poziom: "); nowy->poziom = pobierzInt();
    printf("Reputacja (0-100): "); nowy->reputacja = pobierzInt();
    
    nowy->status = AKTYWNY;
    nowy->nastepny = *glowa;
    *glowa = nowy;
    printf("Dodano!\n");
}

void wyswietlWszystkich(Bohater* glowa) {
    if (!glowa) { printf("Lista pusta.\n"); return; }
    printf("\n%-20s %-15s %-5s %-15s\n", "Imie", "Klasa", "Lvl", "Status");
    while (glowa) {
        printf("%-20s %-15s %-5d %-15s\n", glowa->imie, glowa->klasa, glowa->poziom, statusToString(glowa->status));
        glowa = glowa->nastepny;
    }
}

void usunBohatera(Bohater** glowa) {
    if (!*glowa) { printf("Lista pusta.\n"); return; }
    char szukane[MAX_NAME];
    printf("Imie do usuniecia: "); pobierzTekst(szukane, MAX_NAME);

    Bohater *obecny = *glowa, *poprzedni = NULL;
    while (obecny) {
        if (strcmp(obecny->imie, szukane) == 0) {
            if (obecny->status == NA_MISJI) {
                printf("Blad: Bohater na misji!\n"); return;
            }
            if (!poprzedni) *glowa = obecny->nastepny;
            else poprzedni->nastepny = obecny->nastepny;
            free(obecny);
            printf("Usunieto.\n");
            return;
        }
        poprzedni = obecny;
        obecny = obecny->nastepny;
    }
    printf("Nie znaleziono.\n");
}

void zwolnijPamiec(Bohater* glowa) {
    Bohater* temp;
    while (glowa) {
        temp = glowa;
        glowa = glowa->nastepny;
        free(temp);
    }
}
#include "gildia.h"

void pokazMenu() {
    printf("\n=== GILDIA POSZUKIWACZY PRZYGOD ===\n");
    printf("1. Dodaj nowego bohatera\n");
    printf("2. Wyswietl wszystkich bohaterow\n");
    printf("3. Wyszukaj bohatera\n");
    printf("4. Edytuj bohatera\n");
    printf("5. Usun bohatera\n");
    printf("6. Sortuj liste\n");
    printf("7. Zapisz dane\n");
    printf("8. Wczytaj dane\n");
    printf("0. Wyjscie\n");
    printf("Wybor: ");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Blad: Nie podano nazwy pliku bazy danych w argumencie wywolania.\n");
        printf("Uzycie: %s nazwa_pliku.txt\n", argv[0]);
        return 1;
    }

    const char* nazwaPliku = argv[1];
    Bohater* listaBohaterow = NULL;

    wczytajZPliku(&listaBohaterow, nazwaPliku);

    int wybor;
    do {
        pokazMenu();
        wybor = pobierzInt();

        switch (wybor) {
            case 1: dodajBohatera(&listaBohaterow); break;
            case 2: wyswietlWszystkich(listaBohaterow); break;
            case 3: wyszukajBohatera(listaBohaterow); break;
            case 4: edytujBohatera(listaBohaterow); break;
            case 5: usunBohatera(&listaBohaterow); break;
            case 6: sortujBohaterow(&listaBohaterow); break;
            case 7: zapiszDoPliku(listaBohaterow, nazwaPliku); break;
            case 8: wczytajZPliku(&listaBohaterow, nazwaPliku); break;
            case 0: 
                zapiszDoPliku(listaBohaterow, nazwaPliku);
                zwolnijPamiec(listaBohaterow); 
                printf("Zamykanie systemu Gildii...\n");
                break;
            default: printf("Nieznana opcja.\n");
        }
    } while (wybor != 0);

    return 0;
}
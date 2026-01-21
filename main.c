#include "gildia.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Podaj nazwe pliku jako argument!\n");
        return 1;
    }
    
    Bohater* lista = NULL;
    wczytajZPliku(&lista, argv[1]);
    int wybor;

    do {
        printf("\n1. Dodaj\n2. Wyswietl\n5. Usun\n7. Zapisz\n8. Wczytaj\n0. Wyjscie\nWybor: ");
        wybor = pobierzInt();
        switch(wybor) {
            case 1: dodajBohatera(&lista); break;
            case 2: wyswietlWszystkich(lista); break;
            case 5: usunBohatera(&lista); break;
            case 7: zapiszDoPliku(lista, argv[1]); break;
            case 8: wczytajZPliku(&lista, argv[1]); break;
            case 0: 
                zapiszDoPliku(lista, argv[1]);
                zwolnijPamiec(lista); 
                break;
            default: printf("Opcja niedostepna.\n");
        }
    } while (wybor != 0);
    return 0;
}
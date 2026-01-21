#include "gildia.h"

int main() {
    Bohater* lista = NULL;
    int wybor;

    do {
        printf("\n1. Dodaj\n2. Wyswietl\n5. Usun\n0. Wyjscie\nWybor: ");
        wybor = pobierzInt();
        switch(wybor) {
            case 1: dodajBohatera(&lista); break;
            case 2: wyswietlWszystkich(lista); break;
            case 5: usunBohatera(&lista); break;
            case 0: zwolnijPamiec(lista); break;
            default: printf("Opcja niedostepna w tej wersji.\n");
        }
    } while (wybor != 0);
    return 0;
}
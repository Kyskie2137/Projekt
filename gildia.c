#include "gildia.h"

void pobierzTekst(char* bufor, int rozmiar) {
    if (fgets(bufor, rozmiar, stdin) != NULL) {
        size_t len = strlen(bufor);
        if (len > 0 && bufor[len - 1] == '\n') {
            bufor[len - 1] = '\0';
        }
    } else {
        wyczyscBufor();
    }
}

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
    if (!nowy) {
        printf("Blad alokacji pamieci!\n");
        return;
    }

    printf("\n--- REJESTRACJA NOWEGO BOHATERA ---\n");
    
    while(1) {
        printf("Podaj imie (max %d znakow): ", MAX_NAME);
        pobierzTekst(nowy->imie, MAX_NAME);
        
        int unikalne = 1;
        Bohater* temp = *glowa;
        while(temp) {
            if (strcmp(temp->imie, nowy->imie) == 0) {
                printf("Blad: Bohater o imieniu '%s' juz istnieje!\n", nowy->imie);
                unikalne = 0;
                break;
            }
            temp = temp->nastepny;
        }
        if(unikalne && strlen(nowy->imie) > 0) break;
    }

    printf("Podaj rase: ");
    pobierzTekst(nowy->rasa, MAX_TEXT);
    
    printf("Podaj klase: ");
    pobierzTekst(nowy->klasa, MAX_TEXT);
    
    printf("Podaj poziom doswiadczenia: ");
    nowy->poziom = pobierzInt();
    
    do {
        printf("Podaj reputacje (0-100): ");
        nowy->reputacja = pobierzInt();
    } while (nowy->reputacja < 0 || nowy->reputacja > 100);

    nowy->status = AKTYWNY;
    nowy->nastepny = NULL;

    nowy->nastepny = *glowa;
    *glowa = nowy;
    
    printf("Bohater dodany do Rejestru!\n");
}

void wyswietlWszystkich(Bohater* glowa) {
    if (!glowa) {
        printf("Rejestr jest pusty.\n");
        return;
    }
    printf("\n%-20s %-15s %-15s %-5s %-5s %-15s\n", "Imie", "Rasa", "Klasa", "Lvl", "Rep", "Status");
    printf("--------------------------------------------------------------------------------\n");
    while (glowa) {
        printf("%-20s %-15s %-15s %-5d %-5d %-15s\n", 
               glowa->imie, glowa->rasa, glowa->klasa, glowa->poziom, glowa->reputacja, statusToString(glowa->status));
        glowa = glowa->nastepny;
    }
}

void usunBohatera(Bohater** glowa) {
    if (!*glowa) {
        printf("Rejestr pusty.\n");
        return;
    }

    char szukaneImie[MAX_NAME];
    printf("Podaj imie bohatera do usuniecia: ");
    pobierzTekst(szukaneImie, MAX_NAME);

    Bohater *obecny = *glowa;
    Bohater *poprzedni = NULL;

    while (obecny != NULL) {
        if (strcmp(obecny->imie, szukaneImie) == 0) {
            if (obecny->status == NA_MISJI) {
                printf("BLAD: Nie mozna usunac bohatera '%s', poniewaz jest NA MISJI!\n", obecny->imie);
                return;
            }

            if (poprzedni == NULL) {
                *glowa = obecny->nastepny;
            } else {
                poprzedni->nastepny = obecny->nastepny;
            }
            free(obecny);
            printf("Bohater usuniety z Rejestru.\n");
            return;
        }
        poprzedni = obecny;
        obecny = obecny->nastepny;
    }
    printf("Nie znaleziono bohatera o takim imieniu.\n");
}

void edytujBohatera(Bohater* glowa) {
    char szukaneImie[MAX_NAME];
    printf("Podaj imie bohatera do edycji: ");
    pobierzTekst(szukaneImie, MAX_NAME);

    while (glowa) {
        if (strcmp(glowa->imie, szukaneImie) == 0) {
            printf("Edytujesz bohatera: %s\n", glowa->imie);
            printf("1. Zmien poziom\n2. Zmien reputacje\n3. Zmien status\nWYBOR: ");
            int opcja = pobierzInt();
            
            switch(opcja) {
                case 1:
                    printf("Nowy poziom: ");
                    glowa->poziom = pobierzInt();
                    break;
                case 2:
                    printf("Nowa reputacja (0-100): ");
                    glowa->reputacja = pobierzInt();
                    break;
                case 3:
                    printf("Statusy: 0-Aktywny, 1-Na Misji, 2-Ranny, 3-Zaginiony, 4-Zawieszony\nWybor: ");
                    int st = pobierzInt();
                    if (st >= 0 && st <= 4) glowa->status = (StatusBohatera)st;
                    break;
                default:
                    printf("Niepoprawna opcja.\n");
            }
            printf("Dane zaktualizowane.\n");
            return;
        }
        glowa = glowa->nastepny;
    }
    printf("Nie znaleziono bohatera.\n");
}

void wyszukajBohatera(Bohater* glowa) {
    printf("Wyszukiwanie:\n1. Po fragmencie imienia (tekst)\n2. Powyzej poziomu (liczba)\nWybor: ");
    int opcja = pobierzInt();

    if (opcja == 1) {
        char fraza[MAX_NAME];
        printf("Podaj fragment imienia (prefiks): ");
        pobierzTekst(fraza, MAX_NAME);
        printf("\nWyniki wyszukiwania:\n");
        while(glowa) {
            if (strncmp(glowa->imie, fraza, strlen(fraza)) == 0) {
                printf("- %s (Lvl: %d, %s)\n", glowa->imie, glowa->poziom, glowa->klasa);
            }
            glowa = glowa->nastepny;
        }
    } else if (opcja == 2) {
        printf("Podaj minimalny poziom: ");
        int minLvl = pobierzInt();
        printf("\nBohaterowie z poziomem >= %d:\n", minLvl);
        while(glowa) {
            if (glowa->poziom >= minLvl) {
                printf("- %s (Lvl: %d)\n", glowa->imie, glowa->poziom);
            }
            glowa = glowa->nastepny;
        }
    }
}

void sortujBohaterow(Bohater** glowa) {
    if (!*glowa) return;
    
    printf("Sortowanie:\n1. Po imieniu (A-Z)\n2. Po reputacji (malejaco)\nWybor: ");
    int opcja = pobierzInt();
    
    int zamiana;
    Bohater *ptr1;
    Bohater *lptr = NULL;

    do {
        zamiana = 0;
        ptr1 = *glowa;

        while (ptr1->nastepny != lptr) {
            int warunek = 0;
            if (opcja == 1) {
                if (strcmp(ptr1->imie, ptr1->nastepny->imie) > 0) warunek = 1;
            } else {
                if (ptr1->reputacja < ptr1->nastepny->reputacja) warunek = 1;
            }

            if (warunek) {
                char tImie[MAX_NAME], tRasa[MAX_TEXT], tKlasa[MAX_TEXT];
                int tLvl, tRep; StatusBohatera tStat;
                
                strcpy(tImie, ptr1->imie); strcpy(tRasa, ptr1->rasa); strcpy(tKlasa, ptr1->klasa);
                tLvl = ptr1->poziom; tRep = ptr1->reputacja; tStat = ptr1->status;
                
                strcpy(ptr1->imie, ptr1->nastepny->imie);
                strcpy(ptr1->rasa, ptr1->nastepny->rasa);
                strcpy(ptr1->klasa, ptr1->nastepny->klasa);
                ptr1->poziom = ptr1->nastepny->poziom;
                ptr1->reputacja = ptr1->nastepny->reputacja;
                ptr1->status = ptr1->nastepny->status;
                
                strcpy(ptr1->nastepny->imie, tImie);
                strcpy(ptr1->nastepny->rasa, tRasa);
                strcpy(ptr1->nastepny->klasa, tKlasa);
                ptr1->nastepny->poziom = tLvl;
                ptr1->nastepny->reputacja = tRep;
                ptr1->nastepny->status = tStat;

                zamiana = 1;
            }
            ptr1 = ptr1->nastepny;
        }
        lptr = ptr1;
    } while (zamiana);
    
    printf("Lista posortowana.\n");
}

void zapiszDoPliku(Bohater* glowa, const char* nazwaPliku) {
    FILE* fp = fopen(nazwaPliku, "w");
    if (!fp) {
        printf("Blad otwarcia pliku do zapisu!\n");
        return;
    }
    
    while (glowa) {
        fprintf(fp, "%s|%s|%s|%d|%d|%d\n", 
                glowa->imie, glowa->rasa, glowa->klasa, 
                glowa->poziom, glowa->reputacja, (int)glowa->status);
        glowa = glowa->nastepny;
    }
    fclose(fp);
    printf("Dane zapisano do pliku: %s\n", nazwaPliku);
}

void wczytajZPliku(Bohater** glowa, const char* nazwaPliku) {
    FILE* fp = fopen(nazwaPliku, "r");
    if (!fp) {
        printf("Nie znaleziono pliku danych (%s). Tworzenie nowej bazy.\n", nazwaPliku);
        return;
    }
    
    zwolnijPamiec(*glowa);
    *glowa = NULL;
    
    char bufor[512];
    while (fgets(bufor, sizeof(bufor), fp)) {
        Bohater* nowy = (Bohater*)malloc(sizeof(Bohater));
        int stTemp;
        
        if (sscanf(bufor, "%[^|]|%[^|]|%[^|]|%d|%d|%d", 
                   nowy->imie, nowy->rasa, nowy->klasa, 
                   &nowy->poziom, &nowy->reputacja, &stTemp) == 6) {
            
            nowy->status = (StatusBohatera)stTemp;
            nowy->nastepny = *glowa;
            *glowa = nowy;
        } else {
            free(nowy);
        }
    }
    fclose(fp);
    printf("Wczytano dane z pliku.\n");
}

void zwolnijPamiec(Bohater* glowa) {
    Bohater* temp;
    while (glowa) {
        temp = glowa;
        glowa = glowa->nastepny;
        free(temp);
    }
}
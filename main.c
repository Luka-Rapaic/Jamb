#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int coo = 1;
unsigned long x;

int in_range(int number, int start, int end) {
    if (number >= start && number < end) {
        return 1;
    }
    return 0;
}

int in(int Array[], int ArrayLength, int Element) {
    for (int i = 0; i < ArrayLength; i++) {
        if (Array[i] == Element) {
            return 1;
        }
    }
    return 0;
}

int u_matrici_print(int Matrica[], int DuzinaMatrice, int Vrsta, int Kolona) {
    if (coo == 1) {
        for (int i = 0; i < DuzinaMatrice / 3; i++) {
            if (Matrica[i*3] == Vrsta && Matrica[i*3+1] == Kolona) {
                return Matrica[i*3+2];
            }
        }
        return -1;
    } else {
        return Matrica[Kolona*11 + Vrsta];
    }
}

int u_matrici(int Matrica[], int DuzinaMatrice, int Vrsta, int Kolona) {
    int vrednost = u_matrici_print(Matrica, DuzinaMatrice, Vrsta, Kolona);
    return vrednost != -1 ? vrednost : 0;
}

void set_seed(unsigned long int seed){
    x = seed;
}

double lkg() {
    x = ((429493445 * x + 907633385) % 4294967296);
    return x/4294967296.;
}

int random() {
    int a = lkg()*324;
    return a%6+1;
}

int UkupanBrojBodova(int Matrica[], int DuzinaMatrice) {
    int zbir = 0;
    for (int i = 0; i < 3; i++) {
        zbir += u_matrici(Matrica, DuzinaMatrice, 10, i);
    }
    return zbir;
}

int* formiraj_prazan_talon() {
    int* Matrica = (int *)malloc(9 * sizeof(int));
    for (int i = 0; i < 3; i++) {
        Matrica[i*3] = 10;
        Matrica[i*3+1] = i;
        Matrica[i*3+2] = 0;
    }
    return Matrica;
}

void prikazi_talon(int Matrica[], int DuzinaMatrice) {
    int sume[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            sume[i] += u_matrici(Matrica, DuzinaMatrice, j, i);
        }
    }
    printf("|%s|%s|%s|%s|\n", "   JAMB  ", " Na dole ", " Na gore ", "  Rucna  ");
    printf("|---------|---------|---------|---------|\n");
    for (int i = 0; i < 11; i++) {
        if (i == 0) {
            printf("|%s", "      1  ");
        } else if (i == 1) {
            printf("|%s", "      2  ");
        } else if (i == 2) {
            printf("|%s", "      3  ");
        } else if (i == 3) {
            printf("|%s", "      4  ");
        } else if (i == 4) {
            printf("|%s", "      5  ");
        } else if (i == 5) {
            printf("|%s", "      6  ");
        } else if (i == 6) {
            printf("|%s", "  Kenta  ");
        } else if (i == 7) {
            printf("|%s", "    Ful  ");
        } else if (i == 8) {
            printf("|%s", "  Poker  ");
        } else if (i == 9) {
            printf("|%s", "   Jamb  ");
        } else {
            printf("|%s", "      S  ");
        }
        for (int j = 0; j < 3; j++){
            int vrednost = u_matrici_print(Matrica, DuzinaMatrice, i, j);
            if (vrednost == -1) {
                printf("|         ");
            } else {
                printf("|%6d   ", vrednost);
            }
        }
        printf("|\n");
        if (i == 5) {
            printf("|---------|---------|---------|---------|\n");
            printf("|%s|%6d   |%6d   |%6d   |\n", "      S  ", sume[0], sume[1], sume[2]);
            printf("|---------|---------|---------|---------|\n");
        } else if (i == 9) {
            printf("|---------|---------|---------|---------|\n");
        }
    }
    printf("\n");
}

void popuni_polje(int matrica[], int* duzina_matrice, int vrsta, int kolona, int vrednost) {
    if (coo == 1) {
        if (vrsta == 10) {
            for (int i = 0; i < *duzina_matrice / 3; i++) {
                if (matrica[i*3] == vrsta && matrica[i*3+1] == kolona) {
                    matrica[i*3+2] += vrednost;
                    return;
                }
            }
        }
        *duzina_matrice = *duzina_matrice + 3;
        if (*duzina_matrice == 33) {
            int nova_matrica[33];
            for (int i = 0; i < 33; i++) {
                nova_matrica[i] = -1;
            }
            nova_matrica[kolona*11+vrsta] = vrednost;
            for (int i = 0; i < 10; i++) {
                int a = matrica[i*3], b = matrica[i*3+1], c = matrica[i*3+2];
                nova_matrica[b*11+a] = c;
            }
            matrica = realloc(matrica, *duzina_matrice*sizeof(int));
            int i = 0;
            while (i < 33) {
                matrica[i] = nova_matrica[i];
                i++;
            }
            coo = 0;
            return;
        }

        matrica = realloc(matrica, *duzina_matrice*sizeof(int));
        int i = *duzina_matrice / 3 - 2;
        while ((matrica[i*3] > vrsta || matrica[i*3+1] > kolona) && i >= 0) {
            matrica[(i+1)*3] = matrica[i*3];
            matrica[(i+1)*3+1] = matrica[i*3+1];
            matrica[(i+1)*3+2] = matrica[i*3+2];
            i--;
        }
        matrica[++i*3] = vrsta;
        matrica[i*3+1] = kolona;
        matrica[i*3+2] = vrednost;
    }
    else {
        if (vrsta == 10) {
            matrica[kolona*11+vrsta] += vrednost;
            return;
        }
        matrica[kolona*11+vrsta] = vrednost;
    }
}

int prazno_polje(int Matrica[], int DuzinaMatrice, int Vrsta, int Kolona) {
    if (coo == 1) {
        for (int i = 0; i < DuzinaMatrice / 3; i++) {
            if (Matrica[i*3] == Vrsta && Matrica[i*3+1] == Kolona) {
                return 0;
            }
        }
        return 1;
    }
    else {
        if (Matrica[Kolona*11 + Vrsta] == -1) {
            return 1;
        }
        return 0;
    }
}

int je_kenta(int Kockice[]) {
    for (int i = 1; i < 6; i++) {
        if (in(Kockice, 5, i) == 0) {
            for(int j = 2; j < 7; j++) {
                if (in(Kockice, 5, j) == 0) {
                    return 0;
                }
            }
            return 1;
        }
    }
    return 1;
}

int je_ful(int Kockice[]) {
    int Prebrojeno[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        Prebrojeno[Kockice[i]-1]++;
    }
    if (in(Prebrojeno, 6, 2) && in(Prebrojeno, 6, 3)) {
        return 1;
    }
    return 0;
}

int je_poker(int Kockice[]) {
    int Prebrojeno[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        Prebrojeno[Kockice[i]-1]++;
    }
    if (in(Prebrojeno, 6, 4)){
        return 1;
    }
    return 0;
}

int je_jamb(int Kockice[]) {
    int Prebrojeno[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        Prebrojeno[Kockice[i]-1]++;
    }
    if (in(Prebrojeno, 6, 5)){
        return 1;
    }
    return 0;
}

int vrednost_broja(int Kockice[], int Broj) {
    int Prebrojeno[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        Prebrojeno[Kockice[i]-1]++;
    }
    return Broj*Prebrojeno[Broj-1];
}

int kenta(int Bacanje) {
    switch (Bacanje) {
        case 0:
            return 66;
        case 1:
            return 56;
        default:
            return 46;
    }
}

int poker(int Kockice[]) {
    int Prebrojeno[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        Prebrojeno[Kockice[i]-1]++;
    }
    int broj = 1;
    while (Prebrojeno[broj-1] != 4) {
        broj++;
    }
    return broj*4 + 40;
}

int ful(int Kockice[]){
    int Prebrojeno[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        Prebrojeno[Kockice[i]-1]++;
    }
    int i = 0;
    int vrednost = 0;
    while (i < 6) {
        if (Prebrojeno[i] != 0) {
            vrednost += Prebrojeno[i]*(i+1);
        }
        i++;
    }
    return vrednost + 30;
}

int jamb(int Kockice[]){
    return Kockice[0]*5 + 50;
}

int count(int Array[], int ArrayLength, int Broj) {
    int counter = 0;
    for (int i = 0; i < ArrayLength; i++) {
        if (Array[i] == Broj) {
            counter++;
        }
    }
    return counter;
}

int izracunaj_vrednost(int Kockice[], int Vrsta, int Kolona, int Bacanje) {
    if (Kolona == 2 && Bacanje != 0) {
        printf("\nKolona rucna moze biti popunjena samo nakon prvog bacanja!");
        return 0;
    }
    switch (Vrsta) {
        case 0:
            return vrednost_broja(Kockice, 1);
        case 1:
            return vrednost_broja(Kockice, 2);
        case 2:
            return vrednost_broja(Kockice, 3);
        case 3:
            return vrednost_broja(Kockice, 4);
        case 4:
            return vrednost_broja(Kockice, 5);
        case 5:
            return vrednost_broja(Kockice, 6);
        case 6:
            if (je_kenta(Kockice)) {
                return kenta(Bacanje);
            }
            return 0;
        case 7:
            if (je_ful(Kockice)) {
                return ful(Kockice);
            }
            return 0;
        case 8:
            if (je_poker(Kockice)) {
                return poker(Kockice);
            }
            return 0;
        default:
            if (je_jamb(Kockice)) {
                return jamb(Kockice);
            }
            return 0;
    }
}

int validan_potez(int Kockice[], int Matrica[], int DuzinaMatrice, int Vrsta, int Kolona, int Bacanje) {
    switch(Kolona) {
        case 0:
            if (Vrsta == 0) {
                if (prazno_polje(Matrica, DuzinaMatrice, Vrsta, Kolona)) {
                    break;
                }
                return 0;
            }
            if (!prazno_polje(Matrica, DuzinaMatrice, Vrsta, Kolona) || prazno_polje(Matrica, DuzinaMatrice, Vrsta-1, Kolona)) {
                return 0;
            }
            break;
        case 1:
            if (Vrsta == 9) {
                if (prazno_polje(Matrica, DuzinaMatrice, Vrsta, Kolona)){
                    break;
                }
                return 0;
            }
            if (!prazno_polje(Matrica, DuzinaMatrice, Vrsta, Kolona) || prazno_polje(Matrica, DuzinaMatrice, Vrsta+1, Kolona)) {
                return 0;
            }
            break;
        default:
            if (prazno_polje(Matrica, DuzinaMatrice, Vrsta, Kolona)) {
                break;
            }
            return 0;
    }
    return 1;
}

int upisi_potez(int Matrica[], int* DuzinaMatrice, int Kockice[], int Bacanje) {
    char komanda[14];
    int Vrsta, Kolona, Offset, Vrednost;
    fgets(komanda, 15, stdin);
    fflush(stdin);
    if (strstr(komanda, "Na dole ") - komanda == 0) {
        Kolona = 0;
        Offset = 8;
    }
    else if (strstr(komanda, "Na gore ") - komanda == 0) {
        Kolona = 1;
        Offset = 8;
    }
    else if(strstr(komanda, "Rucna ") - komanda == 0) {
        Kolona = 2;
        Offset = 6;
    }
    else {
        return 0;
    }

    if (strstr(komanda, "kenta\n") - &komanda[Offset] == 0) {
        Vrsta = 6;
    }
    else if (strstr(komanda, "ful\n") - &komanda[Offset] == 0) {
        Vrsta = 7;
    }
    else if (strstr(komanda, "poker\n") - &komanda[Offset] == 0) {
        Vrsta = 8;
    }
    else if (strstr(komanda, "jamb\n") - &komanda[Offset] == 0) {
        Vrsta = 9;
    }
    else if (strcmp(&komanda[Offset], "1\n") == 0) {
        Vrsta = 0;
    }
    else if (strcmp(&komanda[Offset], "2\n") == 0) {
        Vrsta = 1;
    }
    else if (strcmp(&komanda[Offset], "3\n") == 0) {
        Vrsta = 2;
    }
    else if (strcmp(&komanda[Offset], "4\n") == 0) {
        Vrsta = 3;
    }
    else if (strcmp(&komanda[Offset], "5\n") == 0) {
        Vrsta = 4;
    }
    else if (strcmp(&komanda[Offset], "6\n") == 0) {
        Vrsta = 5;
    }
    else {
        return 0;
    }

    if (validan_potez(Kockice, Matrica, *DuzinaMatrice, Vrsta, Kolona, Bacanje)) {
        Vrednost = izracunaj_vrednost(Kockice, Vrsta, Kolona, Bacanje);
        if (Vrednost == 0) {
            char Potvrda[4];
            while (1) {
                printf("\nOvo polje bice precrtano!\nDa li zelite da nastavite?\n");
                fgets(Potvrda, 4, stdin);
                fflush(stdin);
                printf("\n");
                if (strcmp(Potvrda, "Da\n") == 0) {
                    popuni_polje(Matrica, DuzinaMatrice, Vrsta, Kolona, Vrednost);
                    popuni_polje(Matrica, DuzinaMatrice, 10, Kolona, Vrednost);
                    return 1;
                }
                else if (strcmp(Potvrda, "Ne\n") == 0) {
                    return -1;
                }
            }
        } else {
            popuni_polje(Matrica, DuzinaMatrice, Vrsta, Kolona, Vrednost);
            popuni_polje(Matrica, DuzinaMatrice, 10, Kolona, Vrednost);
            return 1;
        }
    }
    else {
        return 0;
    }
}

void baci_kockice (int Kockice[], int Spisak[], int DuzinaSpiska) {
    for (int i = 0; i < DuzinaSpiska; i++) {
        Kockice[Spisak[i]-1] = random();
    }
}

void prikazi_bacanje(int Kockice[]) {
    printf("Rezultati bacanja:\n");
    for (int i = 0; i < 5; i++) {
        printf("Kocka %d: %d\n", i+1, Kockice[i]);
    }
    printf("\n");
}

void odigraj_potez (int Matrica[], int *DuzinaMatrice) {
    int Kockice[5], Spisak[5] = {1, 2, 3, 4, 5}, DuzinaSpiska = 5, Bacanje = 0, dalje = 0;
    char Komanda[11];
    while (dalje != 1) {
        baci_kockice(Kockice, Spisak, DuzinaSpiska);
        system("cls");
        prikazi_talon(Matrica, *DuzinaMatrice);
        printf("Dobili ste sledece brojeve na kockama:\n");
        printf("Kocka 1: %d\nKocka 2: %d\nKocka 3: %d\nKocka 4: %d\nKocka 5: %d\n\n", Kockice[0], Kockice[1], Kockice[2], Kockice[3], Kockice[4]);
        if (Bacanje != 2) {
            printf("1: Baci kockice ponovo\n2: Popuni polje\nOdaberite jednu od ponudjenih opcija...\n");
        }
        while (1){
            if (Bacanje != 2) {
                fgets(Komanda, 3, stdin);
                fflush(stdin);
                printf("\n");
            } else {
                Komanda[0] = '2';
                Komanda[1] = '\n';
                Komanda[2] = '\0';
            }
            if (strcmp(Komanda, "2\n") == 0) {
                dalje = 1;
                break;
            }
            else if (strcmp(Komanda, "1\n") == 0) {
                while (1) {
                    printf("Koje kocke biste zeleli da bacite ponovo?\n");
                    fgets(Komanda, 11, stdin);
                    fflush(stdin);
                    printf("\n");
                    if (strcmp(Komanda, "Sve\n") == 0) {
                        for (int i = 0; i < 5; i++) {
                            Spisak[i] = i + 1;
                        }
                        DuzinaSpiska = 5;
                        Bacanje++;
                        break;
                    }
                    else {
                        int counter = 0;
                        DuzinaSpiska = 0;
                        for (int i = 0; i < strlen(Komanda); i++) {
                            if (in_range(Komanda[i], 49, 54)) {
                                counter++;
                            }
                            else if (Komanda[i] == ' ' || Komanda[i] == '\n') {
                                counter = 0;
                            }
                            else {
                                counter = 2;
                            }
                            if (counter == 1) {
                                char StringForATOI[2] = {Komanda[i], '\0'};
                                Spisak[DuzinaSpiska] = atoi(StringForATOI);
                                DuzinaSpiska++;
                            }
                            if (counter == 2) {
                                printf("Unete vrednosti mogu biti samo brojevi izmedju 1 i 5!\n\n");
                                break;
                            }
                        }
                        if (counter != 2) {
                            Bacanje++;
                            break;
                        }
                    }
                }
                break;
            }
            else {
                printf("Unete vrednosti mogu biti samo brojevi 1 i 2!\n");
            }
        }
    }
    while (1) {
        system("cls");
        prikazi_talon(Matrica, *DuzinaMatrice);
        prikazi_bacanje(Kockice);
        printf("Unesite naziv polja koje biste zeleli da popunite:\n");
        dalje = upisi_potez(Matrica, DuzinaMatrice, Kockice, Bacanje);
        if (dalje == 1) {
            break;
        } else if (dalje == 0) {
            printf("\nNeispravan naziv polja!\nNaziv polja mozete dobiti kombinovanjem naziva kolone i vrste!\n");
            fgets(Komanda, 2, stdin);
            fflush(stdin);
        }
        /*TODO Ovaj deo funkcije treba jos testirati, ne deluje kao da je sve kako treba!*/
    }
    /* Odavde treba da nastavim da pisem, treba dati igracu izbor koje polje hoce da popuni, funkcija za to vec postoji*/
}

int PronadjiPraznaPolja(int Matrica[], int DuzinaMatrice, int PraznaPolja[]) {
    int counter = 0;
    for (int i = 0; i < 10; i++) {
        if (u_matrici_print(Matrica, DuzinaMatrice, i, 0) == -1) {
            PraznaPolja[counter++] = i;
            PraznaPolja[counter++] = 0;
            break;
        }
    }
    for (int i = 9; i > -1; i--) {
        if (u_matrici_print(Matrica, DuzinaMatrice, i, 1) == -1) {
            PraznaPolja[counter++] = i;
            PraznaPolja[counter++] = 1;
            break;
        }
    }
    for (int i = 9; i > -1; i--) {
        /* mozda bude trebalo*/
    }
    /*if (PraznaPolja[0] == -1) {
        PraznaPolja[0] = PraznaPolja[2];
        PraznaPolja[1] = PraznaPolja[3];
    }
    if (PraznaPolja[2] == -1) {
        PraznaPolja[2] = PraznaPolja[0];
        PraznaPolja[3] = PraznaPolja[1];
    }*/
}

int Bacanje_kompjuter(int Kockice[], int Vrsta, int Bacanje) {
    int Potrebno1, Potrebno2;
    switch (Vrsta) {
        case 9:
            Potrebno1 = 5; Potrebno2 = 0;
            break;
        case 8:
            Potrebno1 = 4; Potrebno2 = 0;
            break;
        case 7:
            Potrebno1 = 3; Potrebno2 = 2;
            break;
        case 6:
            Potrebno1 = -1;
            break;
        default:
            Potrebno1 = -2; Potrebno2 = Vrsta+1;
    }
    if (Potrebno1 == -1) {
        while (1) {
            int Prebrojeno[6] = {0, 0, 0, 0, 0, 0};
            for (int i = 0; i < 5; i++) {
                Prebrojeno[Kockice[i] - 1]++;
            }
            int counter = 0;
            for (int i = 0; i < 6; i++) {
                if (Prebrojeno[i] == 1) {
                    counter++;
                    if (counter == 5) {
                        return 1;
                    }
                } else {
                    counter = 0;
                }
            }
            if (Bacanje == 2) {
                return 0;
            }
            if (Prebrojeno[0] != 0 && Prebrojeno[5] != 0) {
                Prebrojeno[0]++;
            }
            for (int i = 0; i < 5; i++) {
                if (Prebrojeno[Kockice[i]-1] > 1) {
                    Prebrojeno[Kockice[i]-1]--;
                    Kockice[i] = random();
                }
            }
            Bacanje++;
        }
    } else if (Potrebno1 == -2) {
        Potrebno1 = 0;
        for (int i = 0; i < 5; i++) {
            if (Kockice[i] != Potrebno2) {
                Kockice[i] = random();
            } else {
                Potrebno1++;
            }
        }
        if (Potrebno1 == 5) {
            return 1;
        }
        return 0;
    } else {
        while (1) {
            int Prebrojeno[6] = {0, 0, 0, 0, 0, 0};
            for (int i = 0; i < 5; i++) {
                Prebrojeno[Kockice[i] - 1]++;
            }
            int Max1[2] = {0, 0}; /*Prva vrednost je broj na kockici, druga je broj pojavljivanja*/
            int Max2[2] = {0, 0};
            for (int i = 5; i > -1; i--) {
                if (Prebrojeno[i] > Max1[1]) {
                    Max1[0] = i + 1;
                    Max1[1] = Prebrojeno[i];
                }
            }
            if (Max1[1] > Potrebno1) {
                Max1[1] = Potrebno1;
            }
            if (Potrebno2 != 0) {
                for (int i = 5; i > -1; i--) {
                    if (Prebrojeno[i] > Max2[1] && i != Max1[0] - 1) {
                        Max2[0] = i + 1;
                        Max2[1] = Prebrojeno[i];
                    }
                }
                if (Max2[1] > Potrebno2) {
                    Max2[1] = Potrebno2;
                }
            }
            if (Max1[1] == Potrebno1 && Max2[1] == Potrebno2) {
                return 1;
            } else if (Bacanje == 2) {
                return 0;
            }
            for (int i = 0; i < 5; i++) {
                if (Max1[0] == Kockice[i] && Max1[1] != 0) {
                    Max1[1] = Max1[1] - 1;
                } else if (Max2[0] == Kockice[i] && Max2[1] != 0) {
                    Max2[1] = Max2[1] - 1;
                } else {
                    Kockice[i] = random();
                }
            }
            Bacanje++;
        }
    }
}

int TestBacanje(int KockiceOriginal[], int Vrsta, int Bacanje) {
    int Kockice[5];
    for (int i = 0; i < 5; i++) {
        Kockice[i] = KockiceOriginal[i];
    }
    return Bacanje_kompjuter(Kockice, Vrsta, Bacanje);
}

float Sansa(int Kockice[], int Vrsta, int Bacanje) {
    float UslovIspunjen = 0;
    for (int i = 0; i <200; i++) {
        if (TestBacanje(Kockice, Vrsta, Bacanje)) {
            UslovIspunjen++;
        }
    }
    return UslovIspunjen/200;
}

void KompjuterPopuni(int Matrica[], int* DuzinaMatrice, int Kockice[], int Vrsta, int Kolona, int Bacanje) {
    int Vrednost = izracunaj_vrednost(Kockice, Vrsta, Kolona, Bacanje);
    popuni_polje(Matrica, DuzinaMatrice, Vrsta, Kolona, Vrednost);
    popuni_polje(Matrica, DuzinaMatrice, 10, Kolona, Vrednost);
}

int KockaKojaSeCescePojavljuje(int Kockice[], int Kocka1, int Kocka2) {
    int Prebrojeno[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        Prebrojeno[Kockice[i] - 1]++;
    }
    if (Prebrojeno[Kocka2-1] > Prebrojeno[Kocka1-1]) {
        return Kocka2;
    }
    return Kocka1;
}

void pomoc_prijatelja_bacanja(int Matrica[], int* DuzinaMatrice, int Kockice[], int PraznaPolja[4]) {
    int nebitno;
    int BacajZa[2];
    for (int Bacanje = 0; Bacanje < 2; Bacanje++) {
        if (PraznaPolja[0] == -1) {
            BacajZa[0] = PraznaPolja[2];
            BacajZa[1] = PraznaPolja[3];
        } else if (PraznaPolja[2] == -1) {
            BacajZa[0] = PraznaPolja[0];
            BacajZa[1] = PraznaPolja[1];
        } else if (in_range(PraznaPolja[0], 0, 6) && in_range(PraznaPolja[2], 6, 10)) {
            if (Sansa(Kockice, PraznaPolja[2], Bacanje) > 0.35) {
                BacajZa[0] = PraznaPolja[2];
                BacajZa[1] = PraznaPolja[3];
            } else {
                BacajZa[0] = PraznaPolja[0];
                BacajZa[1] = PraznaPolja[1];
            }
        } else if (in_range(PraznaPolja[0], 0, 6) && in_range(PraznaPolja[2], 0, 6)) {
            int NajcescaKocka = KockaKojaSeCescePojavljuje(Kockice, PraznaPolja[0] + 1, PraznaPolja[2] + 1);
            if (NajcescaKocka == PraznaPolja[2] + 1) {
                BacajZa[0] = PraznaPolja[2];
                BacajZa[1] = PraznaPolja[3];
            } else {
                BacajZa[0] = PraznaPolja[0];
                BacajZa[1] = PraznaPolja[1];
            }
        } else if (in_range(PraznaPolja[0], 6, 10) && in_range(PraznaPolja[2], 6, 10)) {
            float Sansa1 = Sansa(Kockice, PraznaPolja[0], Bacanje);
            float Sansa2 = Sansa(Kockice, PraznaPolja[2], Bacanje);
            if (Sansa1 > Sansa2) {
                BacajZa[0] = PraznaPolja[0];
                BacajZa[1] = PraznaPolja[1];
            } else {
                BacajZa[0] = PraznaPolja[2];
                BacajZa[1] = PraznaPolja[3];
            }
        } else {
            if (Sansa(Kockice, PraznaPolja[0], Bacanje) > 0.35) {
                BacajZa[0] = PraznaPolja[0];
                BacajZa[1] = PraznaPolja[1];
            } else {
                BacajZa[0] = PraznaPolja[2];
                BacajZa[1] = PraznaPolja[3];
            }
        }
        if (Sansa(Kockice, BacajZa[0], Bacanje) == 1) {
            KompjuterPopuni(Matrica, DuzinaMatrice, Kockice, BacajZa[0], BacajZa[1], Bacanje);
            return;
        } else {
            Bacanje_kompjuter(Kockice, BacajZa[0], Bacanje);
        }
        printf("%d %d\n", BacajZa[0], BacajZa[1]);
        printf("%d %d %d %d %d\n", Kockice[0], Kockice[1], Kockice[2], Kockice[3], Kockice[4]);
    }
    int vrednost1 = izracunaj_vrednost(Kockice, PraznaPolja[0], PraznaPolja[1], 2);
    int vrednost2 = izracunaj_vrednost(Kockice, PraznaPolja[2], PraznaPolja[3], 2);
    if (vrednost1 == vrednost2) {
        KompjuterPopuni(Matrica, DuzinaMatrice, Kockice, BacajZa[0], BacajZa[1], 2);
        return;
    } else if (vrednost1 > vrednost2) {
        KompjuterPopuni(Matrica, DuzinaMatrice, Kockice, PraznaPolja[0], PraznaPolja[1], 2);
        return;
    } else {
        KompjuterPopuni(Matrica, DuzinaMatrice, Kockice, PraznaPolja[2], PraznaPolja[3], 2);
        return;
    }
}

void pomoc_prijatelja(int Matrica[], int* DuzinaMatrice) {
    int Kockice[5], Spisak[5] = {1, 2, 3, 4, 5}, DuzinaSpiska = 5, Dalje = 0, Vrednost;
    int PraznaPolja[4] = { -1, -1, -1, -1 };
    PronadjiPraznaPolja(Matrica, *DuzinaMatrice, PraznaPolja);
    baci_kockice(Kockice, Spisak, DuzinaSpiska);
    if ((je_jamb(Kockice) || PraznaPolja[0] == -1) && prazno_polje(Matrica, *DuzinaMatrice, 9, 2)) {
        KompjuterPopuni(Matrica, DuzinaMatrice, Kockice, 9, 2, 0);
        return;
    } else if((je_poker(Kockice) || PraznaPolja[0] == -1) && prazno_polje(Matrica, *DuzinaMatrice, 8, 2)) {
        KompjuterPopuni(Matrica, DuzinaMatrice, Kockice, 8, 2, 0);
        return;
    } else if((je_ful(Kockice) || PraznaPolja[0] == -1) && prazno_polje(Matrica, *DuzinaMatrice, 7, 2)) {
        KompjuterPopuni(Matrica, DuzinaMatrice, Kockice, 7, 2, 0);
        return;
    } else if((je_kenta(Kockice) || PraznaPolja[0] == -1) && prazno_polje(Matrica, *DuzinaMatrice, 6, 2)) {
        KompjuterPopuni(Matrica, DuzinaMatrice, Kockice, 6, 2, 0);
        return;
    } else {
        int Pojavljivanja[6], Najvise[2];
        for (int i = 0; i < 6; i++) {
            Pojavljivanja[i] = count(Kockice, 5, i+1);
        }
        do {
            Najvise[0] = 0;
            Najvise[1] = 0;
            for (int i = 0; i < 6; i++) {
                if (Pojavljivanja[i] >= Najvise[0]) {
                    Najvise[0] = Pojavljivanja[i];
                    Najvise[1] = i;
                }
            }
            Pojavljivanja[Najvise[1]] = 0;
            if (prazno_polje(Matrica, *DuzinaMatrice, Najvise[1], 2)) {
                KompjuterPopuni(Matrica, DuzinaMatrice, Kockice, Najvise[1], 2, 0);
                return;
            }
        } while (Najvise[0] != 0 || PraznaPolja[0] == -1);
    }
    printf("%d %d %d %d %d\n", Kockice[0], Kockice[1], Kockice[2], Kockice[3], Kockice[4]);
    pomoc_prijatelja_bacanja(Matrica, DuzinaMatrice, Kockice, PraznaPolja);
}

int main() {
    set_seed(time(NULL));
    int* Matrica = formiraj_prazan_talon();
    int DuzinaMatrice = 9, BrojPopunjenihPolja = 0;
    char Komanda[3];
    printf("Uputstvo!\n\nKako bi program bio pravilno prikazan potrebno ga je pokrenuti kao .exe datoteku!\n\nPrilikom odabira kockica za bacanje, format unosa treba biti oblika:\n\{}? \{}? {}? \{}? \{}?\n\nUkoliko zelite ponovo da bacite svih pet kockica, to mozete uciniti i koriscenjem komande\n\"Sve\"\n\nSve pisane komande moraju biti zadate velikim pocetnim slovom!\n\nPrilikom izbora polja u koje zelite da upisete vrednost morate navesti naziv kolone,\na zatim i naziv vrste u koju zelite vrednost da upisete\n\nNa primer:\nRucna kenta\n\nNazivi kolona ne menjaju se po padezima!\n\nNe prekidajte komande kako ne biste izazvali mogucu gresku!\n\nDa biste nastavili, pritisnite enter...");
    fgets(Komanda, 2, stdin);
    fflush(stdin);
    system("cls");
    while (1) {
        printf(":) Glavni meni\n1: Formiraj prazan talon\n2: Ispisi talon i trenutni broj bodova\n3: Baci kockice i odigraj potez\n4: Pomoc prijatelja\n5: Napusti igru\n\nOdaberi jednu od ponudjenih opcija:\n");
        fgets(Komanda, 3, stdin);
        fflush(stdin);
        printf("\n");
        if (strcmp(Komanda, "1\n") == 0) {
            free(Matrica);
            Matrica = formiraj_prazan_talon();
            DuzinaMatrice = 9;
            printf("Uspesno ste formirali prazan talon za igru!\nDa biste nastavili dalje, pritisnite enter...\n");
            fgets(Komanda, 2, stdin);
            fflush(stdin);
            system("cls");
        } else if (strcmp(Komanda, "2\n") == 0) {
            system("cls");
            prikazi_talon(Matrica, DuzinaMatrice);
            printf("Ukupan broj bodova: %d\n\n",UkupanBrojBodova(Matrica, DuzinaMatrice));
            printf("Da biste nastavili dalje, pritisnite enter...\n");
            fgets(Komanda, 2, stdin);
            fflush(stdin);
            system("cls");
        } else if (strcmp(Komanda, "3\n") == 0) {
            odigraj_potez(Matrica, &DuzinaMatrice);
            BrojPopunjenihPolja++;
            system("cls");
        } else if (strcmp(Komanda, "4\n") == 0) {
            pomoc_prijatelja(Matrica, &DuzinaMatrice);
            BrojPopunjenihPolja++;
            system("cls");
            prikazi_talon(Matrica, DuzinaMatrice);
            printf("Racunar je uspesno odigrao potez umesto vas!\nDa biste nastavili dalje, pritisnite enter...\n");
            /*for (int i = 0; i < 33; i++) {
                printf("%d. %d\n", i, Matrica[i]);
            }*/
            fgets(Komanda, 2, stdin);
            fflush(stdin);
            system("cls");
        } else if (strcmp(Komanda, "5\n") == 0) {
            return 0;
        } else {
            printf("Uneta vrednost moze biti samo broj od 1 do 4!\nDa biste nastavili dalje, pritisnite enter...\n");
            fgets(Komanda, 2, stdin);
            fflush(stdin);
            system("cls");
        }
        if (BrojPopunjenihPolja == 30) {
            system("cls");
            printf("\nUSPESNO STE ZAVRSILI IGRU!\n\n");
            prikazi_talon(Matrica, DuzinaMatrice);
            printf("Ukupan broj bodova: %d\n\n",UkupanBrojBodova(Matrica, DuzinaMatrice));
            BrojPopunjenihPolja = 0;
            free(Matrica);
            int* Matrica = formiraj_prazan_talon();
            DuzinaMatrice = 9;
            coo = 1;
            printf("Da biste nastavili dalje, pritisnite enter...");
            fgets(Komanda, 2, stdin);
            fflush(stdin);
            system("cls");
        }
    }
}
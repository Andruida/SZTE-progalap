/***********************************************************************
* A PROGRAMBAN NEM SZEREPELHETNEK AZ ALÁBBI SOROK:
* #include <string.h>
* #include <math.h>
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************
************************************************************************
**  ETTŐL A PONTTÓL DOLGOZHATSZ A FELADATOKON
************************************************************************
***********************************************************************/

/*
1. feladat (5 pont)

Az alabbi fuggveny egy egesz szamot kap parameterkent, majd meghatarozza,
hogy a szam paros-e. Egeszitsd ki a fuggvenyt ugy, hogy a
visszateresi erteke legyen 1, ha a szam paros, minden egyeb esetben pedig legyen 0.

Kodold le a fuggvenyt C nyelven!
A fuggveny fejlecen ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

int paros(int szam) {
    return (szam % 2 + 1) % 2;
}

/*
2. feladat (5 pont)

A feladat meghatarozni egy adott egesz szamnal kisebb paratlan pozitiv egesz szamok osszeget.
A fuggveny egyetlen parametere a kerdeses szam, amelyrol meg kell mondani,
hogy melyek a nala kisebb paratlan pozitiv egesz szamok.
A fuggveny visszateresi erteke pedig ezen paratlan szamok osszege kell legyen.

Kodold le a fuggvenyt C nyelven!
A fuggveny fejlecen ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

int paratlanosszeg(int szam) {
    int sum = 0;
    for (int i = 1; i < szam; i += 2) {
        sum += i;
    }
    return sum;
}

/*
3. feladat (5 pont)

Az alabbi fuggveny egy egesz szamot kap parameterkent, majd meghatarozza,
hogy a szam prim-e. Egeszitsd ki a fuggvenyt ugy, hogy a
visszateresi erteke legyen 1, ha a szam prim, minden egyeb esetben pedig legyen 0.

Kodold le a fuggvenyt C nyelven!
A fuggveny fejlecen ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

int prim(int szam) {
    for (int i = 1; i < szam; i++) {
        if (szam % i == 0) {
            return 1;
        }
    }
    return 0;
}
/***********************************************************************
************************************************************************
**
**  EZEN A PONTON TÚL NE VÁLTOZTASS SEMMIT SEM A FÁJLON!
**
************************************************************************
***********************************************************************/

void call_1()
{
	int szam, eredmeny;
	if(fscanf(stdin, "%d", &szam)!= 1) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	eredmeny = paros(szam);
	fprintf(stdout, "%d\n", eredmeny);
}
void test_1()
{
    int i, eredmeny;
    struct {int szam; int eredmeny;} testlist[2] = {
        {2019, 0},
        {-18,  1},
    };
    for (i = 0; i < 2; ++i) {
        eredmeny=paros(testlist[i].szam);
        if (eredmeny != testlist[i].eredmeny) {
            fprintf(stderr, "HIBA: paros(%d)\n", testlist[i].szam);
            fprintf(stderr, "\telvárt eredmény: %d\n", testlist[i].eredmeny);
            fprintf(stderr, "\tkapott eredmény: %d\n", eredmeny);
        }
    }
}

void call_2()
{
	int szam, eredmeny;
	if(fscanf(stdin, "%d", &szam)!= 1) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	eredmeny = paratlanosszeg(szam);
	fprintf(stdout, "%d\n", eredmeny);
}
void test_2()
{
    int i, eredmeny;
    struct {int szam; int eredmeny;} testlist[2] = {
        {10, 25 },
        {31, 225},
    };
    for (i = 0; i < 2; ++i) {
        eredmeny=paratlanosszeg(testlist[i].szam);
        if (eredmeny != testlist[i].eredmeny) {
            fprintf(stderr, "HIBA: paratlanosszeg(%d)\n", testlist[i].szam);
            fprintf(stderr, "\telvárt eredmény: %d\n", testlist[i].eredmeny);
            fprintf(stderr, "\tkapott eredmény: %d\n", eredmeny);
        }
    }
}

void call_3()
{
	int szam, eredmeny;
	if(fscanf(stdin, "%d", &szam)!= 1) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	eredmeny = prim(szam);
	fprintf(stdout, "%d\n", eredmeny);
}
void test_3()
{
    int i, eredmeny;
    struct {int szam; int eredmeny;} testlist[2] = {
        {13, 1},
        {20, 0},
    };
    for (i = 0; i < 2; ++i) {
        eredmeny=prim(testlist[i].szam);
        if (eredmeny != testlist[i].eredmeny) {
            fprintf(stderr, "HIBA: prim(%d)\n", testlist[i].szam);
            fprintf(stderr, "\telvárt eredmény: %d\n", testlist[i].eredmeny);
            fprintf(stderr, "\tkapott eredmény: %d\n", eredmeny);
        }
    }
}

typedef void (*call_function)();

call_function call_table[] = {
	call_1,
	call_2,
	call_3,
	NULL
};


call_function test_table[] = {
	test_1,
	test_2,
	test_3,
	NULL
};

static int __arg_check_helper(const char * exp, const char * arg) {
    while (*exp && *arg && *exp == *arg) {
        ++exp;
        ++arg;
    }
    return *exp == *arg;
}

int main(int argc, char *argv[])
{
    int feladat, calltabsize;
    if ((argc > 1) && !(__arg_check_helper("-t", argv[1]) && __arg_check_helper("--test", argv[1]))) {
        if (argc > 2) {
            feladat = atoi(argv[2]);
            for (calltabsize=0; test_table[calltabsize]; calltabsize++);
            if (feladat <= 0 || calltabsize < feladat) {
                fprintf(stderr, "HIBA: rossz feladat sorszám: %d!\n", feladat);
                return 1;
            }
            (*test_table[feladat-1])();
        } else {
            for (feladat=0; test_table[feladat]; ++feladat) {
                (*test_table[feladat])();
            }
        }
        return 0;
    }
    if (!freopen("be.txt", "r", stdin)) {
        fprintf(stderr, "HIBA: Hiányzik a `be.txt'!\n");
        return 1;
    }
    if (!freopen("ki.txt", "w", stdout)) {
        fprintf(stderr, "HIBA: A `ki.txt' nem írható!\n");
        return 1;
    }
    for (calltabsize=0; call_table[calltabsize]; calltabsize++);
    if (fscanf(stdin, "%d%*[^\n]", &feladat)!=1) {
        fprintf(stderr, "HIBA: Nem olvasható a feladat sorszám!\n");
        return 1;
    }
    fgetc(stdin);
    if (0<feladat && feladat<=calltabsize) {
        (*call_table[feladat-1])();
    } else {
        fprintf(stderr, "HIBA: Rossz feladat sorszám: %d!\n", feladat);
        return 1;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}

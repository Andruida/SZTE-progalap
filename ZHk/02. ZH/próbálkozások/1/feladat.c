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
1. feladat (2 pont)

A feladat a siknegyed fuggveny megirasa. A fuggveny egy sikbeli pont
x es y koordinatait kapja meg parameterkent, visszateresi
erteke pedig a siknegyed szama, amelyben a pont talalhato.
(A jobb felso az elso, bal felso a masodik, bal also a harmadik,
jobb also pedig a negyedik siknegyed.) A kapott pont nem illeszkedik
egyik tengelyre sem.

Kodold le C nyelven a fuggvenyt! A fuggveny fejlecen ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

int siknegyed(double x, double y) {
    if (x > 0 && y > 0) return 1;
    if (x < 0 && y > 0) return 2;
    if (x < 0 && y < 0) return 3;
    if (x > 0 && y < 0) return 4;
}

/*
2. feladat (3 pont)

A feladat meghatarozni ket egesz szam kozotti zart intervallumba eso
negyzetszamok darabszamat. A fuggveny ket parametere sorban az
intervallum also (a) es felso (b) vegpontja.
Visszateresi erteke az intervallumba eso negyzetszamok darabszama. A
vegpontok meg az intervallum reszei.

A feladat a math.h hasznalata nelkul megoldhato egy ciklussal,
amely 0-tol indul, es addig tart amig a ciklusvaltozo negyzete nagyobb
nem lesz b-nel. A ciklusmagban ellenorizzuk, hogy a ciklusvaltozo
negyzete nagyobb-egyenlo-e mint a, es ha igen, akkor noveljuk a
negyzetszamok darabszamat tarolo valtozo erteket eggyel.
A fuggveny ezzel az eredetileg 0-ra inicializalt valtozoval ter vissza.

Kodold le C nyelven a fuggvenyt! A fuggveny fejlecen ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

int negyzetszam(int a, int b) {
    int count = 0;
    for (int i = 0; i*i <= b; i++) {
        if (i*i >= a && i*i <= b) {
            count++;
        }
    }
    return count;
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
    double x, y;
    int eredmeny;
    if(fscanf(stdin, "%lf %lf", &x, &y)!=2) {
        fprintf(stderr, "HIBA: Nem olvasható adat!\n");
        return;
    }
    eredmeny=siknegyed(x, y);
    fprintf(stdout, "%d\n", eredmeny);
}
void test_1()
{
    int eredmeny, i;
    struct {double x; double y; int eredmeny;} testlist[2] = {{2.0, 0.5, 1}, {-0.2, 0.1, 2}};
    for (i = 0; i < 2; ++i) {
        eredmeny = siknegyed(testlist[i].x, testlist[i].y);
        if (eredmeny != testlist[i].eredmeny) {
            fprintf(stderr, "HIBA: siknegyed(%lf, %lf)\n"
                            "\telvárt eredmény: %d\n"
                            "\tkapott eredmény: %d\n",
                testlist[i].x, testlist[i].y, testlist[i].eredmeny, eredmeny);
        }
    }
}

void call_2()
{
	int a, b, eredmeny;
	if(fscanf(stdin, "%d %d", &a, &b)!=2) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	eredmeny=negyzetszam(a, b);
	fprintf(stdout, "%d\n", eredmeny);
}
void test_2()
{
	int eredmeny, i;
	struct {int a; int b; int eredmeny;} testlist[2] = {{100, 400, 11}, {5, 20, 2}};
	for (i = 0; i < 2; ++i) {
		eredmeny = negyzetszam(testlist[i].a, testlist[i].b);
		if (eredmeny != testlist[i].eredmeny) {
			fprintf(stderr, "HIBA: negyzetszam(%d, %d)\n"
							"\telvárt eredmény: %d\n"
							"\tkapott eredmény: %d\n",
				testlist[i].a, testlist[i].b, testlist[i].eredmeny, eredmeny);
		}
	}
}

typedef void (*call_function)();

call_function call_table[] = {
	call_1,
	call_2,
	NULL
};


call_function test_table[] = {
	test_1,
	test_2,
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

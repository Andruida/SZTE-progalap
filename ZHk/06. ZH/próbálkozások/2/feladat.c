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

Szamold ki egy s1, s2, s3, ... mertani sorozat elemeinek osszeget. A
fuggveny megkapja a sorozat elso elemet (elso) es a kvocienset (q),
valamint egy egesz intervallum also (a) es felso (b) vegpontjat.
A fuggveny visszateresi erteke az sa+...+sb osszeg.
A mertani sorozat n-edik eleme: sn=s1*q^(n-1)
*/

double hatvany(double alap, int kitevo) {
    double eredmeny = 1;
    for (int i = 0; i < kitevo; i++) {
        eredmeny *= alap;
    }
    return eredmeny;
}

double elem(double s1, double q, int n) {
    return s1 * hatvany(q, n-1);
}

double sorozat(double elso, double q, int a, int b) {
    double sum = 0;
    for (int i = a; i <= b; i++) {
        sum += elem(elso, q, i);
    }
    return sum;

}

/*
2. feladat (5 pont)

A feladat egy fuggveny megirasa, amely parameterul var
egy autokbol allo tombot, annak hosszat, illetve
egy utas szamot. A fuggveny adja vissza azon autok
atlagsebesseget, amelyben legalabb annyian utaznak,
mint a harmadik parameterkent kapott utasszam.
Amennyiben nincs az autok kozott ilyen, akkor az eredmeny legyen -1.

Kodold le C nyelven a fuggvenyt! A fuggveny fejlecen es a strukturan ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

typedef struct {
    char tipus; // az auto tipusa
    int sebesseg; // az auto aktualis sebessege
    int utasok; // az autoban utazo utasok szama
} auto_t;

float atlagsebesseg(auto_t autok[], int db, int utasok) {
    int sum = 0, n = 0;
    for (int i = 0; i < db; i++) {
        if (autok[i].utasok >= utasok) {
            sum += autok[i].sebesseg;
            n++;
        }
    }
    if (n == 0) {
        return -1;
    }
    return (float)sum/n;
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
	double e, m, eredmeny;
	int a, b;
	if(fscanf(stdin, "%lf %lf %d %d", &e, &m, &a, &b)!=4) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	eredmeny=sorozat(e, m, a, b);
	fprintf(stdout, "%.5lf\n", eredmeny);
}
void test_1()
{
  int i, err;
  double eredmeny;
  struct {double e; double q; int a; int b; double eredmeny;} testlist[2] = {{1.0, 2.0, 3, 5, 28.0}, {1.0, 0.5, 2, 4, 0.875}};
  fprintf(stderr, "=== 1. feladat tesztelése ===\n");
  for (i = 0; i < 2; ++i) {
    err = 0;
    fprintf(stderr, "%d. teszteset ... ", i + 1);
    eredmeny = sorozat(testlist[i].e, testlist[i].q, testlist[i].a, testlist[i].b);
    if (eredmeny != testlist[i].eredmeny) {
      err = 1;
      fprintf(stderr, "HIBA: sorozat(%lf, %lf, %d, %d)\n"
                      "\telvárt eredmény: %lf\n"
                      "\tkapott eredmény: %lf\n",
              testlist[i].e, testlist[i].q, testlist[i].a, testlist[i].b, testlist[i].eredmeny, eredmeny);
    }
    err ?: fprintf(stderr, "OK\n");
  }
}

void call_2(){
    int db, utas;
    auto_t *autok;
    if (fscanf(stdin, "%d %d\n", &db, &utas) != 2) {
        fprintf(stderr, "HIBA: Nem olvasható adat (db, utas)!\n");
        return;
    }
    autok = (auto_t*)malloc(db * sizeof(auto_t));
    for (int i = 0; i < db; ++i) {
        if(fscanf(stdin, "%c %d %d\n", &(autok[i].tipus), &(autok[i].sebesseg), &(autok[i].utasok)) != 3) {
            fprintf(stderr, "HIBA: Nem olvasható adat (tipus, sebesseg, utasok)!\n");
            free(autok);
            return;
        }
    }
    fprintf(stdout, "%.3f\n", atlagsebesseg(autok, db, utas));
    free(autok);
}
void test_2(){
    int i, err;
    float eredmeny;
    const float delta = 0.001;
    struct { auto_t autok[3]; int db; int utas; float eredmeny; }
        testlist[2] = {
            {
                { {'a', 6, 5}, {'b', 2, 6}, {'c', 4, 2} }, 3, 4, 4.0
            },
            {
                { {'a', 6, 5}, {'b', 2, 4}, {'c', 4, 3} }, 3, 4, 4.0
            }
        };
    fprintf(stderr, "=== 2. feladat tesztelése ===\n");
    for (i = 0; i < 2; ++i) {
        err = 0;
        fprintf(stderr, "%d. teszteset ... ", i + 1);
        eredmeny = atlagsebesseg(testlist[i].autok, testlist[i].db, testlist[i].utas);
        if (eredmeny < testlist[i].eredmeny - delta || eredmeny > testlist[i].eredmeny + delta) {
            fprintf(stderr, "HIBA: atlagsebesseg([{'%c',%d,%d},{'%c',%d,%d},{'%c',%d,%d}],%d,%d)\n"
                    "\telvárt eredmény: %.3f\n"
                    "\tkapott eredmény: %.3f\n",
                    testlist[i].autok[0].tipus, testlist[i].autok[0].sebesseg, testlist[i].autok[0].utasok,
                    testlist[i].autok[1].tipus, testlist[i].autok[1].sebesseg, testlist[i].autok[1].utasok,
                    testlist[i].autok[2].tipus, testlist[i].autok[2].sebesseg, testlist[i].autok[2].utasok,
                    testlist[i].db, testlist[i].utas,
                    testlist[i].eredmeny,
                    eredmeny
            );
            err = 1;
        }
        err ?: fprintf(stderr, "OK\n");
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

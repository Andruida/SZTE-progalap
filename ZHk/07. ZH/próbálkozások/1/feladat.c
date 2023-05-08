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

Az emelkedo() fuggveny feladata kiszamolni azt, hogy mekkora szintemelkedessel bir
a legnagyobb szintkulonbsegu szakasz egy szakaszokbol felepulo hegyvideki tura soran.
A parameterben kapott terkep tomb a turautvonal szakaszait zaro allomasok tengerszint 
feletti magassagertekeit tartalmazza. A masodik parameter ennek a tombnek a hosszat 
adja meg, vagyis az allomasok szamat. A fuggveny kiszamolna, hogy mekkora a legnagyobb kulonbseg 
a kovetkezo es az aktualis allomas kozott, ott ahol a kovetkezo allomas eleresehez felfele kell haladni.
Vedd szemugyre a probainputot es a hozza tartozo kimenetet.

A fuggveny megvalositasa hibakat tartalmaz.
Javitsd ki ezeket a hibakat.
*/
int emelkedo(int terkep[], int n) {
    int szint = 0;
    int maxszint = szint;
    int i;
    for (i = 0; i < n; ++i) {
        if (terkep[i] < terkep[i+1]) {
            szint = terkep[i+1] - terkep[i];
            if (szint > maxszint) {
                maxszint = szint;
            }
        } else {
            szint = 0;
        }
    }
    return maxszint;
}

/*
2. feladat (5 pont)

A feladat egy fuggveny megirasa, amely parameterul var egy egesz
szamokbol allo tombot, illetve ket lebegopontos szamra mutato pointert.
A tombben egesz szamok vannak, a tomb veget 0 jelzi.

A fuggveny feladata, hogy meghatarozza a tombben levo elemek kozul a
pozitiv, illetve negativ elemek atlagat kulon-kulon. A pozitiv pointer
altal mutatott ertek legyen a pozitiv elemek atlaga, mig a negativ
altal mutatott ertek a negativ elemek atlaga.

Amennyiben a tombben egy pozitiv / negativ ertek sem fordul elo,
akkor a pointer altal mutatott ertek legyen 0.

Kodold le C nyelven a fuggvenyt! A fuggveny fejlecen ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/
void statisztika(int szamok[], float* pozitiv, float* negativ) {
    *pozitiv = 0; *negativ = 0;
    int pozitivSum = 0, negativSum = 0, pozitivN = 0, negativN = 0;
    for (int* it = szamok; *it != 0; it++) {
        if (*it > 0) {
            pozitivSum += *it;
            pozitivN++;
        } else if (*it < 0) {
            negativSum += *it;
            negativN++;
        }
    }
    if (pozitivN != 0) {
        *pozitiv = (float)pozitivSum / pozitivN;
    }
    if (negativN != 0) {
        *negativ = (float)negativSum / negativN;
    }
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
    char c;
    int i, n, terkep[128];

    if(fscanf(stdin, "%d\n", &n)!=1) {
        fprintf(stderr, "HIBA: Nem olvasható adat!\n");
        return;
    }

    for (i=0; i<n; ++i) {
        if (fscanf(stdin, "%d", terkep + i)!=1) {
            fprintf(stderr, "HIBA: Nem olvasható adat!\n");
            return;
        }
    }

    if(fscanf(stdin, "\n%c", &c)!=1) {
        fprintf(stderr, "HIBA: Nem olvasható adat!\n");
        return;
    }

    if (i > 0) {
        switch (c) {
            case 'G':
                terkep[i] = terkep[i-1] + 10;
                break;
            case 'E':
                terkep[i] = terkep[i-1];
                break;
            case 'L':
                terkep[i] = terkep[i-1] - 10;
                break;
            default:
                fprintf(stderr, "HIBA: Hibás adat='%c'!\n", c);
                return;
        }
    }

    fprintf(stdout, "%d\n", emelkedo(terkep, n));
}
void test_1()
{
  int i, j, eredmeny;
  struct {int terkep[128]; int n; int eredmeny;} testlist[1] = {
    {{90,101,112,132,134,150,150,140,140,147,152,163}, 12, 20},
  };
  fprintf(stderr, "=== 1. feladat tesztelése ===\n"); 
  for (i = 0; i < 1; ++i) {
    fprintf(stderr, "%d. teszteset ... ", i + 1);
    eredmeny = emelkedo(testlist[i].terkep, testlist[i].n);
    if (eredmeny != testlist[i].eredmeny) {
      fprintf(stderr, "HIBA: emelkedo({");
      for(j = 0; j < testlist[i].n - 1; fprintf(stderr, "%d,", testlist[i].terkep[j++]));
      fprintf(stderr, "%d}, %d)\n", testlist[i].terkep[j], testlist[i].n);
      fprintf(stderr, "\telvárt eredmény: %d\n"
                      "\tkapott eredmény: %d\n",
                      testlist[i].eredmeny, eredmeny);
    } else
      fprintf(stderr, "OK\n");
  }
}

void call_2()
{
	int meret;

	if(fscanf(stdin, "%d", &meret) != 1) {
		fprintf(stderr, "HIBA: Nem olvasható adat (meret)!\n");
		return;
	}

	int tomb[meret];
	for (int i = 0; i < meret; i++){
		if(fscanf(stdin, "%d", &tomb[i]) != 1) {
			fprintf(stderr, "HIBA: Nem olvasható (tomb[%d])!\n", i);
			return;
		}
	}

	float *negativ = (float*)malloc(sizeof(float));
	if (negativ == NULL) {
		fprintf(stderr, "HIBA: Nem foglalható memória (negativ)\n");
		return;
	}

	float *pozitiv = (float*)malloc(sizeof(float));
	if (pozitiv == NULL) {
		fprintf(stderr, "HIBA: Nem foglalható memória (pozitiv)\n");
		free(negativ);
		return;
	}

	*pozitiv = 1234;
	*negativ = -1234;

	statisztika(tomb, pozitiv, negativ);

	if (negativ != NULL) {
		fprintf(stdout, "%.3f\n", *negativ);
		free(negativ);
	} else {
		fprintf(stdout, "NULL\n");
	}

	if (pozitiv != NULL) {
		fprintf(stdout, "%.3f\n", *pozitiv);
		free(pozitiv);
	} else {
		fprintf(stdout, "NULL\n");
	}
}
void test_2()
{
	float delta = 0.001;
	struct {int tomb[5]; float atlagPozitiv; float atlagNegativ;} testlist[2] = {
		{ { -3, -5, 4, 8, 0}, 6, -4 },
		{ { 8, 2, 3, 5, 0}, 4.5, 0 },
	};
	fprintf(stderr, "=== 2. feladat tesztelése ===\n");
	for (int i = 0; i < 2; ++i) {
		fprintf(stderr, "%d. teszteset ... ", i + 1);
		float *pozitiv = (float*)malloc(sizeof(float));
		float *negativ = (float*)malloc(sizeof(float));
		statisztika(testlist[i].tomb, pozitiv, negativ);
		if (pozitiv == NULL) {
			fprintf(stderr, "HIBA: NULL pointer (pozitiv)\n");
			if (negativ) free(negativ);
			continue;
		}
		if (negativ == NULL) {
			fprintf(stderr, "HIBA: NULL pointer (negativ)\n");
			if (pozitiv) free(pozitiv);
			continue;
		}
		if (*negativ <= testlist[i].atlagNegativ - delta ||
			*negativ >= testlist[i].atlagNegativ + delta ||
			*pozitiv <= testlist[i].atlagPozitiv - delta ||
			*pozitiv >= testlist[i].atlagPozitiv + delta) {
			fprintf(stderr, "HIBA statisztika({");
			int j = 0; for (; testlist[i].tomb[j] != 0; fprintf(stderr, "%d,", testlist[i].tomb[j++]));
			fprintf(stderr, "%d})\n"
				"\telvárt eredmény: %0.3f %0.3f\n"
				"\tkapott eredmény: %0.3f %0.3f\n",
				testlist[i].tomb[j],
				testlist[i].atlagPozitiv, testlist[i].atlagNegativ,
				*pozitiv, *negativ);
		} else
			fprintf(stderr, "OK\n");
		if (pozitiv) free(pozitiv);
		if (negativ) free(negativ);
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

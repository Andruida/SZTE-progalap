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

Irj egy haromszog nevu strukturat, ami az
a, b es c nevu float tipusu mezoiben
egy haromszog harom oldalanak hosszat tarolja.
Irj egy compare nevu fuggvenyt, ami ket ilyen
haromszoget kap parameterul, es a nagyobb keruletuvel ter vissza.
Amennyiben a ket haromszog kerulete egyforma, akkor a fuggveny
az elso parameterben kapott haromszoget adja vissza.
A haromszog kerulete: a+b+c.
*/
/****************************************************
 * A kovetkezo sor programba illesztese eseten      *
 * (// torlese a #define elol) a feladat nem okoz   *
 * forditasi hibat, de pontot sem fog erni.         *
 ****************************************************/
//#define KIHAGY_1
#if ! (defined(KIHAGY_1) || defined(KIHAGY_MIND))

typedef struct {
    float a;
    float b;
    float c;
} haromszog;

haromszog compare(haromszog h1, haromszog h2) {
    return (h1.a + h1.b + h1.c >= h2.a + h2.b + h2.c) ? h1 : h2;
}

#endif

/*
2. feladat (5 pont)

Egy iranyitotoronyhoz tartozo legterben 30 repulesi szint talalhato. Az azonos
szinten repulo egynel tobb gep kozul mind potencialis veszelyben van. A feladat
megirni azt a fuggvenyt, ami a repulogepek tombben tarolt magassagi szintjei
alapjan meghatarozza, hogy hany veszelyeztetett gep van a legterben. A fuggveny
parameterei a gepek magassagi szintjeit (1, ..., 30) tarolo tomb es annak a
merete, visszateresi erteke pedig a veszelyben levo gepek szama, illetve -1,
ha nincs veszelyben egy gep sem.
*/

int repulok(int tomb[], int meret) {
    int szintek[30] = {0};
    for (int i = 0; i < meret; i++) {
        szintek[tomb[i]-1]++;
    }
    int sum = 0;
    for (int i = 0; i < 30; i++)
        if (szintek[i] > 1)
            sum += szintek[i];
    
    return (sum == 0) ? -1 : sum;
}
/***********************************************************************
************************************************************************
**
**  EZEN A PONTON TÚL NE VÁLTOZTASS SEMMIT SEM A FÁJLON!
**
************************************************************************
***********************************************************************/

void call_1(){
#if ! (defined(KIHAGY_1) || defined(KIHAGY_MIND))
  int v;
  haromszog a, b, x;
  if(fscanf(stdin, "%d", &v)!=1) {
    fprintf(stderr, "HIBA: Nem olvasható adat!\n");
    return;
  }
  switch(v) {
  case 1:
    if(fscanf(stdin, "%d", &v)!=1) {
      fprintf(stderr, "HIBA: Nem olvasható adat!\n");
      return;
    }
    fprintf(stdout, "fordul%d\n", v);
    break;
  default:
    if(fscanf(stdin, "%f %f %f", &a.a, &a.b, &a.c)!=3) {
      fprintf(stderr, "HIBA: Nem olvasható adat!\n");
      return;
    }
    if(fscanf(stdin, "%f %f %f", &b.a, &b.b, &b.c)!=3) {
      fprintf(stderr, "HIBA: Nem olvasható adat!\n");
      return;
    }
    x = compare(a, b);
    fprintf(stdout, "[%f,%f,%f]\n", x.a, x.b, x.c);
    break;
  }
#endif
}
void test_1(){
#if ! (defined(KIHAGY_1) || defined(KIHAGY_MIND))
  int i;
  haromszog eredmeny;
  struct {haromszog a, b, eredmeny;} testlist[2] = {
    {{.a=3, .b=10, .c=8}, {.a=6, .b=5, .c=2}, {.a=3, .b=10, .c=8}},
    {{.a=2, .b=3,  .c=4}, {.a=4, .b=3, .c=2}, {.a=2, .b=3,  .c=4}}
  };
  for (i = 0; i < 2; ++i) {
    eredmeny = compare(testlist[i].a, testlist[i].b);
    if (eredmeny.a != testlist[i].eredmeny.a || eredmeny.b != testlist[i].eredmeny.b || eredmeny.c != testlist[i].eredmeny.c) {
      fprintf(stderr, "HIBA: compare([%f,%f,%f], [%f,%f,%f])\n"
		      "\telvárt eredmény: [%f,%f,%f]\n"
		      "\tkapott eredmény: [%f,%f,%f]\n",
		      testlist[i].a.a, testlist[i].a.b, testlist[i].a.c, testlist[i].b.a, testlist[i].b.b, testlist[i].b.c,
		      testlist[i].eredmeny.a, testlist[i].eredmeny.b, testlist[i].eredmeny.c,
		      eredmeny.a, eredmeny.b, eredmeny.c
      );
    }
  }
#endif
}

void call_2()
{
	int i=0, db, magassagok[128], eredmeny;
	if(fscanf(stdin, "%d", &db)!=1) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	for(i=0; i<db; i++) {
		if(fscanf(stdin, "%d", magassagok+i)!=1) {
			fprintf(stderr, "HIBA: Nem olvasható adat!\n");
			return;
		}
	}
	eredmeny=repulok(magassagok, db);
	fprintf(stdout, "%d\n", eredmeny);
}void test_2()
{
  int i, eredmeny;
  struct {int magassagok[128]; int db; int eredmeny;} testlist[2] = {
    {{1,2,3,4,5}, 5, -1},
    {{1,20,3,1,20,1}, 6, 5}
  };
  for (i = 0; i < 2; ++i) {
  	eredmeny = repulok(testlist[i].magassagok, testlist[i].db);
    if (eredmeny != testlist[i].eredmeny) {
      fprintf(stderr, "HIBA: repulok({...}, %d)\n"
                      "\telvárt eredmény: %d\n"
                      "\tkapott eredmény: %d\n",
              testlist[i].db, testlist[i].eredmeny, eredmeny);
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

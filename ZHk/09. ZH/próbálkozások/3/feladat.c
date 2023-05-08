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

Az alabbi fuggveny feladata helyet foglalni egy ketdimenzios int tombnek.
A tomb sor- es oszlopszama megegyezik.
A tomb N meretet a fuggveny parameterkent kapja.
A helyfoglalas ugy tortenjen, hogy a ketdimenzios tomb osszes elemet
egy egydimenzios N*N-es tombben helyezzuk el sorfolytonosan.
A helyfoglalas utan toltsuk fel a tomb elemeit ertekekkel a kovetkezo modon:
Minden cellaba irjuk be a sor- es oszlopindexek osszeget.
A fuggveny terjen vissza a tombre mutato pointerrel. A memoria felszabaditasaval
nem kell foglalkoznod.
*/

int *foglal(int n) {
	int* tomb = (int*) malloc(n*n*sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tomb[i*n+j] = i+j;
        }
    }

    return tomb;
}

/*
2. feladat (5 pont)

Egy egyenes orszagut menten a varosok a megadott tavolsagokban kovetik
egymast. Az egyik varosban tuzijatekot szeretnenk rendezni. Melyik
varosban celszeru megrendezni az esemenyt, ha arra torekszunk, hogy az
minel tobb varosbol lathato legyen? Feltesszuk, hogy a latvanyossag csak
a rendezo varos megadott sugaru kornyezeteben lathato.
Tobb optimalis megoldas eseten az a varos nyer, amelyiket az orszaguton
haladva eloszor elerjuk. A tav nevu tombben talalhatok a varosok kozotti
tavolsagok ugy, hogy tav[i] az i. es i+1. varos tavolsagat jelenti.
A varosszam a varosok szamat jeloli, latotav pedig azt a tavolsagot
jelenti, ahonnan meg lathato az esemeny. A visszateresi ertek legyen a
megoldasnak tekintheto varos sorszama 0-tol indexelve.
*/

int tuzijatek_varos(int *tav, int varosszam, int latotav) {
    int maxI = -1, maxErintett = -1;
    for (int i = 0; i < varosszam; i++) {
        int jobbra = 0, balra = 0;
        int erintett = 1;
        for (int o = 1; i-o >= 0 || i+o-1 < varosszam; o++) {
            if (i+o < varosszam) {
                jobbra += tav[i+o-1];
                if (jobbra <= latotav) erintett++;
            }
            if (i-o >= 0) {
                balra += tav[i-o];
                if (balra <= latotav) erintett++;
            }
            if (balra > latotav && jobbra > latotav) break; 
        }
        if (maxErintett < erintett) {
            maxI = i;
            maxErintett = erintett;
        }
    }

    return maxI;
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
	int chck;
	int n, ij;
	int *ptr = NULL;
	if(fscanf(stdin, "%d %d", &chck, &n)!=2) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	ptr = foglal(n);
	switch (chck) {
		case 1:
			if (ptr != NULL) {
				free(ptr);
				fprintf(stdout,"%d\n", n);
			} else {
				fprintf(stdout,"NULL\n");
			}
			break;
		case 2:
			if (ptr != NULL) {
				ptr[n*n-1]=n;
				fprintf(stdout,"%d\n", n);
			} else {
				fprintf(stdout,"NULL\n");
			}
			break;
		case 3:
			for(ij=0; ij<n*n; ij++) {
				fprintf(stdout, "%d%c", ptr[ij], ((ij%n)==(n-1))?'\n':' ');
			}
			break;
		default:
			if(fscanf(stdin, "%d", &ij)!=1) {
				fprintf(stderr, "HIBA: Nem olvasható adat!\n");
				return;
			}
			fprintf(stdout,"%d\n", ptr[ij]);
			break;
	}
}
void test_1()
{
	const int n = 3;
	int i, j, k;
  int *ptr = NULL;
  struct {int ptr[9];} testlist[1] = {
  	{
  		{0,1,2, 1,2,3, 2,3,4}
  	}
  };
  for (i = 0; i < 1; ++i) {
    ptr = foglal(n);
    if (ptr == NULL) {
    	fprintf(stderr, "HIBA: NULL pointer\n");
    	return;
    } else {
    	for (j = 0; j < n; ++j) {
    		for (k = 0; k < n; ++k) {
    			if (ptr[j*n+k] != testlist[i].ptr[j*n+k]) {
    				fprintf(stderr, "HIBA a(z) (%d,%d) pozíción\n"
    					              "\telvárt eredmény: %d\n"
    					              "\tkapott eredmény: %d\n",
    					              j, k, testlist[i].ptr[j*n+k], ptr[j*n+k]);
    				return;
    			}
    		}
    	}
    }
    free(ptr);
  }
}

void call_2()
{
	int varosszam, i, *tav, latotav;
	if(fscanf(stdin, "%d %d", &latotav, &varosszam)!=2) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	tav = malloc(varosszam * sizeof(int));
	for (i = 0; i < varosszam-1; i++) {
		if(fscanf(stdin, "%d", tav+i)!=1) {
			fprintf(stderr, "HIBA: Nem olvasható adat!\n");
			return;
		}
	}
	fprintf(stdout, "%d\n", tuzijatek_varos(tav, varosszam, latotav));
	free(tav);
}
void test_2()
{
	int i, eredmeny;
	struct {int tav[10]; int varosszam; int latotav; int eredmeny;} testlist[2] = {
		{{1,3,3,5,3,4,3}, 7, 6, 1},
		{{1,3,3,5,3,4,3}, 7, 8, 3}
	};
	for (i = 0; i < 2; ++i) {
		eredmeny = tuzijatek_varos(testlist[i].tav, testlist[i].varosszam, testlist[i].latotav);
		if (testlist[i].eredmeny != eredmeny) {
			fprintf(stderr, "HIBA: tuzijatek_varos({...}, %d, %d)\n"
							"\telvárt eredmény: %d\n"
							"\tkapott eredmény: %d\n",
					testlist[i].varosszam, testlist[i].latotav, testlist[i].eredmeny, eredmeny);
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

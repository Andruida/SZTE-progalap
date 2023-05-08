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

Az alabbi fuggveny elso parametere egy sztring. A feladat a sztringben
megadott erteku elemek csereje masik ertekre. A feladat megoldhato egy
ciklus hasznalataval. A ciklus szamlaloja azt mutatja, hogy eppen hanyadik
elemet dolgozzuk fel az eredeti sztringnek es az eredmeny-sztring hanyadik
helyere kerul ez az elem. Nyilvanvalo, hogy ha az aktualisan feldolgozott
elem megegyezik a  parameterben kapott ertekkel, akkor ezt le kell cserelni.
Figyelj arra, hogy az eredmeny-sztring veget lezard a sztring veget jelzo
0 kodu karakterrel!
Az eredmenyt a masodik parameterben kapott eredmeny nevu sztringben
kell elkesziteni.
Kodold le a fuggvenyt C nyelven. A fuggveny fejlecen ne valtoztass!
*/
void strcsere(char str[], char eredmeny[], char mit, char mire) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == mit) {
            eredmeny[i] = mire;
        } else {
            eredmeny[i] = str[i];
        }
    }
    eredmeny[i] = '\0';
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
	char x=0, f=0, t=0, src[128]="#####", dst[128]="#####", *p;
	int  N=-1;
	int i;
	for(i=0;i<128;++i) dst[i]='#';
	if(fscanf(stdin, "%c", &x)!=1) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	if(x=='E' || x=='R') {
		if(fscanf(stdin, ":%d", &N)!=1) {
			fprintf(stderr, "HIBA: Nem olvasható adat!\n");
			return;
		}
	}
	if(!(fscanf(stdin, "%*[^\n]") || (fgetc(stdin) != EOF))) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	if(fscanf(stdin, "%c:%c:", &f, &t)!=2) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	if(fgets(src, 128, stdin)==NULL) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	for(p=src;*p&&*p!=10;p++);
	*p=0;
	strcsere(src, dst, f, t);
	if(x=='R') {
		fprintf(stdout, "%d\n", dst[N]);
	} else if(x=='E') {
		int i;
		for(i=0; i<N; i++) {
			fprintf(stdout, "%c", dst[i]);
		}
		fputc('\n', stdout);
	} else {
		fprintf(stdout, "%s\n", dst);
	}
}

void test_1()
{
    int i, j;
    char str[] = "####################", eredmeny[] = "####################";
    struct {char str[20]; char mit; char mire; char eredmeny[20];} testlist[2] = {
        {"progalap", 'a', 'A', "progAlAp"},
        {"valami",   'e', 'a', "valami"  },
    };
    for (i = 0; i < 2; ++i) {
        for(j = 0; testlist[i].str[j] != 0; str[j] = testlist[i].str[j], ++j);
        str[j] = 0;
        strcsere(str, eredmeny, testlist[i].mit, testlist[i].mire);
        for(j = 0; eredmeny[j] != 0 && testlist[i].eredmeny[j] != 0 && eredmeny[j] == testlist[i].eredmeny[j]; ++j);
        if (eredmeny[j] != testlist[i].eredmeny[j]) {
            fprintf(stderr, "HIBA: strcsere(\"%s\", \"...\", '%c', '%c')\n", testlist[i].str, testlist[i].mit, testlist[i]. mire);
            fprintf(stderr, "\telvárt eredmény: \"%s\"\n", testlist[i].eredmeny);
            fprintf(stderr, "\tkapott eredmény: \"%s\"\n", eredmeny);
        }
    }
}

typedef void (*call_function)();

call_function call_table[] = {
	call_1,
	NULL
};


call_function test_table[] = {
	test_1,
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

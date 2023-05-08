#include <stdio.h>

int main() {

    FILE* fi = fopen("be.txt", "r");
    char str[100] = {0};
    fscanf(fi, "%s", str);
    fclose(fi);

    int zarojelek = 0;
    int hiba = -1;
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '(') zarojelek++;
        if (str[i] == ')') zarojelek--;
        hiba = i;
        if (zarojelek < 0) {
            break;
        }
    }

    if (zarojelek == 0) {
        hiba = -1;
    } else if (zarojelek > 0) {
        hiba++;
    }

    FILE* fo = fopen("ki.txt", "w");
    fprintf(fo, "%d\n", hiba);
    fclose(fo);

    return 0;
}
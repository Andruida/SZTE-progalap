#include <stdio.h>

int valid(int sorok, int oszlopok, int r, int c) {
    return (r >= 0 && c >= 0 && r < sorok && c < oszlopok);
}

int main() {
    
    FILE* fi = fopen("be.txt", "r");
    int r,c;
    fscanf(fi, "%d,%d\n", &r, &c); // csak mert lol
    r--;c--; 

    char curr = 0;
    int oszlopok = 1;
    while(curr != '\n') {
        fscanf(fi, "%c", &curr);
        if (curr == ',') {
            oszlopok++;
        }
    }
    fseek(fi, 0, SEEK_SET);

    curr = 0;
    int sorok = -1;
    while(curr != '-') {
        fscanf(fi, "%c", &curr);
        if (curr == '\n') {
            sorok++;
        }
    }
    fseek(fi, 0, SEEK_SET);

    fscanf(fi, "%d,%d\n", &r, &c);
    r--;c--;
    int matrix[sorok][oszlopok];
    char _;

    for (int i = 0; i < sorok; i++) {
        for (int j = 0; j < oszlopok; j++) {
            fscanf(fi, "%d%c", &matrix[i][j], &_);
        }
    }

    fclose(fi);

    FILE* fo = fopen("ki.txt", "w");

    int listed = 0;
    int stepsize = 1;
    int direction = -1;

    while (listed < sorok*oszlopok)
    {
        // Y
        for (int i = 0; i < stepsize; i++) {
            if (valid(sorok, oszlopok, r, c)) {
                fprintf(fo, "%d,", matrix[r][c]);
                listed++;
            }
            r += direction;
        }

        // X
        for (int i = 0; i < stepsize; i++) {
            if (valid(sorok, oszlopok, r, c)) {
                fprintf(fo, "%d,", matrix[r][c]);
                listed++;
            }
            c += direction;
        }

        direction *= -1;
        stepsize++;
    }
    fseek(fo, -1, SEEK_CUR);
    fprintf(fo, "\n");
    

    fclose(fo);
}
#include <stdio.h>

int main() {
    char polubiosz[6][6];
    int row = 0, col = 0;
    for (char c = 'A'; c <= 'Z'; c++) {
        polubiosz[row][col] = c;
        col++;
        if (col > 5) {
            col %= 6;
            row++;
        }
    }

    for (char c = '0'; c <= '9'; c++) {
        polubiosz[row][col] = c;
        col++;
        if (col > 5) {
            col %= 6;
            row++;
        }
    }


    FILE* fin = fopen("be.txt", "r");
    FILE* fout = fopen("ki.txt", "w");
    int n = 0;
    fscanf(fin, "%d\n", &n);
    for (int i = 0; i < n; i++) {
        char cr, cc;
        fscanf(fin, "%c%c\n", &cr, &cc);
        int r = cr - '0' - 1, c = cc - '0' - 1;
        if (r < 0 || r > 5 || c < 0 || c > 5) continue;

        fprintf(fout, "%c", polubiosz[r][c]);
    }
    fprintf(fout, "\n");

    fclose(fout);
    fclose(fin);

    return 0;
}
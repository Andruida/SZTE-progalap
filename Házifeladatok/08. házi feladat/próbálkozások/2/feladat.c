#include <stdio.h>
#include <stdlib.h>

int checkArea(char** map, int rows, int cols, int row, int col, int dist, char str) {
    int startRow = (row-dist > 0) ? row-dist : 0;
    int startCol = (col-dist > 0) ? col-dist : 0;

    int endRow = (row+dist < rows) ? row+dist : rows-1;
    int endCol = (col+dist < cols) ? col+dist : cols-1;

    for (int r = startRow; r <= endRow; r++) {
        for (int c = startCol; c <= endCol; c++) {
            if (map[r][c] == str) {
                return 1;
            }
        }
    }
    return 0;

}

int main() {
    FILE* f = fopen("be.txt", "r");
    int mountD, waterD, stormD;
    fscanf(f, "%d %d %d", &mountD, &waterD, &stormD);
    int rows, cols;
    fscanf(f, "%d %d", &rows, &cols);
    char** map = (char**)malloc(rows * sizeof(char*));
    for (int r = 0; r < rows; r++) {
        map[r] = (char*)malloc(cols * sizeof(char));
        char _;
        fscanf(f, "%c", &_);
        for (int c = 0; c < cols; c++) {
            fscanf(f, "%c", &map[r][c]);
        }
    }
    fclose(f);
    int possibilities = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (map[r][c] == 'A' || map[r][c] == 'X') continue;
            if (
                checkArea(map, rows, cols, r, c, mountD, 'A') &&
                checkArea(map, rows, cols, r, c, waterD, '~') &&
                !checkArea(map, rows, cols, r, c, stormD, 'X')
            ) possibilities++;
        }
    }    

    f = fopen("ki.txt", "w");
    fprintf(f, "%d\n", possibilities);
    fclose(f);

    for (int r = 0; r < rows; r++) {
        free(map[r]);        
    }
    free(map);

    return 0;
}
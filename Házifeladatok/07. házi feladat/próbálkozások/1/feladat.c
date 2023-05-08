#include <stdio.h>

int main() {
    FILE* input = fopen("be.txt", "r");
    int rows, cols;
    fscanf(input, "%d %d", &rows, &cols);
    int data[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(input, "%d", &data[i][j]);
        }
    }
    fclose(input);

    // kiindulóhelyzet
    int rPos;
    for (int j = 0; j < cols; j++) {
        if (data[0][j] == 1) {
            rPos = j;
            break;
        }
    }

    int missed = 0;

    for (int i = 1; i < rows; i++) {
        int left = 0, right = 0, nLeft = 0, nRight = 0, onRobot = 0, sum = 0;
        for (int j = 0; j < cols; j++) {
            if (data[i][j] == 1) {
                sum++;
                if (j < rPos) {
                    left++;
                    if (j == rPos-1) {
                        nLeft++;
                    }
                } else if (j > rPos) {
                    right++;
                    if (j == rPos+1) {
                        nRight++;
                    }
                } else if (j == rPos) {
                    onRobot++;
                }
            }
        }
        int caught = 0;
        if (sum == 0) {}//noop
        else if (onRobot == 1) {
            caught = 1;
        } else if (nLeft && !nRight) {
            rPos--;
            caught = 1;
        } else if (!nLeft && nRight) {
            rPos++;
            caught = 1;
        } else if (left > right) {
            rPos--;
        } else if (left < right) {
            rPos++;
        }

        missed += sum - caught;
    }

    FILE* output = fopen("ki.txt", "w");
    fprintf(output, "%d\n", missed);
    fclose(output);

    return 0;
}
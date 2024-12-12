#include <stdio.h>
#include <string.h>

#define MAX_SIZE 141
#define WORD "XMAS"

int count_word(char grid[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    int directions[8][2] = {
        {0, 1},    // Droite
        {1, 0},    // Bas
        {1, 1},    // Diagonale bas-droite
        {1, -1},   // Diagonale bas-gauche
        {0, -1},   // Gauche
        {-1, 0},   // Haut
        {-1, -1},  // Diagonale haut-gauche
        {-1, 1}    // Diagonale haut-droite
    };

    int word_length = strlen(WORD);
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int d = 0; d < 8; d++) {
                int found = 1;
                for (int k = 0; k < word_length; k++) {
                    int new_i = i + k * directions[d][0];
                    int new_j = j + k * directions[d][1];

                    if (new_i < 0 || new_i >= rows || new_j < 0 ||
                        new_j >= cols || grid[new_i][new_j] != WORD[k]) {
                        found = 0;
                        break;
                    }
                }
                if (found) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char grid[MAX_SIZE][MAX_SIZE];
    int rows = 0, cols = 0;

    while (fgets(grid[rows], MAX_SIZE, file) && rows < MAX_SIZE) {
        // Remove newline character if present
        grid[rows][strcspn(grid[rows], "\n")] = '\0';
        rows++;
    }
    fclose(file);

    // Determine the number of columns from the first row
    if (rows > 0) {
        cols = strlen(grid[0]);
    }

    int result = count_word(grid, rows, cols);
    printf("The word '%s' appears %d times in the grid.\n", WORD, result);

    return 0;
}

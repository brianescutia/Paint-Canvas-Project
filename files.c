#include "canvas.h"
#include <stdio.h>
#include <stdlib.h>

// Saves the current canvas to the specified file
void save_canvas(Canvas* c, const char* file_name) {
    if (!c || !file_name) return;

    FILE* file = fopen(file_name, "w");
    if (!file) {
        printf("Failed to open file for writing\n");
        return;
    }

    fprintf(file, "%d %d\n", c->rows, c->cols);

    for (int i = 0; i < c->rows; i++) {
        for (int j = 0; j < c->cols; j++) {
            fprintf(file, "%c", c->matrix[i][j]);
        }
        fprintf(file, "\n"); 
    }

    fclose(file);
}

// Loads a canvas from the specified file.
void load_canvas(Canvas** c, const char* file_name) {
    if (!file_name) return;

    FILE* file = fopen(file_name, "r");
    if (!file) {
        return;
    }

    int rows, cols;
    if (fscanf(file, "%d %d\n", &rows, &cols) != 2) {
        fclose(file);
        return;
    }

    if (*c) {
        for (int i = 0; i < (*c)->rows; i++) {
            free((*c)->matrix[i]);
        }
        free((*c)->matrix);
        free(*c);
    }

    *c = create_canvas(rows, cols);
    if (!*c) {
        fclose(file);
        return;
    }

    // Read the canvas content from the file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char tempChar;
            if (fscanf(file, " %c", &tempChar) != 1) {
                fclose(file);
                return;
            }
            (*c)->matrix[i][j] = tempChar;
        }
        fscanf(file, "\n");
    }

    fclose(file);
}
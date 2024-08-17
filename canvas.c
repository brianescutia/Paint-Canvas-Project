#include "canvas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to safely allocate memory and handle errors
void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// Initialize each cell of the canvas to a default character
void initialize_canvas_cells(Canvas* c, char defaultChar) {
    for (int i = 0; i < c->rows; ++i) {
        for (int j = 0; j < c->cols; ++j) {
            c->matrix[i][j] = defaultChar;
        }
    }
}

// Create a new canvas with specified dimensions
Canvas* create_canvas(int rows, int cols) {
    Canvas* c = (Canvas*)safe_malloc(sizeof(Canvas));
    c->rows = rows;
    c->cols = cols;
    c->matrix = (char**)safe_malloc(rows * sizeof(char*));

    for (int i = 0; i < rows; ++i) {
        c->matrix[i] = (char*)safe_malloc(cols * sizeof(char));
    }

    initialize_canvas_cells(c, '*'); // Use '*' as the default fill character
    return c;
}

// Display the current state of the canvas
void display_canvas(Canvas* c) {
    // Displaying the canvas from top to bottom
    for (int i = c->rows - 1; i >= 0; --i) {
        printf("%2d ", i); // Adjust for potential double-digit numbers
        for (int j = 0; j < c->cols; ++j) {
            printf("%c ", c->matrix[i][j]);
        }
        printf("\n");
    }

    // Displaying column headers
    printf("   "); // Align with row numbers
    for (int j = 0; j < c->cols; ++j) {
        printf("%d ", j);
    }
    printf("\n");
}

// Erase a character at the specified position
void erase(Canvas* c, int row, int col) {
    // Validating the specified position
    if (row >= 0 && row < c->rows && col >= 0 && col < c->cols) {
        c->matrix[row][col] = '*'; // Reset to default character
    } else {
        printf("Position (%d, %d) is out of bounds.\n", row, col);
    }
}

// Expand or shrink the matrix to accommodate a new row
char** adjust_matrix_for_new_row(Canvas* c, int newSize) {
    char** newMatrix = (char**)safe_malloc(newSize * sizeof(char*));
    for (int i = 0; i < c->rows && i < newSize; ++i) {
        newMatrix[i] = c->matrix[i]; // Copying existing row pointers
    }
    return newMatrix;
}

// Add a row at the specified position
void add_row(Canvas* c, int position) {
    if (position < 0 || position > c->rows) {
        printf("Invalid position %d for adding a new row.\n", position);
        return;
    }

    // Expanding the matrix to accommodate the new row
    char** newMatrix = adjust_matrix_for_new_row(c, c->rows + 1);
    if (position < c->rows) { // If not adding to the end, shift rows down
        for (int i = c->rows; i > position; --i) {
            newMatrix[i] = newMatrix[i - 1];
        }
    }
    newMatrix[position] = (char*)safe_malloc(c->cols * sizeof(char)); // Allocate new row
    for (int j = 0; j < c->cols; ++j) {
        newMatrix[position][j] = '*'; // Initialize new row cells
    }

    if (c->rows > 0) free(c->matrix); // Free old matrix if it exists
    c->matrix = newMatrix; // Assign the new matrix to the canvas
    c->rows++; // Increment row count
}

// Helper function to allocate memory for a new column
// Allocate a new column array and initialize its values
char* allocate_new_column(int cols) {
    // Use safe memory allocation with error handling
    char* new_column = (char*)safe_malloc(cols * sizeof(char));
    // Initialize each cell in the new column to the default character
    for (int i = 0; i < cols; ++i) {
        new_column[i] = '*';
    }
    return new_column;
}

// Reallocate the existing matrix to include a new column at the specified position
void reallocate_matrix_for_column(Canvas* c, int position, bool isAdding) {
    for (int row = 0; row < c->rows; ++row) {
        // Allocate or reallocate each row to accommodate the new column
        char* new_row = isAdding ? allocate_new_column(c->cols + 1) : (char*)safe_malloc((c->cols - 1) * sizeof(char));
        
        // Copy existing row elements to the new row, skipping or adding space for the new column as needed
        for (int col = 0, new_col = 0; col < c->cols; ++col) {
            if (isAdding) {
                if (col == position) {
                    new_row[new_col++] = '*'; // Initialize the new column cell
                }
                new_row[new_col++] = c->matrix[row][col];
            } else { // For deleting a column, skip the specified column
                if (col != position) {
                    new_row[new_col++] = c->matrix[row][col];
                }
            }
        }
        
        // Replace the old row with the new row
        free(c->matrix[row]);
        c->matrix[row] = new_row;
    }
}

// Add a column at a specified position
void add_column(Canvas* c, int position) {
    if (position < 0 || position > c->cols) {
        printf("Invalid position for adding column: %d.\n", position);
        return;
    }

    // Adjust the matrix for the new column
    reallocate_matrix_for_column(c, position, true);

    // Increase the column count
    c->cols++;
}

// Delete a row at a specified position
void delete_row(Canvas* c, int position) {
    if (position < 0 || position >= c->rows) {
        printf("Invalid position for deleting row: %d.\n", position);
        return;
    }

    // Free the memory for the specified row
    free(c->matrix[position]);

    // Shift rows above the deleted row down by one position
    for (int i = position; i < c->rows - 1; ++i) {
        c->matrix[i] = c->matrix[i + 1];
    }

    // Decrease the row count and reallocate the matrix
    c->rows--;
    c->matrix = (char**)realloc(c->matrix, c->rows * sizeof(char*));
    if (!c->matrix && c->rows > 0) {
        perror("Failed to reallocate memory for the matrix after row deletion");
        exit(EXIT_FAILURE);
    }
}

// Delete a column at a specified position
void delete_column(Canvas* c, int position) {
    if (position < 0 || position >= c->cols) {
        printf("Invalid position for deleting column: %d.\n", position);
        return;
    }

    // Adjust the matrix for the removed column
    reallocate_matrix_for_column(c, position, false);

    // Decrease the column count
    c->cols--;
}

// Resize the canvas to new dimensions
void resize_canvas(Canvas* c, int new_rows, int new_cols) {
    // Handle reducing the number of rows
    if (new_rows < c->rows) {
        for (int i = new_rows; i < c->rows; ++i) {
            free(c->matrix[i]); // Free extra rows
        }
    }

    // Resize the row pointers
    c->matrix = (char**)safe_malloc(new_rows * sizeof(char*));

    // Adjust each row
    for (int i = 0; i < new_rows; i++) {
        if (i >= c->rows) {
            // New rows need to be allocated
            c->matrix[i] = allocate_new_column(new_cols);
        } else {
            // Existing rows need to be resized
            c->matrix[i] = (char*)realloc(c->matrix[i], new_cols * sizeof(char));
            if (!c->matrix[i]) {
                perror("Failed to reallocate memory for existing row during resize");
                exit(EXIT_FAILURE);
            }
            // Initialize any new cells in existing rows
            for (int j = c->cols; j < new_cols; j++) {
                c->matrix[i][j] = '*';
            }
        }
    }
    
    // Update canvas size
    c->rows = new_rows;
    c->cols = new_cols;

    // Handle expanding number of rows
    if (new_rows > c->rows) {
        for (int i = c->rows; i < new_rows; ++i) {
            c->matrix[i] = allocate_new_column(new_cols); // Allocate and initialize new rows
        }
    }
}


// Function to draw a line
void draw_line(Canvas* c, int start_row, int start_col, int end_row, int end_col) {
int col_distance = abs(end_col - start_col);
int row_distance = -abs(end_row - start_row);
int horizontal_direction, vertical_direction;

    if (start_col < end_col) {  
        horizontal_direction = 1;
    } else {
        horizontal_direction = -1;
    }

    if (start_row < end_row) {
        vertical_direction = 1;
    } else {
        vertical_direction = -1;
    }
    int path = col_distance + row_distance; 
    int path_check;

    char lineChar = determine_draw_char(start_row, start_col, end_row, end_col); // Use for the entire line

    while (true) {
        // Set character for the current point
        if (c->matrix[start_row][start_col] != '*' && c->matrix[start_row][start_col] != lineChar) {
            c->matrix[start_row][start_col] = '+'; // Intersection
        } else {
            c->matrix[start_row][start_col] = lineChar; // Draw line
        }

        if (start_row == end_row && start_col == end_col) break; // Stop if end point is reached
        path_check = 2 * path;
        if (path_check >= row_distance) { path += row_distance; start_col += horizontal_direction; }
        if (path_check <= col_distance) { path += col_distance; start_row += vertical_direction; }
    }
}

char determine_draw_char(int start_row, int start_col, int end_row, int end_col) {
    // Initially assume a horizontal line
    char lineChar = '-';

    // Vertical line
    if (start_col == end_col) lineChar = '|';
    // Diagonal line
    else if (abs(end_col - start_col) == abs(end_row - start_row)) {
        if ((end_col > start_col && end_row > start_row) || (end_col < start_col && end_row < start_row)) {
            lineChar = '/';
        } else {
            lineChar = '\\';
        }
    }
    
    return lineChar;
}

// Function to free the canvas memory
void free_canvas(Canvas* c) {
    for (int i = 0; i < c->rows; ++i) {
        free(c->matrix[i]);
    }
    free(c->matrix);
    free(c);
}
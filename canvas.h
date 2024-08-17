#ifndef CANVAS_H
#define CANVAS_H
#include <stdbool.h>

typedef struct {
    int rows;
    int cols;
    char **matrix;
} Canvas;

Canvas* create_canvas(int rows, int cols);
void free_canvas(Canvas* c);
void draw_line(Canvas* c, int x0, int y0, int x1, int y1);
char determine_draw_char(int start_row, int start_col, int end_row, int end_col); 

void display_canvas(Canvas* c);
void add_row(Canvas* c, int position);
void add_column(Canvas* c, int position);
void delete_row(Canvas* c, int position);
void delete_column(Canvas* c, int position);
void resize_canvas(Canvas* c, int new_rows, int new_cols);
void erase(Canvas* c, int row, int col);

#endif // CANVAS_H
#include "canvas.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming these functions are defined in other parts of your program
void print_help(){
  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}
void draw_line(Canvas* c, int x0, int y0, int x1, int y1);
void add_row(Canvas* c, int position);
void add_column(Canvas* c, int position);
void delete_row(Canvas* c, int position);
void delete_column(Canvas* c, int position);
void resize_canvas(Canvas* c, int new_rows, int new_cols);
void erase(Canvas* c, int row, int col);
void save_canvas(Canvas* c, const char* file_name);
void load_canvas(Canvas** c, const char* file_name);

// handle all command inputs
void process_command(Canvas** c, char* command) {
    char type;
    int x0, y0, x1, y1, position, new_rows, new_cols;
    char file_name[256];

    if (strncmp(command, "q", 1) == 0) {
    } else if (strncmp(command, "h", 1) == 0) {
        print_help();
    } else if (sscanf(command, " %*c %d %d %d %d", &x0, &y0, &x1, &y1) == 4) {
    if (x0 < 0 || x0 >= (*c)->cols || y0 < 0 || y0 >= (*c)->rows || x1 < 0 || x1 >= (*c)->cols || y1 < 0 || y1 >= (*c)->rows) {
        printf("Coordinates out of bounds.\n");
    } else {
        draw_line(*c, x0, y0, x1, y1);
        display_canvas(*c);
    }
    

    } else if (sscanf(command, "r %d %d", &new_rows, &new_cols) == 2) {
        if (new_rows <= 0 || new_cols <= 0) {
            printf("Improper resize command.\n");
        } else {
            resize_canvas(*c, new_rows, new_cols);
            display_canvas(*c);
        }
    } else if (sscanf(command, " %*[^a] a %c %d", &type, &position) == 2 && (type == 'r' || type == 'c')) {
        if ((type == 'r' && (position < 0 || position > (*c)->rows)) || (type == 'c' && (position < 0 || position > (*c)->cols))) {
            printf("Improper add command.\n");
        } else {
            if (type == 'r') {
                add_row(*c, position);
            } else {
                add_column(*c, position);
            }
            display_canvas(*c);
        }
    } else if (sscanf(command, "d %c %d", &type, &position) == 2 && (type == 'r' || type == 'c')) {
        if ((type == 'r' && (position < 0 || position >= (*c)->rows)) || (type == 'c' && (position < 0 || position >= (*c)->cols))) {
            printf("Improper delete command.\n");
        } else {
            if (type == 'r') {
                delete_row(*c, position);
            } else {
                delete_column(*c, position);
            }
            display_canvas(*c);
        }
    } else if (sscanf(command, "e %d %d", &x0, &y0) == 2) {
        if (x0 < 0 || x0 >= (*c)->cols || y0 < 0 || y0 >= (*c)->rows) {
            printf("Improper erase command.\n");
        } else {
            erase(*c, y0, x0);
            display_canvas(*c);
        }
    } else if (sscanf(command, "s %255s", file_name) == 1) {
        save_canvas(*c, file_name);
    } else if (sscanf(command, "l %255s", file_name) == 1) {
        load_canvas(c, file_name);
        display_canvas(*c);
    } else {
        printf("Unrecognized command. Type h for help.\n");
    }
}
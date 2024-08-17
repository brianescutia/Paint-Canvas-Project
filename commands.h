#ifndef COMMANDS_H
#define COMMANDS_H

#include "canvas.h"

void process_command(Canvas** c, char* command);
void print_help();
void erase(Canvas* c, int row, int col);

#endif // COMMANDS_H
#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "canvas.h"

void save_canvas(Canvas* c, const char* file_name);
void load_canvas(Canvas** c, const char* file_name);

#endif // FILE_OPERATIONS_H
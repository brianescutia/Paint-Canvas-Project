#include "canvas.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rows = 10; // Default canvas size
    int cols = 10; // Default canvas size

    // Process command-line arguments for canvas size
    if (argc == 3) {
        rows = atoi(argv[1]);
        if (rows <= 0) {
            printf("The number of rows is not less than 1.\n");
            rows = 10; // Reset to default if invalid
        }

        cols = atoi(argv[2]);
        if (cols <= 0) {
            printf("The number of columns is not less than 1.\n");
            cols = 10; // Reset to default if invalid
        }
    } else if (argc != 1) {
        printf("Wrong number of command line arguments entered.\n");
        printf("Usage: %s [num_rows num_cols]\n", argv[0]);
        return 1; // Exit if the wrong number of arguments are provided
    }

    // Initialize the canvas
    Canvas *canvas = create_canvas(rows, cols);
    if (!canvas) {
        fprintf(stderr, "Failed to initialize canvas.\n");
        return 1;
    }

    // Display the canvas
    display_canvas(canvas);

    // Main command loop
    char command[256];
    printf("Enter your command: ");
    while (fgets(command, sizeof(command), stdin) != NULL) {
        if (strncmp(command, "q", 1) == 0) {;
            break; // Quit command
        }

        // Process each command within the command loop.
        process_command(&canvas, command);

        printf("Enter your command: "); // Prompt again for the next command
    }

    // Clean up and exit
    free_canvas(canvas);
    return 0;
}
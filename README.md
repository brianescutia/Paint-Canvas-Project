# Paint Canvas

Paint Canvas is a simple C-based terminal drawing tool that allows users to create, modify, and save a grid-based canvas. Users can draw lines, add or delete rows and columns, resize the canvas, erase specific areas, and save/load their artwork.

## Features

- Draw Lines: Draw horizontal, vertical, and diagonal lines.
- Canvas Resize: Adjust the size of the canvas by adding or deleting rows and columns.
- Erase: Remove specific characters from the canvas.
- Save/Load: Save your canvas to a file or load it from a file.
  
## Getting Started

### Prerequisites

- C compiler (GCC or similar)
- Make utility (optional but recommended)
  
### Installation
1. Clone the repository:

```sh
  git clone https://github.com/yourusername/paint-canvas.git
  cd paint-canvas
  ```

2. Build the project:
   
```sh
make
```

or manually:

```sh
gcc -o paint_canvas main.c canvas.c commands.c files.c -I.
```

## Running the Application
After building the project, you can run the application using the following command:

```sh
./paint_canvas
```
### Commands
- Help: h - Display available commands.
- Quit: q - Exit the program.
- Draw Line: w row_start col_start row_end col_end - Draw a line between two points.
- Resize Canvas: r num_rows num_cols - Resize the canvas.
- Add Row/Column: a [r | c] pos - Add a row or column at a specified position.
- Delete Row/Column: d [r | c] pos - Delete a row or column at a specified position.
- Erase: e row col - Erase a character at the specified position.
- Save: s file_name - Save the current canvas to a file.
- Load: l file_name - Load a canvas from a file.

## Example Usage

```sh
h
w 1 1 3 3
a r 2
r 15 15
e 2 2
s my_drawing.txt
```

## Project Structure

- canvas.h/c: Core canvas operations like creating, resizing, drawing, and erasing.
- commands.h/c: Command processing and user interaction handling.
- files.h/c: File operations for saving and loading canvas states.
- main.c: Main entry point and initial canvas setup.
  
## Example Outputs
Example of drawing on a 10x10 canvas:

```sh
 9 * * * * * * * * * *
 8 * * * * * * * * * *
 7 * * * * * * * * * *
 6 * * * * * * * * * *
 5 * * * * * * * * * *
 4 * * * * * * * * * *
 3 * * * * * * * * * *
 2 * * * * * * * * * *
 1 * * * * * * * * * *
 0 * * * * * * * * * *
   0 1 2 3 4 5 6 7 8 9
```

## Notes

- Ensure that the canvas dimensions and positions specified in commands are within bounds.
- When saving and loading, ensure that the file is properly formatted to avoid errors.

## Authors
- Brian Escutia 

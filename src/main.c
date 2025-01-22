#include "header.h"

#define GRID_ROW 20
#define GRID_COL 10

int cells[GRID_ROW][GRID_COL];

// Grid
typedef struct {
    int numRows;
    int numCols;
    int cellSize;
} Grid;


static Grid createGrid(int numRows, int numCols, int cellSize) {
    Grid grid;
    grid.numRows = numRows;
    grid.numCols = numCols;
    grid.cellSize = cellSize;
    return grid;
}

static void initialize(Grid *grid) {
    for (int row = 0; row < grid->numRows; row++) {
        for (int col = 0; col < grid->numCols; col++) {
            cells[row][col] = 0;
        }
    }
}

// Function to draw the grid on the screen
static void drawGrid(Grid grid) {
    for (int row = 0; row < grid.numRows; row++) {
        for (int col = 0; col < grid.numCols; col++) {
            printf("%d ", cells[row][col]); // Print the actual grid value followed by a space
        }
        printf("\n");  // New line after each row
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 800;

    // Initialize window
    InitWindow(screenWidth, screenHeight, "Tetris");

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Grid grid = createGrid(GRID_ROW, GRID_COL, 30);
    initialize(&grid);
    drawGrid(grid);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);  // Clear the screen with a white color
        
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

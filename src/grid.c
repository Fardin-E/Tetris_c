//
// Created by freid on 10/01/25.
//

#include "grid.h"

Grid init_grid(int numRows, int numCols, int cellSize) {
    Grid grid = {
        .numRows = numRows,
        .numCols = numCols,
        .cellSize = cellSize,
        };

    grid.cells = (int *)malloc(sizeof(int) * numRows * numCols);

    for (int row = 0; row < numRows; row++) {
      for (int col = 0; col < numCols; col++) {
        grid.cells[row * numCols + col] = 0;
      }
    }

    return grid;
}

void draw_grid(Grid *grid) {
  for (int row = 0; row < grid->numRows; row++) {
    for (int col = 0; col < grid->numCols; col++) {
      grid->cells[row * grid->numCols + col] = 0;
    }
  }
}


//
// Created by freid on 10/01/25.
//
#pragma once
#include "header.h"
#ifndef GRID_H
#define GRID_H

typedef struct {
  int numRows;
  int numCols;
  int cellSize;
  int cellValue;
  int *cells;
} Grid;

typedef struct
{
  Color darkGrey = { 26, 31, 40, 255};
  Color green = { 47, 230, 23, 255};
  Color red = { 232, 18, 18, 255};
  Color orange = { 226, 116, 17, 255};
  Color yellow = { 237, 234, 4, 255};
  Color purple = { 166, 0, 247, 255};
  Color cyan = { 21, 204, 209, 255};
  Color blue = { 13, 64, 216, 255};
} Tet_Color;

Grid init_grid(int numRows, int numCols, int cellSize);
void draw_grid(Grid *grid);
void print_grid(Grid *grid);

#endif //GRID_H

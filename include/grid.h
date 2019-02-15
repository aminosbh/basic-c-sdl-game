/*
 * Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

#include "utils.h"

#define GRID_MAX_X_CELLS    (20)
#define GRID_MAX_Y_CELLS    (20)

struct Cell
{
    // Rect dimensions and color
    SDL_Rect rect;
    SDL_Color rectColor;

    // Border dimensions and color
    SDL_Rect border;
    SDL_Color borderColor;
};
typedef struct Cell Cell;


struct Grid
{
    // x, y, width, height
    SDL_Rect rect;

    // Grid background color
    SDL_Color backgroundColor;

    // Grid border thickness and color
    unsigned int border;
    SDL_Color borderColor;

    // Number of cells over the x axis
    int xCells;
    // Number of cells over the y axis
    int yCells;

    // Cells boder thickness and color
    unsigned int cellsBorder;
    SDL_Color cellsBorderColor;

    // Matrix of Cells
    Cell cells[GRID_MAX_X_CELLS][GRID_MAX_Y_CELLS];
};
typedef struct Grid Grid;

int Grid_ajustSize(Grid *grid);
void Grid_alignCenter(Grid *grid, int screenWidth, int screenHeight);

bool Grid_init(Grid *grid);
void Grid_initCell(Grid *grid, Cell *cell, int i, int j, SDL_Color color, SDL_Color borderColor);

void Grid_render(Grid *grid, SDL_Renderer *renderer);
void Grid_renderCell(Cell *cell, SDL_Renderer *renderer);

#endif // GRID_H

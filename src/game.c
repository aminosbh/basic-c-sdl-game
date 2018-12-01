/*
 * Copyright (c) 2018 Amine Ben Hassouna <amine.benhassouna@gmail.com>
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

#include "game.h"

bool Game_start(SDL_Renderer *renderer, int w, int h)
{
    // Init grid
    Grid grid = {0};

    // Set grid dimensions
    int margin = 50;
    grid.rect.w = MIN(w - margin * 2, h - margin * 2);
    grid.rect.h = grid.rect.w;

    // Set number of cells
    grid.xCells = 10;
    grid.yCells = 10;

    // Set cells interspace
    grid.xInterspace = 6;
    grid.yInterspace = 6;

    // Set backgroud and border color
    grid.backgroundColor = COLOR_DARK_GRAY;
    grid.borderColor = COLOR_GRAY;

    // Ajust size and center
    Grid_ajustSize(&grid);
    Grid_alignCenter(&grid, w, h);

    if(!Grid_init(&grid))
    {
        fprintf(stderr, "Grid fail to initialize !\n");
        return false;
    }

    // Initialize framerate manager : 30 FPS
    FPSmanager fpsmanager;
    SDL_initFramerate(&fpsmanager);
    SDL_setFramerate(&fpsmanager, 30);

    // Initialize start time (in ms)
    long long last = Utils_time();

    // Falling brick coordinates
    int fallingBrickX = grid.xCells / 2;
    int fallingBrickY = -1;
    int fallingBrickSpeed = 4;


    // Event loop exit flag
    bool quit = false;

    // Event loop
    while(!quit)
    {
        SDL_Event e;

        // Get available event
        while(SDL_PollEvent(&e))
        {
            // User requests quit
            if(e.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;

                case SDLK_RIGHT:
                    if(fallingBrickY != -1 && fallingBrickX < grid.xCells - 1)
                    {
                        // Un-color last position
                        grid.cells[fallingBrickX][fallingBrickY].rectColor = grid.backgroundColor;

                        // Color new position
                        fallingBrickX++;
                        grid.cells[fallingBrickX][fallingBrickY].rectColor = COLOR_RED;
                    }
                    break;

                case SDLK_LEFT:
                    if(fallingBrickY != -1 && fallingBrickX > 0)
                    {
                        // Un-color last position
                        grid.cells[fallingBrickX][fallingBrickY].rectColor = grid.backgroundColor;

                        // Color new position
                        fallingBrickX--;
                        grid.cells[fallingBrickX][fallingBrickY].rectColor = COLOR_RED;
                    }
                    break;
                }
            }
        }

        // Move the falling brick
        if(Utils_time() - last >= 1000 / fallingBrickSpeed)
        {
            if(fallingBrickY >= 0)
            {
                // Un-color the falling brick last position
                grid.cells[fallingBrickX][fallingBrickY].rectColor = grid.backgroundColor;
            }

            if(fallingBrickY < grid.yCells - 1)
            {
                // Go to next position
                fallingBrickY++;

                // Color the falling brick new position
                grid.cells[fallingBrickX][fallingBrickY].rectColor = COLOR_RED;
            }
            else
            {
                // Reset position
                fallingBrickY = -1;
            }

            last = Utils_time();
        }

        // Set background color
        Utils_setBackgroundColor(renderer, COLOR_DARK_GRAY);

        // Render grid
        Grid_render(&grid, renderer);

        // Show message
        stringRGBA(renderer, grid.rect.x + grid.xCells, grid.rect.y - 20,
                   "This is a falling brick < Press RIGTH and LEFT to move >",
                   COLOR_LIGHT_GRAY.r, COLOR_LIGHT_GRAY.g, COLOR_LIGHT_GRAY.b, COLOR_LIGHT_GRAY.a);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay
        SDL_framerateDelay(&fpsmanager);
    }

    return true;
}

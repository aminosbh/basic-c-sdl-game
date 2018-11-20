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
    int padding = 50;
    grid.rect.w = MIN(w - padding*2, h - padding*2);
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
        }

        // Set background color
        Utils_setBackgroundColor(renderer, COLOR_DARK_GRAY);

        // Render grid
        Grid_render(&grid, renderer);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay
        SDL_framerateDelay(&fpsmanager);
    }

    return true;
}

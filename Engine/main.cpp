//#include "pch.h"

#include <iostream>
#include <chrono>

#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;
using namespace chrono;

const float MS_PER_FRAME = 16.7f;
const int SCALE_FACTOR = 2;
const int WIDTH = 1920;
const int HEIGHT = 1080;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window* gameWindow = SDL_CreateWindow(
        "Hello, World!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    if (nullptr == gameWindow) {
        printf("Could not create SDL Window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Surface* gameScreen = SDL_GetWindowSurface(gameWindow);
    if (nullptr == gameScreen) {
        printf("Could not get gameWindow surface: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    bool exitSignalled = false;
    float lastTime = 0.0f;
    // main game loop
    while (!exitSignalled) {
        SDL_Event event;
        bool keyStates[SDLK_z + 1] = { 0 };
        // event loop
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
                //Quit();
                exitSignalled = true;
                break;
            }
            case SDL_KEYDOWN: {
                keyStates[event.key.keysym.sym] = true;
               // printf("keydown: %i\n", event.key.keysym.sym);
                break;
            }
            case SDL_KEYUP: {
                keyStates[event.key.keysym.sym] = false;
                //printf("keyup: %i\n", event.key.keysym.sym);
                break;
            }
            case SDL_MOUSEMOTION: {  
                int mouseX, mouseY = 0;
                SDL_GetMouseState(&mouseX, &mouseY);
                break;
            }
            }
        }// end event loop

        if (keyStates[SDLK_z] == true) {
            printf("z pressed\n");
        }

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), lastTime + MS_PER_FRAME)) {
            //wait if we're above our target framerate
        }

        float now = SDL_GetTicks();
        float deltaTime = (now - lastTime) / 1000.0f;
        //clamp deltaTime to a max in case we were debugging
        deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
        lastTime = now;

        //TODO: Update entities here!

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //TODO: Render all models here!

        SDL_RenderPresent(renderer);
    }// end main game loop

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(gameWindow);
    gameWindow = nullptr;
    SDL_Quit();

    return EXIT_SUCCESS;
}

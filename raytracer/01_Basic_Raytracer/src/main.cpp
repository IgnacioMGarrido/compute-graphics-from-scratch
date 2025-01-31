#include "SDL_render.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Image.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;


int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        std::cerr << "Error: Failed to initialize SDL video - " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Window",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!window) {
        std::cerr << "Error: Failed to create window - " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    rt::Image rtImage;
    rtImage.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, renderer);

    for (int x = 0; x < WINDOW_WIDTH; x++) {
        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            double red = (static_cast<double>(x) / WINDOW_WIDTH) * 255.0;
            double green = (static_cast<double>(y) / WINDOW_HEIGHT) * 255.0;
            rtImage.SetPixel(x, y, red, green, 0);
        }
    }


    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            //Render
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            rtImage.Display();

            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

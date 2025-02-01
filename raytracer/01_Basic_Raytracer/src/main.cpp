#include <SDL2/SDL.h>
#include <SDL2/SDL_test_font.h>
#include <iostream>
#include <sstream>
#include "Scene.h"
#include "Image.h"
#include "Camera.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;


// Variables para FPS
Uint32 lastTime = 0, currentTime;
int frames = 0;
float fps = 0.0f;

namespace {
    void CalculateFPS() {
        frames++;
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + 1000) {
            fps = frames * 1000.0f / (currentTime - lastTime);
            lastTime = currentTime;
            frames = 0;
        }
    }
}

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
    rt::Camera camera({0.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 1.0}, 90, 16.0 / 9.0);

    auto screenCenter = camera.getScreenCenter();
    auto cameraScreenU = camera.getU();
    auto cameraScreenV = camera.getV();

    std::cout << "Camera Screen Center: " << screenCenter << std::endl;
    std::cout << "Camera Screen U: " << cameraScreenU << std::endl;
    std::cout << "Camera Screen V: " << cameraScreenV << std::endl;
    rt::Scene rtScene;
    rt::Image rtImage;
    rtImage.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, renderer);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        CalculateFPS();
        //Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render Image
        rtScene.Render(rtImage);

        // Render FPSs
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        std::ostringstream fpsText;
        fpsText << "FPS: " << static_cast<int>(fps);
        SDLTest_DrawString(renderer, 10, 10, fpsText.str().c_str());
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_test_font.h>
#include <iostream>
#include <sstream>
#include "Scene.h"
#include "Image.h"
#include "Camera.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

double mouseSensitivity = 0.1;
double yaw = 0, pitch = 0;
// Variables para FPS
Uint32 lastTime = 0, currentTime;
int frames = 0;
float fps = 0.0f;
float dt = 0;

namespace {
    void CalculateFPS() {
        static Uint32 lastFrameTime = SDL_GetTicks();
        frames++;
        currentTime = SDL_GetTicks();

        dt = (currentTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentTime; // Actualizar el tiempo del último frame
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
            //TODO: This i broken. don't bother with rotations.
            /*if (event.type == SDL_MOUSEMOTION) {*/
            /*    double deltaX = event.motion.xrel * mouseSensitivity;*/
            /*    double deltaY = event.motion.yrel * mouseSensitivity;*/
            /**/
            /*    rtScene.GetSceneCamera().Rotate(deltaX, -deltaY);*/
            /*}*/
        }

        static const float speed = 5.0f;
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_Q]) { rtScene.GetSceneCamera().Move({0.0, 0.0, -3.0},speed * dt); }
        if (keystate[SDL_SCANCODE_E]) { rtScene.GetSceneCamera().Move({0.0, 0.0, 3.0}, speed * dt); }
        if (keystate[SDL_SCANCODE_A]) { rtScene.GetSceneCamera().Move({-3.0, 0.0, 0.0},speed * dt); }
        if (keystate[SDL_SCANCODE_D]) { rtScene.GetSceneCamera().Move({3.0, 0.0, 0.0}, speed * dt); }
        if (keystate[SDL_SCANCODE_W]) { rtScene.GetSceneCamera().Move({0.0, 3.0, 0.0}, speed * dt); }
        if (keystate[SDL_SCANCODE_S]) { rtScene.GetSceneCamera().Move({0.0, -3.0, 0.0},speed * dt); }


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

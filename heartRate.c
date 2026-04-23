#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 400

int waveform[WIDTH];   // store history

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "PulseGuard Monitor",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int running = 1;
    SDL_Event event;

    float t = 0;

    // Initialize waveform
    for (int i = 0; i < WIDTH; i++) {
        waveform[i] = HEIGHT / 2;
    }

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        // Generate pulse
        float pulse = sin(t) + 0.5 * sin(2 * t) + 0.333 * sin(3 * t) + 0.25 * sin(4 * t);
        t += 0.1;

        int newY = (HEIGHT / 2) - (int)(pulse * 80);

        // SHIFT LEFT (scroll effect)
        for (int i = 0; i < WIDTH - 1; i++) {
            waveform[i] = waveform[i + 1];
        }

        waveform[WIDTH - 1] = newY;

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw full trace
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        for (int i = 1; i < WIDTH; i++) {
            SDL_RenderDrawLine(renderer, i - 1, waveform[i - 1], i, waveform[i]);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

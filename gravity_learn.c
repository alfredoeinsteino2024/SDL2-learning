#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 400

int main(int argc, char *argv[]){
    float gravity = 800.0f;
    float velocityY = 0.0f;

    SDL_Rect Player = {0, 0, 20, 50};
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        "Gravity Simulation", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WIDTH, 
        HEIGHT, 
        0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;
    Uint32 last_time = SDL_GetTicks();

    while(running){
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }
        velocityY += gravity * delta_time;
        Player.y += (int)(velocityY * delta_time);

        int ground = HEIGHT - 50;
        if(Player.y + Player.h >= ground){
            Player.y = ground - Player.h;
            velocityY = 0.0f;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
        SDL_Rect groundRect = {0, ground, WIDTH, 50};
        SDL_RenderFillRect(renderer, &groundRect);

        SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
        SDL_RenderFillRect(renderer, &Player);

    SDL_RenderPresent(renderer);
    }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
    return 0;
}

#include<stdio.h>
#include<SDL2/SDL.h>
#include<stdbool.h>

#define WIDTH 800
#define HEIGHT 700

int main(int argc, char *argv[]){
    float gravity = 800.0f;
    float velocityY = 0.0f;
    float playerY = 250.0f;

    SDL_Rect Player = {0, 250, 30, 50};
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("GRAVITY SIMULATION", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WIDTH, 
        HEIGHT, 
        SDL_WINDOW_SHOWN);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    bool running = true;
    SDL_Event event;

    Uint32 last_time = SDL_GetTicks();
    while(running){
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT){
                running = false;
            }
        }
    
        velocityY += gravity * delta_time;
        
        playerY  += (velocityY * delta_time);
        
        int ground = HEIGHT - 50;

        if(playerY + Player.h >= ground){
            playerY = ground - Player.h;
            velocityY = 0.0f;
        }
        Player.y = (int)playerY;
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 180, 255);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 20, 255 , 0, 240);
        SDL_Rect groundRect = {0, ground, WIDTH, 50};
        SDL_RenderFillRect(renderer, &groundRect);

        SDL_SetRenderDrawColor(renderer, 230, 0, 0, 255);
        SDL_RenderFillRect(renderer, &Player);

        SDL_RenderPresent(renderer);
        
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>

int main(int argc, char *argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) !=0){
        printf("SDL not initializing: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow(
        "Alfred Window",
        SDL_WINDOWPOS_CENTERED,  
        SDL_WINDOWPOS_CENTERED,
        850, 
        600,
        0
    );
    if(!window){
        printf("Window not initializing : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        printf("Renderer not initializing : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    bool running = true;
   
        SDL_Rect box;
        box.x = 200;
        box.y = 150;
        box.w = 150;
        box.h = 100;

        int speed = 5;
 while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                       box.y -=speed;
                       break;
                       
                    case SDLK_DOWN:
                       box.y +=speed;
                       break;

                    case SDLK_LEFT:
                       box.x -= speed;
                       break;
                       
                    case SDLK_RIGHT:
                       box.x += speed;
                       break;
                }
            }
        } 
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &box);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

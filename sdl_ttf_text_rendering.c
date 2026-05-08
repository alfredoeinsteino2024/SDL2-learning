#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include <SDL2/SDL_ttf.h>

#define font_size 24

int main(int argc, char *argv[]){

    #define WIDTH 400
    #define HEIGHT 600

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("TTF_TEST_WINDOW", 
                         SDL_WINDOWPOS_CENTERED, 
                         SDL_WINDOWPOS_CENTERED, 
                         WIDTH, 
                         HEIGHT, 
                         SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if(TTF_Init() == -1){
        printf("TTF not initialized: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // LOADING FONT
    TTF_Font *font = TTF_OpenFont("Roboto_Condensed-Regular.ttf", font_size);
    if(!font){
        printf("%s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Color white = { 255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Hello ALFRED", white);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect rect = {100, 100, 120, 40};

    SDL_Event event;
    bool running = true;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 150, 150, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, &rect);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

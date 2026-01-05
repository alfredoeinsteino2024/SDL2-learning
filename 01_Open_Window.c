#include <SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <stdint.h>


#define WINDOW_TITLE "01 Open Window"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define AUTO_CLOSE_TIME_MS 5000

struct Game 
{
  SDL_Window *window;
  SDL_Renderer *renderer;
};

bool sdl_initialize(struct Game *game);
void game_cleanup(struct Game *game);

int main(int argc, char *argv[]){
  struct Game game = {
    .window = NULL,
    .renderer = NULL,
  };
   
 if(sdl_initialize(&game)){ 
   printf("All bad! Initialization failed, check stderr.\n");
   game_cleanup(&game); 
  return 1;
 }

   SDL_SetRenderDrawColor(game.renderer, 135, 206, 235, 255);
   SDL_RenderClear(game.renderer);
   SDL_RenderPresent(game.renderer);

  bool running = true;
  SDL_Event event;
  Uint32 start_time = SDL_GetTicks();


  while(running){
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        running = false;

      }
    }
    if(SDL_GetTicks() - start_time >= AUTO_CLOSE_TIME_MS){
      running = false;
    }
    SDL_Delay(10);
  }

 game_cleanup(&game);
 printf("All good! Window closed after %dms.\n", AUTO_CLOSE_TIME_MS);   
 return 0;
}

void game_cleanup(struct Game *game){
 SDL_DestroyRenderer(game->renderer); 
 SDL_DestroyWindow(game->window);
 SDL_Quit();
}
 
bool sdl_initialize(struct Game *game){
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return true;
  }

   game->window = SDL_CreateWindow(
    WINDOW_TITLE,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT, 
    0
    );
      
if(!game->window){
   fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
   return true;
}

//  SDL_Renderer *SDL_CreateRenderer(SDL_Window * window, int index, Uint32 flags);
 game->renderer = SDL_CreateRenderer(game->window, -1, 0);
 if(!game->renderer){
   fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
   return true;
}

  return false;
  }

#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>

#define WINDOW_HEIGHT 650
#define WINDOW_WIDTH 850

typedef struct {
    float x, y, w, h;
} WorldRect;

typedef struct {
    float x, y;
} Camera;

SDL_Rect WorldToScreen(WorldRect w, Camera cam){
    SDL_Rect r;
    r.w = w.w;
    r.h = w.h;
    r.x = w.x - cam.x + WINDOW_WIDTH / 2;
    r.y = w.y - cam.y + WINDOW_HEIGHT / 2;
    return r;
}

int main(int argc, char *argv[]){

    WorldRect Player = {23, 100, 50, 50};
    WorldRect Tree = {290, -100, 100, 50};
    WorldRect Car = {100, -200, 150, 50}; // I WILL BE USING A BLUE CAR FOR THIS
    WorldRect Truck = {-80, 200, 50, 50}; // I SHOULD BE USING A BROWN TRUCK FOR THIS

    Camera cam = {0, 0};

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL Initializing failed !!: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Box Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if(!window){
        printf("Window Initializing failed !!: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        printf("Renderer initializing failed : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Uint32 last_time = SDL_GetTicks();

    SDL_Event event;
    bool running = true;
    bool up = false; bool down = false;  bool right = false;  bool left = false;

    while(running){
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;
        float move_amount = 200.0f * delta_time;

        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT){
                running = false;
            }
            if(event.type == SDL_KEYUP){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: up = false;        break;
                case SDLK_DOWN: down = false;    break;
                case SDLK_RIGHT: right = false;  break;
                case SDLK_LEFT: left = false;    break;
                default:
                    break;
                }
            }
             if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: up = true;        break;
                case SDLK_DOWN: down = true;    break;
                case SDLK_RIGHT: right = true;  break;
                case SDLK_LEFT: left = true;    break;
                default:
                    break;
                }
            }
        }


        if(up) Player.y -=     move_amount;
        if(down) Player.y +=   move_amount;
        if(right) Player.x +=  move_amount;
        if(left) Player.x -=   move_amount;

        cam.x = Player.x + Player.w / 2;
        cam.y = Player.y + Player.h / 2;

        SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect SPlayer = WorldToScreen(Player, cam);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0 , 255);
        SDL_RenderFillRect(renderer, &SPlayer);

        SDL_Rect STree = WorldToScreen(Tree, cam);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255 , 255);
        SDL_RenderFillRect(renderer, &STree);

        SDL_Rect SCar = WorldToScreen(Car, cam);
        SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
        SDL_RenderFillRect(renderer, &SCar);
        
        SDL_Rect STruck= WorldToScreen(Truck, cam);
        SDL_SetRenderDrawColor(renderer, 255, 0, 150, 255);
        SDL_RenderFillRect(renderer, &STruck);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

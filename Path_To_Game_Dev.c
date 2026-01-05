#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 700

typedef struct{
    float x, y, w, h;
} WorldRect;

typedef struct{
    float x, y;
} Camera;

SDL_Rect worldToScreen(WorldRect w, Camera cam){
    SDL_Rect r;
    r.h = w.h;
    r.w = w.w;
    r.x = w.x - cam.x + WINDOW_WIDTH / 2;
    r.y = w.y - cam.y + WINDOW_HEIGHT / 2;
    return r;
}

int main(int argc, char *argv[]){
    WorldRect player = {100, 200, 50, 50};
    WorldRect brick = {150, 200, 100, 100}; 
    WorldRect Tree = {-100, -200, 100, 50}; 
    WorldRect Rock = {300, 200, 100, 80}; 
    WorldRect Car = {100, -200, 150, 50}; // I WILL BE USING A BLUE CAR FOR THIS
    WorldRect Truck = {-80, 200, 50, 50}; // I SHOULD BE USING A BROWN TRUCK FOR THIS
    WorldRect Person = {-120, 250, 50, 50};

    Camera cam = {0, 0};

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL not initializing: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "First Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if(!window){
        printf("Window not initializing: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        printf("Renderer not initializing : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1 ;
    }

    SDL_Event event;
    bool running = true;
    bool up = false; bool down = false; bool right = false; bool left = false;
    int speed = 2;
    
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT){
                running = false;
            }
            if(event.type == SDL_KEYUP){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: up = false;       break;
                case SDLK_DOWN: down = false;   break;
                case SDLK_LEFT: left = false;   break;
                case SDLK_RIGHT: right = false; break;      
                default:
                    break;
                }
            }
            if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: up = true;       break;
                case SDLK_DOWN: down = true;   break;
                case SDLK_LEFT: left = true;   break;
                case SDLK_RIGHT: right = true; break;      
                default:
                    break;
                }
            }
           
        }

            if(up) player.y -= speed;
            if(down) player.y += speed;
            if(right) player.x += speed;
            if(left) player.x -= speed;

            cam.x = player.x + player.w/2;
            cam.y = player.y + player.h/2;


        SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect Splayer = worldToScreen(player, cam);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &Splayer);
        
        SDL_Rect Sbrick = worldToScreen(brick, cam);
        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
        SDL_RenderFillRect(renderer, &Sbrick);
        
        SDL_Rect STree = worldToScreen(Tree, cam);
        SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
        SDL_RenderFillRect(renderer, &STree);
        
        SDL_Rect SRock = worldToScreen(Rock, cam);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
        SDL_RenderFillRect(renderer, &SRock);
        
        SDL_Rect SCar = worldToScreen(Car, cam);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &SCar);
        
        SDL_Rect STruck= worldToScreen(Truck, cam);
        SDL_SetRenderDrawColor(renderer, 255, 0, 150, 255);
        SDL_RenderFillRect(renderer, &STruck);

        SDL_Rect SPerson= worldToScreen(Person, cam);
        SDL_SetRenderDrawColor(renderer, 255, 0, 150, 255);
        SDL_RenderFillRect(renderer, &SPerson);

        SDL_RenderPresent(renderer);
        
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}

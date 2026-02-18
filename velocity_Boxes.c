#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
    float x, y, w, h;
} WorldRect;

typedef struct{
    float x, y;
} Camera;

SDL_Rect worldToScreen(WorldRect w, Camera cam){
    SDL_Rect r;
    r.w = w.w;
    r.h = w.h;
    r.x = w.x - cam.x + 450; 
    r.y = w.y - cam.y + 325;
    return r; 
}

int main(int argc, char *argv[]) {
    WorldRect player = {-100, 50, 40, 40};
    Camera cam = {0, 0};
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL not initializing: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "GRASS",
        SDL_WINDOWPOS_CENTERED,        
        SDL_WINDOWPOS_CENTERED,
        900,
        650,
        0
    );

    if (!window) {
        printf("Window not initializing : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        printf("Renderer not initializing: %s\n", SDL_GetError());
    }

    SDL_Event event;
    bool running = true;

    SDL_Rect box = {0, 0, 200, 100};
    SDL_Rect box1 = {500, 0, 200, 100};

    bool up = false, down = false, left = false, right = false;

    float vx = 0;
    float vy = 0;
    float speed = 2.0f;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            // Key pressed
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:    up = true;    break;
                    case SDLK_DOWN:  down = true;  break;
                    case SDLK_LEFT:  left = true;  break;
                    case SDLK_RIGHT: right = true; break;
                }
            }

            // Key released
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:    up = false;    break;
                    case SDLK_DOWN:  down = false;  break;
                    case SDLK_LEFT:  left = false;  break;
                    case SDLK_RIGHT: right = false; break;
                }
            }
        }  

        if (up)    vy = -speed;
        if (down)  vy = speed;
        if (left)  vx = -speed;
        if (right) vx = speed;

        box.x += vx;
        box.y +=vy;

        // Keep box inside the screen
        if (box.x <= 1 && box1.x <= 1 ){box.x = 0;  box1.x = 0;} 
        if (box.y <= 1 && box1.y <= 1 ){ box.y = 0;  box1.y =0;}
        

        if (box.x >= 900 && box1.x >= 900 ) {box.x = 900  - box.w;  box1.x = 900; }
        if (box.y >= 650 && box1.y >= 650)  { box.y = 650 - box.h;  box1.y = 650;  }

        // Draw
        SDL_SetRenderDrawColor(renderer, 0, 230, 0, 100);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &box);

        SDL_SetRenderDrawColor(renderer, 235, 0, 0, 255);
        SDL_RenderFillRect(renderer, &box1);

        SDL_RenderPresent(renderer); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT  650

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
    r.x = w.x - cam.x + WINDOW_WIDTH / 2; 
    r.y = w.y - cam.y + WINDOW_HEIGHT/ 2;
    return r; 
}

bool checkOverlap(WorldRect A, WorldRect B){
    if(A.x >= B.x + B.w) return false; // A is right of B
    if(A.x + A.w <= B.x) return false; // A is left of B
    if(A.y + A.h <= B.y) return false; // A is completely Above
    if(A.y >= B.y + B.h) return false; // A is completely Below

    return true;
}

int main(int argc, char *argv[]) {
    WorldRect player = {-100, 50, 40, 40};
    Camera cam = {0, 0};
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL not initializing: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Velocity_Test",
        SDL_WINDOWPOS_CENTERED,        
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    if (!window) {
        printf("Window not initializing : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Renderer not initializing: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    bool running = true;

    WorldRect box = {0, 0, 200, 100};
    WorldRect box1 = {500, 0, 200, 100};

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
        
        vx = 0;
        vy = 0;

        // MOVING AT CONSTANT SPEED
        if (up)    vy = -speed;
        if (down)  vy = speed;
        if (left)  vx = -speed;
        if (right) vx = speed;

        box.x += vx;
        box.y +=vy;

        // CREATION OF BOUNDARY
        float World_max_x = 1000.0f;
        float World_min_x = -1000.0f;
        float World_max_y = 800.0f;
        float World_min_y = -800.0f;

        if(box.x + box.w > World_max_x ) box.x = World_max_x;
        if(box.x < World_min_x ) box.x = World_min_x;

        if(box.y + box.w > World_max_y ) box.y = World_max_y;
        if(box.y < World_min_y ) box.y = World_min_y;

        if(checkOverlap(player, box)){
            box.x -= vx;
            box.y -= vy;
        }

        cam.x = box.x + box.w / 2;

        SDL_SetRenderDrawColor(renderer, 0, 230, 0, 100);
        SDL_RenderClear(renderer);
        
        SDL_Rect Sbox = worldToScreen(box, cam);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &Sbox);
        
        SDL_Rect Sbox1 = worldToScreen(box1, cam);
        SDL_SetRenderDrawColor(renderer, 235, 0, 0, 255);
        SDL_RenderFillRect(renderer, &Sbox1);

        SDL_RenderPresent(renderer); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 650

typedef struct {
    float x, y, w, h;
} WorldRect;

typedef struct {
    float x, y;
} Camera;

bool check_Overlap(WorldRect A, WorldRect B){
    if(A.x + A.w <= B.x) return false;
    if(A.x >= B.x + B.w) return false;
    if(A.y + A.h <= B.y) return false;
    if(A.y >= B.y + B.h) return false;

    return true;
}

SDL_Rect WorldToScreen(WorldRect w, Camera cam){
    SDL_Rect r;
    r.w = w.w;
    r.h = w.h;
    r.x = w.x - cam.x + WINDOW_WIDTH / 2;
    r.y = w.y - cam.y + WINDOW_HEIGHT / 2;

    return r;
}

int main(int argc, char *argv[]){
    WorldRect Player = {0, 0, 150, 150};
    WorldRect Tree = {300, 300, 400, 200};
    WorldRect Truck = {700, 700, 400, 200};  
    WorldRect Car = {1100, 1100, 400, 200}; // Stop and continue

    WorldRect Rock = {1500, 1500, 400, 200};
    WorldRect House = {1900, 1900, 400, 200};  
    WorldRect Container = {2300, 2300, 400, 200};
    WorldRect Bridge = {2700, 2700, 400, 200};
    WorldRect Church = {3100, 3100, 400, 200};  
    WorldRect Mosque = {3500, 3500, 400, 200};

    
    Camera cam = {0,0};

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL not initializing: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Home Game",
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
        printf("REnderer not initializing: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    SDL_Event event;
    bool running = true;
    bool up = false; bool down = false; bool right = false; bool left = false;
    Uint32 last_Time = SDL_GetTicks();

    while(running){
        Uint32 current_Time = SDL_GetTicks();
        float delta_Time = (current_Time - last_Time) / 1000.0f;
        last_Time = current_Time;
        float move_Amount = 200.0f * delta_Time;

        while(SDL_PollEvent(&event)){
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

        float old_x = Player.x;
        float old_y = Player.y;

        if(up) Player.y -= move_Amount;
        if(down) Player.y += move_Amount;
        if(right) Player.x += move_Amount;
        if(left) Player.x -= move_Amount;

        if(check_Overlap(Player, Tree) ||check_Overlap(Player, Truck)|| check_Overlap(Player, Car)|| check_Overlap(Player, Rock)|| check_Overlap(Player, House)|| check_Overlap(Player, Container)|| check_Overlap(Player, Bridge)|| check_Overlap(Player, Church)|| check_Overlap(Player, Mosque)){
            Player.x = old_x;
            Player.y = old_y;
        }
   
        cam.x = Player.x + Player.w /2;
        cam.y = Player.y + Player.h /2; 

        SDL_SetRenderDrawColor(renderer, 20, 150, 20, 255);
        SDL_RenderClear(renderer);

        SDL_Rect sPlayer = WorldToScreen(Player, cam);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &sPlayer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // THIS DRAW OUTLINES FOR THE RECT
        SDL_RenderDrawRect(renderer, &sPlayer);

        SDL_Rect sTree = WorldToScreen(Tree, cam);
        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
        SDL_RenderFillRect(renderer, &sTree);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // THIS DRAW OUTLINES FOR THE RECT
        SDL_RenderDrawRect(renderer, &sTree);


        SDL_Rect sTruck = WorldToScreen(Truck, cam);
        SDL_SetRenderDrawColor(renderer, 0, 0, 130, 255);
        SDL_RenderFillRect(renderer, &sTruck);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // THIS DRAW OUTLINES FOR THE RECT
        SDL_RenderDrawRect(renderer, &sTree);


        SDL_Rect sCar = WorldToScreen(Car, cam);
        SDL_SetRenderDrawColor(renderer, 0, 200, 130, 255);
        SDL_RenderFillRect(renderer, &sCar);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // THIS DRAW OUTLINES FOR THE RECT  
        SDL_RenderDrawRect(renderer, &sCar);

        //I WILL CONTINUE FROM HERE LATER

        SDL_Rect sRock = WorldToScreen(Rock, cam);
        SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
        SDL_RenderFillRect(renderer, &sRock);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // THIS DRAW OUTLINES FOR THE RECT  
        SDL_RenderDrawRect(renderer, &sRock);

        SDL_Rect sHouse = WorldToScreen(House, cam);
        SDL_SetRenderDrawColor(renderer, 0, 180, 255, 255);
        SDL_RenderFillRect(renderer, &sHouse);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // THIS DRAW OUTLINES FOR THE RECT  
        SDL_RenderDrawRect(renderer, &sHouse);

        SDL_Rect sContainer = WorldToScreen(Container, cam);
        SDL_SetRenderDrawColor(renderer, 0, 180, 0, 255);
        SDL_RenderFillRect(renderer, &sContainer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // THIS DRAW OUTLINES FOR THE RECT  
        SDL_RenderDrawRect(renderer, &sContainer);

        SDL_Rect sBridge = WorldToScreen(Bridge, cam);
        SDL_SetRenderDrawColor(renderer, 160, 82, 45, 255);
        SDL_RenderFillRect(renderer, &sBridge);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // THIS DRAW OUTLINES FOR THE RECT  
        SDL_RenderDrawRect(renderer, &sBridge);

        SDL_Rect sChurch = WorldToScreen(Church, cam);
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &sChurch);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // THIS DRAW OUTLINES FOR THE RECT  
        SDL_RenderDrawRect(renderer, &sChurch);


        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

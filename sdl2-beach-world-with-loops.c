#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL_image.h>

#define WINDOW_WIDTH 1250
#define WINDOW_HEIGHT 700


typedef struct{
    float x, y, w, h;
} WorldRect;

typedef struct{
    float x, y;
} Camera;


bool checkOverlap(WorldRect A, WorldRect B){
    if(A.x >= B.x + B.w) return false;
    if(A.x + A.w <= B.x) return false;
    if(A.y >= B.y + B.h) return false;
    if(A.y + A.h <= B.y) return false;

    return true;
}

SDL_Rect WorldToScreen(WorldRect w, Camera cam){
    SDL_Rect r;
    r.h = w.h;
    r.w = w.w;
    r.x = w.x - cam.x + WINDOW_WIDTH / 2;
    r.y = w.y - cam.y + WINDOW_HEIGHT / 2;
    return r;
}

int main(int argc, char *argv[]){

   WorldRect Player = {0, 0, 100, 100}; 
    // OBJECTS IN THE WORLD COORDINATE
    WorldRect Objects[9] = {
        {-500, 700, 300, 200}, // Car1
        {400, 700, 300, 200}, // Car
        {1000, 400, 300, 200}, // Truck
        {150, 80, 500, 500}, // Hotel
        {-1000, 100, 15000, 6000},  // Beach
        {-1800, -600, 1000, 500}, // Rock
        {0,-6000, 1000, 100000},     // Road
        {1000, 3100, 10, 200}, // Tree1
        {500, 50, 300, 700}, // Tree
    };
    // *TRUE* TELLS US IT IS SOLID SO IT WOULD COLLIDE BUT *FALSE* TELLS US THAT IT ISN'T SOLID, AND CAN BE COLLIDED WITH OR OVERLAPED
    bool Collidable[9] = {
        true, // Car1
        true, // Car
        true, // Truck
        false, // Hotel
        false, // Beach
        true, // Rock
        false, // Road
        true, // Tree1
        true  // Tree
    };


    Camera cam = {0, 0};

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL not initializing : %s\n", SDL_GetError());
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
        printf("Renderer not initializing: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture *textures[9];
    const char *filenames[9] = {
        "Car1.png",
        "Car.png",
        "Truck.png",
        "Hotel.png",
        "Beach.png",
        "Rock.png",
        "Road.png",
        "Tree.png",
        "Tree1.png"
    };

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
        printf("PNG Image not loading : %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *Player_Texture = IMG_LoadTexture(renderer, "Player.png");
    if(!Player_Texture){
        printf("Error Loading Player PNG: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    for(int i = 0; i < 9; i++){
        textures[i] = IMG_LoadTexture(renderer, filenames[i]);

        if(!textures[i]){
            printf("%s PNG not loading...: %s\n", filenames[i], IMG_GetError());
            SDL_DestroyTexture(Player_Texture);   
        
         for(int j = 0; j < i; j++){
            SDL_DestroyTexture(textures[j]);
         }
       
         IMG_Quit();
         SDL_DestroyRenderer(renderer);
         SDL_DestroyWindow(window);
         SDL_Quit();
         return 1; 
        }
    }
    

    SDL_Event event;
    bool running = true;
    bool up = false; bool down = false; bool right = false; bool left = false;
    Uint32 last_time = SDL_GetTicks();

    while(running){
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;
        float move_amount = 200.0f * delta_time;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
            if(event.type == SDL_KEYUP){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: up = false;       break; 
                case SDLK_DOWN: down = false;   break;
                case SDLK_RIGHT: right = false; break;
                case SDLK_LEFT: left = false;   break;
                default:
                    break;
                }
            }
            if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: up = true;       break; 
                case SDLK_DOWN: down = true;   break;
                case SDLK_RIGHT: right = true; break;
                case SDLK_LEFT: left = true;   break;
                default:
                    break;
                }
            }
        }

        float old_x = Player.x;
        float old_y = Player.y;

        if(up) Player.y -= move_amount;
        if(down) Player.y += move_amount;
        if(right) Player.x += move_amount;
        if(left) Player.x -= move_amount;

        for(int i = 0; i < 9; i++){
            if(checkOverlap(Player, Objects[i]) && Collidable[i]){
                Player.x = old_x ;
                Player.y = old_y;
                break;
            }
        }

        cam.x = Player.x + Player.w / 2;
        cam.y = Player.y + Player.h / 2;

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 150);
        SDL_RenderClear(renderer);

        for(int i = 0; i < 9; i++){
            SDL_Rect r = WorldToScreen(Objects[i], cam);
            SDL_RenderCopy(renderer, textures[i], NULL, &r);
        }

        SDL_Rect SPlayer = WorldToScreen(Player, cam);
        SDL_RenderCopy(renderer, Player_Texture, NULL, &SPlayer);


        SDL_RenderPresent(renderer); // Make all the renderer visible to the window by drawing


    }
    SDL_DestroyTexture(Player_Texture);
    for(int i = 0; i < 9; i++){
        SDL_DestroyTexture(textures[i]);
    }
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

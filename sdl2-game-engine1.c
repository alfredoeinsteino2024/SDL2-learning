#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL_image.h>

#define WINDOW_WIDTH 1100
#define WINDOW_HEIGHT 700
#define num_Objects 7

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

//NOW IT IS TIME FOR THE COLLISION PART OF THE CODE
bool CheckOverlap(WorldRect A, WorldRect B) {
    if(A.x >= B.x + B.w) return false; // A IS LEFT OF B
    if(A.x + A.w <= B.x) return false; // A IS RIGHT OF B

    if(A.y >= B.y + B.h) return false; // A IS COMPLETELY ABOVE OF B
    if(A.y + A.h <= B.y ) return false; //  A IS COMPLETELY BELOW B
    return true;
}

int main(int argc, char* argv[]){

    WorldRect Player = {-300, -300, 150, 250};
    Camera cam = {0, 0};

    WorldRect Objects[num_Objects] = {  
        {-1000, 0, 2000, 2000},            // "Grass.png", 
        {-100, 1500, 300, 350},           // "Car1.png", 
        {80, 1500, 300, 350},            // "Car.png", 
        {-1000, 1000, 600, 500},        // "Truck.png",
        {200, -3000, 1000, 2000},      // "Beach.png",
        {-200, 1000, 500, 500},       // "hotel.png", 
        {50, 50, 100, 400},          // "tree.png", 
    };

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL not Initializing: %s\n ", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow(
        "Game Engine1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if(!window){
        printf("Window not Initializing: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        printf("Renderer not Initializing: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
   
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
        printf("PNG not Loading...: \n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    } 

    const char *filenames[7] = {
        "Grass.png", 
        "Car1.png", 
        "Car.png", 
        "Truck.png",
        "Beach.png",
        "hotel.png", 
        "tree.png", 
    };

    bool Collidable[num_Objects] = { 
    false,  // Grass    
    true,   // Car1
    true,   // Car
    true,   // Truck
    false,  // Beach
    false,  // Hotel
    true    // Tree
    };

    SDL_Texture *textures[7];

    SDL_Texture* Player_texture = IMG_LoadTexture(renderer, "Player.png");
    if(!Player_texture){
        printf("Player PNG not Loading: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    for(int i = 0; i < num_Objects; i++){
        textures[i] = IMG_LoadTexture(renderer, filenames[i]);
        if(!textures[i]){
            printf("%s PNG not Loading...: %s\n", filenames[i], IMG_GetError());
            SDL_DestroyTexture(Player_texture);

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
    Uint32 last_time = SDL_GetTicks();
    bool running = true;
    bool up = false; bool down = false; bool right = false; bool left = false;

    while(running){

        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time; 
        float move_amount = 400.0f * delta_time; // We are using 200 Frame per Seconds

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }

            if(event.type == SDL_KEYUP){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: up = false;  break; 
                case SDLK_DOWN: down = false;  break; 
                case SDLK_RIGHT: right = false;  break; 
                case SDLK_LEFT: left = false;  break;
                default:
                    break;
                }
            }
            if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: up = true;  break; 
                case SDLK_DOWN: down = true;  break; 
                case SDLK_RIGHT: right = true;  break; 
                case SDLK_LEFT: left = true;  break;
                default:
                    break;
                }
            }
        }
         
        float old_x = Player.x;
        float old_y = Player.y;

        if(up) Player.y -= move_amount;
        if(down) Player.y += move_amount;
        if(left) Player.x -= move_amount;
        if(right) Player.x += move_amount; 

        float world_min_x = -1000;
        float world_max_x = 1500;
        float world_min_y = 0;
        float world_max_y = 2000;

        if(Player.x < world_min_x) Player.x = world_min_x;
        if(Player.x + Player.w > world_max_x) Player.x = world_max_x - Player.w;
        if(Player.y < world_min_y) Player.y = world_min_y;
        if(Player.y + Player.h > world_max_y) Player.y = world_max_y - Player.h;


        for(int i = 0; i < num_Objects; i++){
            if(CheckOverlap(Player, Objects[i]) && Collidable[i]){
                Player.x = old_x;
                Player.y = old_y;
                break;
            }
        }
        cam.x = Player.x + Player.w / 2;
        cam.y = Player.y + Player.h / 2;


        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
        SDL_RenderClear(renderer);

        for(int i = 0; i < num_Objects; i++){
            SDL_Rect r = WorldToScreen(Objects[i], cam);
            SDL_RenderCopy(renderer, textures[i], NULL, &r);
        }

        SDL_Rect SPlayer = WorldToScreen(Player, cam);
        SDL_RenderCopy(renderer, Player_texture, NULL, &SPlayer);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(Player_texture);
    for(int i = 0; i < num_Objects; i++){
        SDL_DestroyTexture(textures[i]);
    }
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

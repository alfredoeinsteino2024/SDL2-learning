#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 700

typedef struct{
    float x, y, w, h;
} WorldRect;

typedef struct{
    float x, y;
} Camera;

bool checkOverlap(WorldRect A, WorldRect B){
    if(A.x + A.w <= B.x) return false;  // A is completely LEFT of B
    if(A.x >= B.x + B.w) return false;  // A is completely RIGHT of B
    // Top not Overlap to check now
    if(A.y + A.h <= B.y) return false;  // A is completely above B
    if(A.y >= B.y + B.h) return false;  // A is completely below B

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

   WorldRect Player = {23, 100, 80, 50};
   WorldRect Objects[4] = { 
   
    {250, 150, 200, 100},
    {100, -200, 350, 150},
    {-80, 500, 250, 150},
    {-400, 200, 150, 200},
    };

    Camera cam = {0, 0};

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL not Initializing: %s\n", SDL_GetError());
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
        printf("PNG Image not Loading: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return 1;
    }

    SDL_Texture *textures[4];
    const char *filenames[4] = {
        "car1.png",    // textures[0] = Car1
        "car.png",     // textures[1] = Car
        "truck.png",   // textures[2] = Truck
        "tree.png"     // textures[3] = Tree
    };
    //PLAYER IMAGE LOADING
    SDL_Texture *Player_Texture = IMG_LoadTexture(renderer, "Player.png");
    if(!Player_Texture){
        printf("Error Loading Player PNG: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    for(int i = 0; i < 4; i++){
       textures[i] = IMG_LoadTexture(renderer, filenames[i]);
       if(!textures[i]){
        printf("Error Loading %s PNG: %s\n", filenames[i], IMG_GetError());
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
    
    bool running = true;
    bool up = false; bool down = false; bool right = false; bool left = false;
    SDL_Event event;

    Uint32 last_time = SDL_GetTicks();

    while(running){
        Uint32 current_time = SDL_GetTicks();
        float delta_time = current_time - last_time;      //      I GUESS I CAN ALSO ADD THE DIVISION HERE ALSO IT SEEMS BOTH WORKED / 1000.0f
        last_time = current_time;
        float move_amount = (delta_time * 200.0f) / 1000.0f; //Can this be other way for the Conversion??

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
             // WHEN NO KEY IS PRESSED
            if(event.type == SDL_KEYUP){
                switch (event.key.keysym.sym) // IDENTIFYING THE KIND OF KEY PRESSED
                {
                case SDLK_UP: up = false;  break;
                case SDLK_DOWN: down = false;  break;
                case SDLK_RIGHT: right = false;  break;
                case SDLK_LEFT: left = false;  break;
                default:
                    break;
                }
            }
            // WHEN A KEY IS PRESSED DOWN
            if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym) // IDENTIFYING THE KIND OF KEY PRESSED
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
        if(right) Player.x += move_amount;
        if(left) Player.x -= move_amount;

        for(int i = 0; i < 4; i ++){
            if(checkOverlap(Player, Objects[i])){
                Player.x = old_x;
                Player.y = old_y;
                break;
            }
        }

        cam.x = Player.x + Player.w / 2;
        cam.y = Player.y + Player.h / 2;

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
        SDL_RenderClear(renderer);

        

        for(int i = 0; i < 4; i++){
            SDL_Rect r = WorldToScreen(Objects[i], cam);
            SDL_RenderCopy(renderer, textures[i], NULL, &r);
        }
        
        SDL_Rect SPlayer = WorldToScreen(Player, cam);
        SDL_RenderCopy(renderer, Player_Texture, NULL, &SPlayer);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyTexture(Player_Texture);
    for(int i = 0; i < 4; i++){
        SDL_DestroyTexture(textures[i]);

    }
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

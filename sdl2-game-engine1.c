#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL_image.h>
#include<math.h>

#define WINDOW_WIDTH 1200
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

    WorldRect carPlayer = {-300, -300, 300, 350};
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
        "Game Engine",
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

    SDL_Renderer *renderer = SDL_CreateRenderer(window,
         -1, 
         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );
        
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

    SDL_Texture* carPlayer_texture = IMG_LoadTexture(renderer, "carPlayer.png");
    if(!carPlayer_texture){
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
            SDL_DestroyTexture(carPlayer_texture);

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
        float move_amount = 500.0f * delta_time; // We are using 200 Frame per Seconds

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
         
        float old_x = carPlayer.x;
        float old_y =carPlayer.y;

        float dx = 0;
        float dy = 0;

        // PART FOR DIAGONAL MOVEMENT
        if(up) dy -=1;
        if(down) dy +=1;
        if(left) dx -=1;
        if(right) dx +=1;

        if(dx !=0 || dy != 0){
            float length = sqrt(dx*dx + dy*dy);
            dy = dy / length;
            dx = dx / length;
        }
        carPlayer.x += dx * move_amount;
        carPlayer.y += dy * move_amount;


         // BOUNDARY CREATION IN PROGRESS
        float world_min_x = -1000;
        float world_max_x = 1500;
        float world_min_y = 0;
        float world_max_y = 2000;
        
        //Player cannot cross this boundary specified
        if(carPlayer.x < world_min_x) carPlayer.x = world_min_x;
        if(carPlayer.x + carPlayer.w > world_max_x) carPlayer.x = world_max_x - carPlayer.w;
        if(carPlayer.y < world_min_y) carPlayer.y = world_min_y;
        if(carPlayer.y + carPlayer.h > world_max_y) carPlayer.y = world_max_y - carPlayer.h;


        for(int i = 0; i < num_Objects; i++){
            if(CheckOverlap(carPlayer, Objects[i]) && Collidable[i]){
                carPlayer.x = old_x;
                carPlayer.y = old_y;
                break;
            }
        }
        cam.x = carPlayer.x + carPlayer.w / 2;
        cam.y = carPlayer.y + carPlayer.h / 2;


        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
        SDL_RenderClear(renderer);

        for(int i = 0; i < num_Objects; i++){
            SDL_Rect r = WorldToScreen(Objects[i], cam);
            SDL_RenderCopy(renderer, textures[i], NULL, &r);
        }

        SDL_Rect ScarPlayer = WorldToScreen(carPlayer, cam);
        SDL_RenderCopy(renderer, carPlayer_texture, NULL, &ScarPlayer);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(carPlayer_texture);
    for(int i = 0; i < num_Objects; i++){
        SDL_DestroyTexture(textures[i]);
    }
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

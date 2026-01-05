#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL_image.h>

#define WINDOW_HEIGHT 650
#define WINDOW_WIDTH 850

typedef struct {
    float x, y, w, h;
} WorldRect;

typedef struct {
    float x, y;
} Camera;
// CHECKING FOR OVERLAP
bool checkOverlap(WorldRect A, WorldRect B){
    if(A.x >= B.x + B.w) return false; // A completely right of B
    if(A.x + A.w <= B.x) return false; // A completely left of B

    if(A.y + A.h <= B.y) return false; // A completely above B
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
    WorldRect Tree = {250, 150, 200, 100};
    WorldRect Car = {100, -200, 350, 150}; // I WILL BE USING A BLUE CAR FOR THIS
    WorldRect Truck = {-80, 500, 250, 150}; // I SHOULD BE USING A BROWN TRUCK FOR THIS
    WorldRect Car1 = {-400, 200, 150, 200};

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

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
        printf("PNG loading not supported: %s\n", SDL_GetError());

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    
    }
    SDL_Texture *Player_texture = IMG_LoadTexture(renderer, "player.png");
    if(!Player_texture){
        printf("Failed to load player.png: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *Car_texture = IMG_LoadTexture(renderer, "car.png");
      if(!Car_texture){
        printf("Failed to load car.png: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *Truck_texture = IMG_LoadTexture(renderer, "truck.png");
      if(!Truck_texture){
        printf("Failed to load truck.png: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_texture);
        SDL_DestroyTexture(Car_texture);

        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *Tree_texture = IMG_LoadTexture(renderer, "tree.png");
      if(!Tree_texture){
        printf("Failed to load Tree.png: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_texture);
        SDL_DestroyTexture(Car_texture);
        SDL_DestroyTexture(Truck_texture);

        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *Car1_Texture = IMG_LoadTexture(renderer, "car1.png");
      if(!Car1_Texture){
        printf("Failed to load car1.png : %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_texture);
        SDL_DestroyTexture(Car_texture);
        SDL_DestroyTexture(Truck_texture);
        SDL_DestroyTexture(Tree_texture);

        IMG_Quit();
        SDL_DestroyRenderer(renderer);
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
        
        float old_x = Player.x;
        float old_y = Player.y;

        if(up) Player.y -=     move_amount;
        if(down) Player.y +=   move_amount;
        if(right) Player.x +=  move_amount;
        if(left) Player.x -=   move_amount;

        if(checkOverlap(Player, Tree) ||checkOverlap(Player, Car) || checkOverlap(Player, Truck) || checkOverlap(Player, Car1)){
            Player.x = old_x;
            Player.y = old_y;
        }
        
        cam.x = Player.x + Player.w / 2;
        cam.y = Player.y + Player.h / 2;

        SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect SPlayer = WorldToScreen(Player, cam);
        SDL_RenderCopy(renderer, Player_texture, NULL, &SPlayer);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0 , 255);
        // SDL_RenderFillRect(renderer, &SPlayer);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        // SDL_RenderDrawRect(renderer, &SPlayer);

        SDL_Rect STree = WorldToScreen(Tree, cam);
        SDL_RenderCopy(renderer, Tree_texture, NULL, &STree);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 255 , 255);
        // SDL_RenderFillRect(renderer, &STree);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // SDL_RenderDrawRect(renderer, &STree);

        SDL_Rect SCar = WorldToScreen(Car, cam);
        SDL_RenderCopy(renderer, Car_texture, NULL, &SCar);
        // SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
        // SDL_RenderFillRect(renderer, &SCar);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // SDL_RenderDrawRect(renderer, &SCar);
        
        SDL_Rect STruck= WorldToScreen(Truck, cam);
        SDL_RenderCopy(renderer, Truck_texture, NULL, &STruck);
        // SDL_SetRenderDrawColor(renderer, 255, 0, 150, 255);
        // SDL_RenderFillRect(renderer, &STruck);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // SDL_RenderDrawRect(renderer, &STruck);

        SDL_Rect SCar1= WorldToScreen(Car1, cam);
        SDL_RenderCopy(renderer, Car1_Texture, NULL, &SCar1);
        // SDL_SetRenderDrawColor(renderer, 100, 0, 150, 255);
        // SDL_RenderFillRect(renderer, &SPig);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // SDL_RenderDrawRect(renderer, &SPig);

        SDL_RenderPresent(renderer);

    }
    SDL_DestroyTexture(Player_texture);
    SDL_DestroyTexture(Car_texture);
    SDL_DestroyTexture(Truck_texture);
    SDL_DestroyTexture(Tree_texture);
    SDL_DestroyTexture(Car1_Texture);
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

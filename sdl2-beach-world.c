#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL_image.h>

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 1400
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
    // OBJECTS IN THE WORLD COORDINATE
    WorldRect Player = {0, 0, 100, 150};
    WorldRect Car1 = {-500, 700, 300, 200};
    WorldRect Car = {400, 700, 300, 200};
    WorldRect Truck = {100, 400, 300, 200};
    WorldRect Hotel = {150, 80, 500, 500};
    WorldRect Beach = {-1000, 100, 15000, 6000};
    WorldRect Rock = {-1800, -600, 1000, 500}; 
    WorldRect Road = {0,-6000, 1000, 100000};     // CONTINUE TEXTURE FROM HERE
    WorldRect Tree1 = {1000, 3100, 10, 200};
    WorldRect Tree = {500, 50, 300, 700};

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
    SDL_Texture *Car1_Texture = IMG_LoadTexture(renderer, "Car1.png");
    if(!Car1_Texture){
        printf("Error Loading Car1 PNG: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_Texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture *Car_Texture = IMG_LoadTexture(renderer, "Car.png");
    if(!Car_Texture){
        printf("Error Loading Car PNG: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_Texture);
        SDL_DestroyTexture(Car1_Texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture *Truck_Texture = IMG_LoadTexture(renderer, "Truck.png");
    if(!Truck_Texture){
        printf("Error Loading Truck PNG: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_Texture);
        SDL_DestroyTexture(Car1_Texture);
        SDL_DestroyTexture(Car_Texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture *Hotel_Texture = IMG_LoadTexture(renderer, "Hotel.png");
    if(!Hotel_Texture){
        printf("Error Loading Hotel PNG: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_Texture);
        SDL_DestroyTexture(Car1_Texture);
        SDL_DestroyTexture(Car_Texture);
        SDL_DestroyTexture(Truck_Texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture *Beach_Texture = IMG_LoadTexture(renderer, "Beach.png");
    if(!Beach_Texture){
        printf("Error Loading Beach PNG: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_Texture);
        SDL_DestroyTexture(Car1_Texture);
        SDL_DestroyTexture(Car_Texture);
        SDL_DestroyTexture(Truck_Texture);
        SDL_DestroyTexture(Hotel_Texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture *Rock_Texture = IMG_LoadTexture(renderer, "Rock.png");
    if(!Rock_Texture){
        printf("Error Loading Rock PNG: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_Texture);
        SDL_DestroyTexture(Car1_Texture);
        SDL_DestroyTexture(Car_Texture);
        SDL_DestroyTexture(Truck_Texture);
        SDL_DestroyTexture(Beach_Texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture *Road_Texture = IMG_LoadTexture(renderer, "Road.png");
    if(!Road_Texture){
        printf("Error Loading Road PNG: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_Texture);
        SDL_DestroyTexture(Car1_Texture);
        SDL_DestroyTexture(Car_Texture);
        SDL_DestroyTexture(Truck_Texture);
        SDL_DestroyTexture(Hotel_Texture);
        SDL_DestroyTexture(Beach_Texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // Texture for Tree1 and Tree
    SDL_Texture *Tree_Texture = IMG_LoadTexture(renderer, "Tree.png");
    if(!Tree_Texture){
        printf("Tree PNG not Loading!!: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_Texture);
        SDL_DestroyTexture(Car1_Texture);
        SDL_DestroyTexture(Car_Texture);
        SDL_DestroyTexture(Truck_Texture);
        SDL_DestroyTexture(Hotel_Texture);
        SDL_DestroyTexture(Beach_Texture);
        SDL_DestroyTexture(Road_Texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *Tree1_Texture = IMG_LoadTexture(renderer, "Tree1.png");
    if(!Tree1_Texture){
        printf("Tree1 PNG not Loading!!: %s\n", IMG_GetError());
        SDL_DestroyTexture(Player_Texture);
        SDL_DestroyTexture(Car1_Texture);
        SDL_DestroyTexture(Car_Texture);
        SDL_DestroyTexture(Truck_Texture);
        SDL_DestroyTexture(Hotel_Texture);
        SDL_DestroyTexture(Beach_Texture);
        SDL_DestroyTexture(Road_Texture);
        SDL_DestroyTexture(Tree1_Texture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
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

        if(checkOverlap(Player, Car1) || checkOverlap(Player, Car)|| checkOverlap(Player, Truck)|| checkOverlap(Player, Hotel)|| checkOverlap(Player, Rock)){
             Player.x = old_x ;
             Player.y = old_y;
        }

        cam.x = Player.x + Player.w / 2;
        cam.y = Player.y + Player.h / 2;

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 150);
        SDL_RenderClear(renderer);

        

        SDL_Rect SCar1 = WorldToScreen(Car1, cam);
        SDL_RenderCopy(renderer, Car1_Texture, NULL, &SCar1);

        SDL_Rect SCar = WorldToScreen(Car, cam);
        SDL_RenderCopy(renderer, Car_Texture, NULL, &SCar);

        SDL_Rect STruck = WorldToScreen(Truck, cam);
        SDL_RenderCopy(renderer, Truck_Texture, NULL, &STruck);

        SDL_Rect SHotel = WorldToScreen(Hotel, cam);
        SDL_RenderCopy(renderer, Hotel_Texture, NULL, &SHotel);

        

        SDL_Rect SRock = WorldToScreen(Rock, cam);
        SDL_RenderCopy(renderer, Rock_Texture, NULL, &SRock);

        

        // Tree and Tree1 to copy

        SDL_Rect STree = WorldToScreen(Tree, cam);
        SDL_RenderCopy(renderer, Tree_Texture, NULL, &STree);

        SDL_Rect STree1 = WorldToScreen(Tree1, cam);
        SDL_RenderCopy(renderer, Tree1_Texture, NULL, &STree1);

        

        SDL_Rect SBeach = WorldToScreen(Beach, cam);
        SDL_RenderCopy(renderer, Beach_Texture, NULL, &SBeach);

        SDL_Rect SRoad = WorldToScreen(Road, cam);
        SDL_RenderCopy(renderer, Road_Texture, NULL, &SRoad);

        SDL_Rect SPlayer = WorldToScreen(Player, cam);
        SDL_RenderCopy(renderer, Player_Texture, NULL, &SPlayer);

        SDL_RenderPresent(renderer); // Make all the renderer visible to the window by drawing


    }
    SDL_DestroyTexture(Player_Texture);
    SDL_DestroyTexture(Car1_Texture);
    SDL_DestroyTexture(Car_Texture);
    SDL_DestroyTexture(Truck_Texture);
    SDL_DestroyTexture(Hotel_Texture);
    SDL_DestroyTexture(Beach_Texture);
    SDL_DestroyTexture(Road_Texture);
    SDL_DestroyTexture(Tree_Texture);
    SDL_DestroyTexture(Tree1_Texture);
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

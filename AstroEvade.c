#include<stdio.h>
#include<SDL2/SDL.h>
#include<stdbool.h>
#include<SDL2/SDL_image.h>
#include<math.h>

#define WINDOW_WIDTH 750
#define WINDOW_HEIGHT 700

#define num_objects 20

typedef struct {
    float x, y, w, h;
} WorldSystem;

typedef struct {
    float x, y;
} Camera;

SDL_Rect WorldToscreen(WorldSystem w, Camera cam){
    SDL_Rect r;
    r.h = w.h;
    r.w = w.w;
    r.x = w.x - cam.x + WINDOW_WIDTH / 2;
    r.y = w.y - cam.y + WINDOW_HEIGHT / 2;
    return r;
}

bool CheckOverlap(WorldSystem A, WorldSystem B){
    if(A.x + A.w <= B.x) return false; // A is to the left of B
    if(A.x >= B.x + B.w) return false; // A is completely right of B

    if(A.y + A.h <= B.y) return false; // A is completely Above B
    if(A.y >= B.y + B.h) return false; // A is completely below B

    return true;
}



int main(int argc, char *argv[]){
    // WHAT ARE THOSE THING THAT WILL BE NEEDED FOR ME IN THE WORLD SYSTEMS?
    // I AM THINKING OF MAKING A JET/PLAYER TO BE MOVING MAINLY +X AXIS AND -X AXIS BUT THERE WILL BE VELOCITY OF FOREIGN OBJECT TRYING TO COLLIDE WITH MY PLAYER, BUT MY PLAYER WITH THE HELP OF THE SDL_K ARROWS WILL BE ABLE TO MANUEVER IT'S WAY BEFORE BEING IT BY THE FOREIGN OBJECT.
    // IF THERE IS A COLLISION BETWEEN THE FOREIGN OBJECT AND THE PLAYER, AUTOMATICALLY THE PLAYER DISAPPEARS AND THEN THE WINDOW EXIST IN 10 SECONDS

    WorldSystem Player = {300, 950, 50, 80};      // HOW DO INAMKE THE MOVEMENT OF THE PLAYER MOVING VERTICALLY UPWARD TO INFINITY *TAKE NOT THERE IS BOUNDARY, IS IT THAT AFTER IT REACHED THE MAX VERTICAL HEIGHT, IT WILL AUTOMATICALLY START AGIN FROM THE INITIAL MINIMUM VALUE, THEN IT WILL LOOK AS IF THE GAME IS NOT ENDING AND IT WILL COUNTINUE TO INFINITY WHICH IS ACTUALLY AN ILLUSION OF THE GAME.

        Camera cam = {850, 450}; // WHAT IF I DON'T WANT MY CAMERA COORDINATE TO BE {0, 0} I CAN ALSO CHANGE. WHAT EXAMPLES DOW WE CHANGE COORDNATE OF THE CAMERA???
       // I USE {850, 450} COS THE PLAYER WILL BE AT ALMOST CENTER OF THE SCREEN TOWARDS THE BOTTOM OF THE VERTICAL LINE. THAT MEANS WHEN CREATING THE MAXIMUM VALUE OF THE Y AXIS, IT WILL BE 850 SINCE 850 SPANS DOWNWARD POSITIVELY

       WorldSystem Foreign_Objects[num_objects] = {
        {551, -600, 80, 100},  // STONE1
        {150, 700, 90, 130},  // STONE2
        {10, -500, 80, 95},  // STONE3
        {0, 300, 60, 90},  // STONE4
        {-50, -100, 80, 100},  // STONE5
        {125, 175, 90, 130},  // STONE6
        {-95, 450, 80, 95},  // STONE7
        {700, 250, 30, 60},  // STONE8
        {340, -10, 80, 100},  // STONE9
        {150, -50, 30, 60},  // STONE10

        //FOR A NEW AND SAMLLER SPARTIAL DIMENSION

        {1000, 600, 80, 80},  // STONE11
        {1500, 20, 90, 90},  // STONE12
        {10, -500, 30, 20},  // STONE13
        {0, 300, 10, 10},  // STONE14
        {50, 100, 35, 10},  // STONE15
        {10, 200, 20, 15},  // STONE16
        {-150, 600, 50, 35},  // STONE17
        {550, 220, 5, 5},  // STONE18
        {390, -50, 20, 30},  // STONE19
        {280, -50, 30, 60},  // STONE20
       };

       const char *filenames[num_objects] = {
        "Stone1.png","Stone2.png","Stone3.png","Stone4.png","Stone5.png",
        "Stone6.png","Stone7.png","Stone8.png","Stone9.png","Stone10.png",
        "Stone11.png","Stone12.png","Stone13.png","Stone14.png","Stone15.png",
        "Stone16.png","Stone17.png","Stone18.png","Stone19.png","Stone20.png"
       };


    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL not initializing: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Engine_Architecture",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if(!window){
        printf("SDL_Window not initializing: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer){
        printf("Renderer not initializing: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    bool up = false; bool down = false; bool right = 0; bool left = 0;
    SDL_Event event;
    Uint32 last_time = SDL_GetTicks();

    while(running){
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;
        
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }

            if(event.type == SDL_KEYUP){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: up = false;   break;
                case SDLK_DOWN: down = false;   break;
                case SDLK_RIGHT: right = false;   break;
                case SDLK_LEFT: left = false;   break;

                default:
                break;
                }
            }
            if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: up = true;   break;
                case SDLK_DOWN: down = true;   break;
                case SDLK_RIGHT: right = true;   break;
                case SDLK_LEFT: left = true;   break;

                default:
                break;
                }
            }
        }

        float old_x = Foreign_Objects[num_objects].x;
        float old_y = Foreign_Objects[num_objects].y;

        float dy = 0; 
        float dx = 0;


        if(dy != 0 || dx != 0){
            float length = sqrt(dx*dx + dy*dy);
            dx = dx / length;
            dy = dy / length;
        }

        // THIS IS JUST FOR CONSTANT VELOCITY
        for(int i = 0; i < num_objects; i++){
            Foreign_Objects[i].y += 200 * delta_time;

            if(right) Foreign_Objects[i].x -= 200 * delta_time;
            if(left) Foreign_Objects[i].x += 200 * delta_time;
        }

        

        // BOUNDARY CREATION 
        float World_Min_x = -100.0f;
        float World_Max_x = 950.0f;
       
        // CONDITION TO AVOID OUT BOUNDARY
        if(Player.x < World_Min_x) Player.x = World_Min_x;
        if(Player.x + Player.w > World_Max_x) Player.x = World_Max_x - Player.w;

        
        // I NEED TO AVOID COLLISION
        for(int i = 0; i <num_objects; i++){
            if(CheckOverlap(Player, Foreign_Objects[i])){
                Foreign_Objects[i].x = old_x; //Player.x - Player.w;
                Foreign_Objects[i].y =  old_y; //Player.y - Player.h;
                break;
            }
        }

        // CAMERA IMPLEMENTATION
        cam.x = Player.x + Player.w / 2;
        cam.y = Player.y + Player.h / 2;

        SDL_SetRenderDrawColor(renderer, 0, 0, 80, 150);
        SDL_RenderClear(renderer);


        for(int i = 0; i < num_objects; i++){
            SDL_Rect r = WorldToscreen(Foreign_Objects[i], cam); 
            SDL_SetRenderDrawColor(renderer, 255, 0, 150, 100);
            SDL_RenderFillRect(renderer, &r);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &r);
        }

        SDL_Rect SPlayer = WorldToscreen(Player, cam);
        SDL_SetRenderDrawColor(renderer, 230, 0, 0, 230);
        SDL_RenderFillRect(renderer, &SPlayer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderDrawRect(renderer, &SPlayer);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}



// I NEED TO WORK WITH SEED.RANDOM NUMBERS FOR THE SHAPES
// IF THE PLAYER CAN MAKE THE OTHER RECT TO DISAPPEARS, THE SIZE THEN NEED TO INCREASE AS WELL AS THE SPEED
// HOW DO I MAKE A ROAD LOOK INFINITE??
// HOW DO I MAKE THE WHOLE SCREEN A PNG TESXTURE?  WHAT ARE THE CRITERIA IN BOTHE SIZE AND QUALITY BEFORE I COULD USE A PNG TO RENDER THE SCREEN OF THE WINDOW I CREATED

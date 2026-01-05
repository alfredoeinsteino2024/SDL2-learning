# SDL2 Learning Projects
This branch contains my SDL2 learning journey with various projects and exercises.

## Projects

### Latest: SDL2 Beach World - Refactored Version (`sdl2-beach-world-with-loops.c`)
✨ **NEW: Improved with for loops and selective collision!**

A complete 2D beach world game featuring:
- PNG sprite rendering (Player, Cars, Truck, Tree, Hotel, Beach, Road, Rock)
- **Selective collision detection** - some objects block, others don't
- Camera system following the player
- Smooth movement with delta time
- Player can walk on Beach and Road, blocked by Cars, Trucks, Trees, and Rocks

**Key Improvements over original:**
- Eliminated repetitive code using arrays and for loops
- Added `collidable` array for selective collision
- Cleaner texture loading and management
- Simplified rendering and cleanup
- Easier to add new game objects
- More maintainable code structure

### Previous Version: SDL2 Beach World (`sdl2-beach-world.c`)
Original version with repetitive code - kept for comparison to show learning progress.

### Earlier: SDL2 Sprite Game (`sdl2-sprite-game.c` and `sdl2-sprite-game-with-loops.c`)
Sprite-based game with collision detection and camera system.

### Learning Progression:
1. `01_Open_Window.c` - Basic SDL2 window
2. `SDL2_Renderer_Event.c` - Event handling
3. `Rectangle_Key_Control.c` - Keyboard input
4. `Collision_Detection.c` - Collision system
5. `StepRect.c` - Movement
6. `cameraOnPlayer_Frame_Per_Seconds.c` - Camera and timing
7. `sdl2-sprite-game.c` - Complete game with textures
8. `sdl2-sprite-game-with-loops.c` - Refactored with for loops
9. `sdl2-beach-world.c` - Beach world game
10. `sdl2-beach-world-with-loops.c` - **Beach world with for loops and selective collision** ⭐

## Key Learning: Code Refactoring & Game Logic
- How arrays eliminate variable repetition
- How for loops reduce code duplication
- Implementing selective collision detection
- Better code maintainability and scalability

## Tech Stack
- C Programming
- SDL2
- SDL2_image

## Compilation
```bash
# Compile the latest refactored version
gcc sdl2-beach-world-with-loops.c -lSDL2 -lSDL2_image -o game

# Or compile any other version
gcc sdl2-sprite-game-with-loops.c -lSDL2 -lSDL2_image -o game
```

# SDL2 Learning Projects
This branch contains my SDL2 learning journey with various projects and exercises.

## Projects

### Latest: SDL2 Learning Project (`sdl2-game-engine.c`)
✨ **NEW: Practicing diagonal movement with vector normalization**

A learning project where I'm practicing:
- Normalized diagonal movement using vector math
- Hardware-accelerated rendering
- Selective collision detection
- World boundaries
- Camera following player

**What I implemented:**
- Vector normalization using `sqrt()` from math.h
- SDL_RENDERER_ACCELERATED for better performance
- Array-based object management with 7 objects
- Boolean flags for collision detection

Still learning and improving - not a complete game, but solid practice!

### Previous: SDL2 Beach World - Refactored Version (`sdl2-beach-world-with-loops.c`)
Practice project with for loops and selective collision:
- Arrays and for loops instead of repetition
- Selective collision system
- World boundaries

### Earlier Projects:
- `sdl2-beach-world.c` - Original version (repetitive code)
- `sdl2-sprite-game.c` and `sdl2-sprite-game-with-loops.c` - Sprite practice

## Learning Progression:
1. `01_Open_Window.c` - Basic SDL2 window
2. `SDL2_Renderer_Event.c` - Event handling
3. `Rectangle_Key_Control.c` - Keyboard input
4. `Collision_Detection.c` - Collision system
5. `StepRect.c` - Movement
6. `cameraOnPlayer_Frame_Per_Seconds.c` - Camera and timing
7. `sdl2-sprite-game.c` - Complete game with textures
8. `sdl2-sprite-game-with-loops.c` - Refactored with for loops
9. `sdl2-beach-world.c` - Beach world game
10. `sdl2-beach-world-with-loops.c` - Beach world with for loops
11. `sdl2-game-engine.c` - **Practicing vector normalization** ⭐

## What I'm Learning

### Code Organization
- Arrays instead of repetitive variables
- For loops for cleaner code
- Macros for easy configuration

### Game Development Concepts
- Collision detection
- Camera systems
- Delta time for smooth movement
- Vector normalization (why diagonal movement needs adjustment)

### Performance
- Hardware acceleration
- VSync for smoother visuals

## Tech Stack
- C Programming
- SDL2
- SDL2_image
- math.h

## Compilation
```bash
# Compile latest version
gcc sdl2-game-engine.c -lSDL2 -lSDL2_image -lm -o game

# Note: -lm flag needed for math.h
```

## Current Focus
Learning vector mathematics and how it applies to game development. Understanding the theory, then implementing it in code.

These are learning exercises, not polished projects - but that's the point! 🚀

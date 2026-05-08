# SDL2 Learning Projects
This branch contains my SDL2 learning journey with 
various projects and exercises.
## Projects
### Latest: SDL2 TTF Text Rendering (`sdl_ttf_text_rendering.c`)
✨ **NEW: Rendering text to an SDL2 window using SDL2_ttf**

A project focused on integrating TrueType font rendering
into an SDL2 application using the SDL2_ttf library.

**What I implemented:**
- TTF initialization and error handling
- Loading a TrueType font (Roboto Condensed) at runtime
- Rendering text to a surface with `TTF_RenderText_Solid()`
- Converting surface to GPU texture for rendering
- Correct resource cleanup order

**Window & Text Config:**
- Window: `400 x 600`, teal background `(0, 150, 150)`
- Text: `"Hello ALFRED"`, white, font size `24`
- Renderer: `SDL_RENDERER_SOFTWARE`

---

### Previous: PulseGuard Monitor (`heartrate.c`)
✨ **Real-time ECG-style heartbeat waveform visualizer**
A project born from a real health monitoring system 
I was building with my team. I explored how low-level 
C programming could be integrated into medical 
visualizations.

**What I implemented:**
- Real-time scrolling waveform using array shifting
- Fourier-inspired sine wave formula for pulse generation
- SDL2 hardware-accelerated rendering
- Coordinate system conversion for correct wave display

**The Math Behind It:**
f(t) = sin(t) + 1/2*sin(2t) + 1/3*sin(3t) + 1/4*sin(4t)

---

### Earlier: SDL2 Game Engine (`sdl2-game-engine.c`)
✨ **Practicing diagonal movement with vector normalization**
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

Still learning and improving - not a complete game, 
but solid practice!

---

### Earlier: Gravity Simulation (`gravity_learn.c`)
Practice project for frame-rate independent physics:
- Delta time for smooth, frame-rate independent movement
- Gravity and velocity accumulation
- Ground collision detection
- Basic SDL2 game loop structure

> Note: the player and ground are rendered the same color —
> a small bug I noticed after the fact. Left as-is since
> this is a learning snapshot, not a polished project.

---

### Earlier: SDL2 Beach World (`sdl2-beach-world-with-loops.c`)
Practice project with for loops and selective collision:
- Arrays and for loops instead of repetition
- Selective collision system
- World boundaries

---

### Earlier Projects:
- `sdl2-beach-world.c` - Original version (repetitive code)
- `sdl2-sprite-game.c` and `sdl2-sprite-game-with-loops.c` 
  - Sprite practice

---

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
10. `sdl2-beach-world-with-loops.c` - Beach world with loops
11. `gravity.c` - Frame-rate independent gravity simulation
12. `sdl2-game-engine.c` - Practicing vector normalization ⭐
13. `heartrate.c` - Real-time pulse waveform monitor 🫀
14. `sdl_ttf_text_rendering.c` - SDL2_ttf text rendering 🔤

---

## What I'm Learning

### Code Organization
- Arrays instead of repetitive variables
- For loops for cleaner code
- Macros for easy configuration

### Game Development Concepts
- Collision detection
- Camera systems
- Delta time for smooth movement
- Vector normalization

### Physics Simulation
- Frame-rate independent movement with delta time
- Velocity and gravity accumulation
- Ground collision response

### Mathematics in Programming
- Fourier sine wave synthesis
- Coordinate system conversion
- Harmonic frequency and amplitude

### Text & UI Rendering
- TrueType font loading with SDL2_ttf
- Surface-to-texture pipeline for text
- Positioning and sizing text with `SDL_Rect`
- Correct TTF initialization and cleanup

### Performance
- Hardware acceleration
- VSync for smoother visuals

---

## Tech Stack
- C Programming
- SDL2
- SDL2_image
- SDL2_ttf
- math.h

---

## Compilation
```bash
# Compile TTF text rendering
gcc sdl_ttf_text_rendering.c -lSDL2 -lSDL2_ttf -o sdl_ttf_text_rendering

# Compile PulseGuard Monitor
gcc heartrate.c -lSDL2 -lm -o heartrate

# Compile latest game engine
gcc sdl2-game-engine.c -lSDL2 -lSDL2_image -lm -o game

# Compile gravity simulation
gcc gravity.c -lSDL2 -o gravity
```

---

## Current Focus
Exploring how C programming and SDL2 can be applied 
to real world problems like health monitoring systems. 
Understanding mathematics and how it applies to 
programming. Now branching into UI and text rendering
with SDL2_ttf for richer visual output.

These are learning exercises, not polished projects 
- but that's the point! 🚀

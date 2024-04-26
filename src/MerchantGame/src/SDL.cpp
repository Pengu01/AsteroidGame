#include "SDL.h"
#include "systems.cpp"
#include <iostream>

// Function to start the SDL system
bool SDL::Start()
{
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // Print error message if initialization fails
        printf(SDL_GetError());
        return false;
    }
    
    // Create a window with the specified title and dimensions
    gWindow = SDL_CreateWindow("AsteroidGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    // Check if window creation fails
    if (gWindow == NULL)
    {
        // Print error message if window creation fails
        printf(SDL_GetError());
        return false;
    }
    
    // Create a renderer for the window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    
    // Check if renderer creation fails
    if (gRenderer == NULL)
    {
        // Print error message if renderer creation fails
        printf(SDL_GetError());
        return false;
    }
    
    // Get the surface of the window
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    
    // Return true if SDL initialization is successful
    return true;
}

// Function to run the game loop
void SDL::GameLoop()
{
    // Set the background color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    // Load textures for player, bullet, and asteroid
    textures.push_back(LoadTexture("../../assets/player.png"));
    textures.push_back(LoadTexture("../../assets/bullet.png"));
    textures.push_back(LoadTexture("../../assets/asteroid.png"));
    
    // Initialize the registry
    registry reg;
    
    // Initialize all systems
    mobility_system mobility_sys;
    sprite_system sprite_sys;
    controller_system controller_sys;
    velocity_system velocity_sys;
    rotation_system rotation_sys;
    tracking_system tracking_sys;
    lifespan_system lifespan_sys;
    collision_system collision_sys;
    asteroid_system asteroid_sys;
    input_system input_sys;
    
    // Create the player entity
    reg.sprites[player] = { {0, 0, 52, 30}, textures[0], 200 };
    reg.velocities[player] = { 0, 0, 0.5f, 600 };
    reg.controllers[player] = { 0, 0 };
    reg.trackers[player] = { NULL, true };
    reg.collisions[player] = { 'p' };
    
    // Create asteroid entities
    reg.asteroids[create_entity()] = { 2.0,2.0,1,0,40,40 };
    reg.asteroids[create_entity()] = { 5.0,1.5,-1,0,40,40 };
    reg.asteroids[create_entity()] = { 7.0,2.0,0,-1,40,40 };
    reg.asteroids[create_entity()] = { 10.0,1.5,0,1,40,40 };
    
    // Game loop
    while (!quit)
    {
        // Handle events
        while (SDL_PollEvent(&e)!= 0)
        {
            // Check for quit event
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            
            // Update controller system
            controller_sys.update(reg, e);
            
            // Update input system
            input_sys.update(reg, player, e, *this);
        }
        
        // Calculate delta time
        LAST = NOW;
        NOW = SDL_GetTicks64();
        deltaTime = (NOW - LAST) / 1000.0;
        
        // Clear the screen
        SDL_RenderClear(gRenderer);
        
        // Update all systems
        asteroid_sys.update(reg, deltaTime, *this);
        velocity_sys.update(reg, deltaTime);
        mobility_sys.update(reg, deltaTime);
        collision_sys.update(reg);
        lifespan_sys.update(reg, deltaTime);
        tracking_sys.update(reg);
        rotation_sys.update(reg, deltaTime);
        sprite_sys.update(reg, gRenderer);
        
        // Update the screen
        SDL_RenderPresent(gRenderer);
    }
    
    // Close the game
    Close();
}

// Function to close the game
void SDL::Close()
{
    // Destroy the renderer
    SDL_DestroyRenderer(gRenderer);
    
    // Destroy the window
    SDL_DestroyWindow(gWindow);
    
    // Set the window to null
    gWindow = NULL;
    
    // Quit SDL
    SDL_Quit();
}

// Function to load a texture from a file
SDL_Texture* SDL::LoadTexture(std::string path)
{
    // Texture to return
    SDL_Texture* newTexture = NULL;
    
    // Load image to surface
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    
    // Check if image was loaded successfully
    if (loadedSurface == NULL)
    {
        // Print error message if image was not loaded
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Create texture from surface
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        
        // Check if texture was created successfully
        if (newTexture == NULL)
        {
            // Print error message if texture was not created
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        
        // Free the surface
        SDL_FreeSurface(loadedSurface);
    }
    
    // Return the texture
    return newTexture;
}

entity SDL::create_entity()
{
	// Initializes entity count
	static entity entities = 0;
	// Increments entity count
	++entities;
	// Returns entity count
	return entities;
}
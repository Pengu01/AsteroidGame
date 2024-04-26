#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "components.cpp"

// Define an entity as a size_t type
using entity = std::size_t;

// registry struct holds all the component data for entities
struct registry
{
    // Map entity to sprite_component
    std::unordered_map<entity, sprite_component> sprites;

    // Map entity to movement_component
    std::unordered_map<entity, movement_component> movements;

    // Map entity to controller_component
    std::unordered_map<entity, controller_component> controllers;

    // Map entity to velocity_component
    std::unordered_map<entity, velocity_component> velocities;

    // Map entity to rotation_component
    std::unordered_map<entity, rotation_component> rotations;

    // Map entity to tracking_component
    std::unordered_map<entity, tracking_component> trackers;

    // Map entity to lifespan_component
    std::unordered_map<entity, lifespan_component> lifespans;

    // Map entity to collision_component
    std::unordered_map<entity, collision_component> collisions;

    // Map entity to asteroid_component
    std::unordered_map<entity, asteroid_component> asteroids;
};

// SDL class represents the game window and handles the game loop
class SDL
{
public:
    // Event structure to store SDL events
    SDL_Event e;

    // Boolean flag to indicate if the game should quit
    bool quit = false;

    // Current time in milliseconds
    Uint64 NOW = SDL_GetTicks64();

    // Previous time in milliseconds
    Uint64 LAST = 0;

    // Time difference between frames
    double deltaTime = 0;

    // Game window size
    static const int SCREEN_WIDTH = 720;
    static const int SCREEN_HEIGHT = 480;

    // Create a new entity and return its unique identifier
    entity create_entity();

    // Initialize SDL and create the game window
    bool Start();

    // Main game loop that updates and renders the game
    void GameLoop();

    // Close the game window and clean up resources
    void Close();

    // Load a texture from the specified path
    SDL_Texture* LoadTexture(std::string path);

    // Game window
    SDL_Window* gWindow = NULL;

    // Surface of game window
    SDL_Surface* gScreenSurface = NULL;

    // Displayed game window surface
    SDL_Surface* gCurrentSurface = NULL;

    // Renderer
    SDL_Renderer* gRenderer = NULL;

    // Vector containing the textures
    std::vector<SDL_Texture*> textures;

    // Creates a new entity and returns its unique identifier
    entity player = create_entity();
};
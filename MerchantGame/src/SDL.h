#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "components.cpp"

using entity = std::size_t;

struct registry
{
	std::unordered_map<entity, sprite_component> sprites;
	std::unordered_map<entity, movement_component> movements;
	std::unordered_map<entity, controller_component> controllers;
	std::unordered_map<entity, velocity_component> velocities;
	std::unordered_map<entity, rotation_component> rotations;
	std::unordered_map<entity, tracking_component> trackers;
	std::unordered_map<entity, lifespan_component> lifespans;
	std::unordered_map<entity, collision_component> collisions;
	std::unordered_map<entity, asteroid_component> asteroids;
};

class SDL
{
public:
	SDL_Event e;
	bool quit = false;
	Uint64 NOW = SDL_GetTicks64();
	Uint64 LAST = 0;
	double deltaTime = 0;
	//Game window size
	static const int SCREEN_WIDTH = 720;
	static const int SCREEN_HEIGHT = 480;
	entity create_entity();
	//Start the window and game
	bool Start();
	//gameloop
	void GameLoop();
	//close and free
	void Close();
	//load a texture
	SDL_Texture* LoadTexture(std::string path);
	//Game window
	SDL_Window* gWindow = NULL;
	//Surface of game window
	SDL_Surface* gScreenSurface = NULL;
	//Displayed game window surface
	SDL_Surface* gCurrentSurface = NULL;
	//Renderer
	SDL_Renderer* gRenderer = NULL;
	//so that i can reuse textures
	std::vector<SDL_Texture*> textures;

	entity player = create_entity();
private:
};

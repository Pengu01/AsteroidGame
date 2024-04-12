#include "SDL.h"
#include "systems.cpp"
#include <iostream>

bool SDL::Start()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf(SDL_GetError());
		return false;
	}
	gWindow = SDL_CreateWindow("AsteroidGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf(SDL_GetError());
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		printf(SDL_GetError());
		return false;
	}
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	return true;
}

void SDL::GameLoop()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	textures.push_back(LoadTexture("../../assets/player.png"));
	textures.push_back(LoadTexture("../../assets/bullet.png"));
	textures.push_back(LoadTexture("../../assets/asteroid.png"));

	registry reg;

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

	reg.sprites[player] = { {0, 0, 52, 30}, textures[0], 200 };
	reg.velocities[player] = { 0, 0, 0.5f, 600 };
	reg.controllers[player] = { 0, 0 };
	reg.trackers[player] = { NULL, true };
	reg.collisions[player] = { 'p' };
	reg.asteroids[create_entity()] = { 2.0,2.0,1,0,40,40 };
	reg.asteroids[create_entity()] = { 5.0,1.5,-1,0,40,40 };
	reg.asteroids[create_entity()] = { 7.0,2.0,0,-1,40,40 };
	reg.asteroids[create_entity()] = { 10.0,1.5,0,1,40,40 };

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			controller_sys.update(reg, e);
			input_sys.update(reg, player, e, *this);
		}
		LAST = NOW;
		NOW = SDL_GetTicks64();
		deltaTime = (NOW - LAST) / 1000.0;

		SDL_RenderClear(gRenderer);
		asteroid_sys.update(reg, deltaTime, *this);
		velocity_sys.update(reg, deltaTime);
		mobility_sys.update(reg, deltaTime);
		collision_sys.update(reg);
		lifespan_sys.update(reg, deltaTime);
		tracking_sys.update(reg);
		rotation_sys.update(reg, deltaTime);
		sprite_sys.update(reg, gRenderer);

		SDL_RenderPresent(gRenderer);
	}
	Close();
}

void SDL::Close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

SDL_Texture* SDL::LoadTexture(std::string path)
{
	//texture to return
	SDL_Texture* newTexture = NULL;
	//Load image to texture
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << IMG_GetError();
		return newTexture;
	}
	//Create texture from loaded surface
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf(SDL_GetError());
		return newTexture;
	}
	//free the old surface
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

entity SDL::create_entity()
{
	static entity entities = 0;
	++entities;
	return entities;
}
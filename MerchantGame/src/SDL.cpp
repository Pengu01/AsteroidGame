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
	gWindow = SDL_CreateWindow("BulletGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	registry reg;

	mobility_system mob_sys;
	sprite_system sprite_sys;
	input_system input_sys;
	velocity_system vel_sys;
	rotation_system rot_sys;
	tracking_system trk_sys;

	reg.sprites[player] = { {0, 0, 32, 32}, LoadTexture("src/player.png"), 200 };
	reg.velocities[player] = { 0, 0, 0.5f, 500 };
	reg.inputs[player] = { 0, 0 };
	reg.trackers[player] = { NULL, true };

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			input_sys.update(reg, e);
		}
		LAST = NOW;
		NOW = SDL_GetTicks64();
		deltaTime = (NOW - LAST) / 1000.0f;

		SDL_RenderClear(gRenderer);

		vel_sys.update(reg, deltaTime);
		mob_sys.update(reg, deltaTime);
		trk_sys.update(reg, deltaTime);
		rot_sys.update(reg, deltaTime);
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
	static std::size_t entities = 0;
	++entities;
	max_entity = entities;
	return entities;
}
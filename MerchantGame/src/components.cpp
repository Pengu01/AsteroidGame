#pragma once
#include <vector>
#include <SDL.h>
#include <string>

struct sprite_component
{
	SDL_FRect src;
	SDL_Texture* texture;
};

struct movement_component
{
	float vel_x;
	float vel_y;
	float speed;
};

struct input_component
{
	float input_x;
	float input_y;
};
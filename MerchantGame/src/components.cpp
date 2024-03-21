#pragma once
#include <vector>
#include <SDL.h>
#include <string>

using entity = std::size_t;

struct sprite_component
{
	SDL_FRect src;
	SDL_Texture* texture;
	float angle;
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

struct velocity_component
{
	float vel_x;
	float vel_y;
	float drag;
	float speed;
};

struct rotation_component
{
	float deviation;
};

struct tracking_component
{
	entity target;
	bool follow_mouse;
};
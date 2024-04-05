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

struct controller_component
{
	float controller_x;
	float controller_y;
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

struct lifespan_component
{
	double lifespan;
};

struct collision_component
{
	char tag;
};

struct asteroid_component
{
	double spawn_timer;
	double spawn_delay;
	float vel_x, vel_y;
	float width, height;
};
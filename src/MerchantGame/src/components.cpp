#pragma once
#include <vector>
#include <SDL.h>
#include <string>

using entity = std::size_t;

// sprite_component represents the visual aspect of an entity
struct sprite_component
{
	SDL_FRect src;
	SDL_Texture* texture;
	float angle;
};

// movement_component represents the movement properties of an entity
struct movement_component
{
	float vel_x;
	float vel_y;
	float speed;
};

// controller_component represents the user input for controlling an entity
struct controller_component
{
	float controller_x;
	float controller_y;
};

// velocity_component represents the velocity and drag of an entity
struct velocity_component
{
	float vel_x;
	float vel_y;
	float drag;
	float speed;
};

// rotation_component represents the rotational deviation of an entity
struct rotation_component
{
	float deviation;
};

// tracking_component represents the target or mouse tracking behavior of an entity
struct tracking_component
{
	entity target;
	bool follow_mouse;
};

// lifespan_component represents the remaining lifespan of an entity
struct lifespan_component
{
	double lifespan;
};

// collision_component represents the collision tag of an entity
struct collision_component
{
	char tag;
};

// asteroid_component represents the spawning properties of asteroids
struct asteroid_component
{
	double spawn_timer;
	double spawn_delay;
	float vel_x, vel_y;
	float width, height;
};
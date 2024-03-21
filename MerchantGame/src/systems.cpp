#pragma once
#include <vector>
#include <SDL.h>
#include <string>
#include "SDL.h"
#include <iostream>

using entity = std::size_t;

struct mobility_system
{
	void update(registry& reg, double deltaTime)
	{
		for (auto& it : reg.movements)
		{
			if (reg.sprites.find(it.first) == reg.sprites.end())
			{
				continue;
			}

			float tempX = it.second.vel_x;
			float tempY = it.second.vel_y;

			float diff = sqrt(pow(tempX, 2) + pow(tempY, 2));

			if (diff != 0)
			{
				tempX /= diff;
				tempY /= diff;
			}

			reg.sprites[it.first].src.x += tempX * deltaTime * it.second.speed;
			reg.sprites[it.first].src.y += tempY * deltaTime * it.second.speed;
		}
	}
};

struct sprite_system
{
	void update(registry& reg, SDL_Renderer* renderer)
	{
		for (auto& it : reg.sprites)
		{
			SDL_RenderCopyExF(renderer, it.second.texture, NULL, &it.second.src, it.second.angle, NULL, SDL_FLIP_NONE);
		}
	}
};

struct input_system
{
	void update(registry& reg, SDL_Event& e)
	{
		for (auto& it : reg.inputs)
		{
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP: it.second.input_y--; break;
				case SDLK_DOWN: it.second.input_y++; break;

				case SDLK_LEFT: it.second.input_x--; break;
				case SDLK_RIGHT: it.second.input_x++; break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP: it.second.input_y++; break;
				case SDLK_DOWN: it.second.input_y--; break;

				case SDLK_LEFT: it.second.input_x++; break;
				case SDLK_RIGHT: it.second.input_x--; break;
				}
			}
			if (reg.movements.find(it.first) == reg.movements.end())
			{
				continue;
			}
			reg.movements[it.first].vel_y = it.second.input_y;
			reg.movements[it.first].vel_x = it.second.input_x;
		}
	}
};

struct velocity_system
{
	void update(registry& reg, double deltaTime)
	{
		for (auto& it : reg.velocities)
		{
			if (reg.sprites.find(it.first) == reg.sprites.end())
			{
				continue;
			}
			if (reg.inputs.find(it.first) == reg.inputs.end())
			{
				continue;
			}

			it.second.vel_x += reg.inputs[it.first].input_x * deltaTime * it.second.speed;
			it.second.vel_y += reg.inputs[it.first].input_y * deltaTime * it.second.speed;

			it.second.vel_x *= pow(it.second.drag, deltaTime);
			it.second.vel_y *= pow(it.second.drag, deltaTime);

			reg.sprites[it.first].src.x += it.second.vel_x * deltaTime;
			reg.sprites[it.first].src.y += it.second.vel_y * deltaTime;
		}
	}
};

struct rotation_system
{
	void update(registry& reg, double deltaTime)
	{
		for (auto& it : reg.rotations)
		{
			if (reg.sprites.find(it.first) == reg.sprites.end())
			{
				continue;
			}

			reg.sprites[it.first].angle += it.second.deviation * deltaTime;
		}
	}
};

struct tracking_system
{
	void update(registry& reg, double deltaTime)
	{
		for (auto& it : reg.trackers)
		{
			if (reg.sprites.find(it.first) == reg.sprites.end())
			{
				continue;
			}
			if (it.second.follow_mouse)
			{
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);

				float angle_rad = atan2(mouse_y - reg.sprites[it.first].src.y, mouse_x - reg.sprites[it.first].src.x);
				float angle_deg = angle_rad * 180.0 / M_PI;

				reg.sprites[it.first].angle = angle_deg + 90;
				continue;
			}
			if (reg.sprites.find(it.second.target) == reg.sprites.end())
			{
				continue;
			}
			double angle_rad = atan2(reg.sprites[it.second.target].src.y - reg.sprites[it.first].src.y, reg.sprites[it.second.target].src.x - reg.sprites[it.first].src.x);
			double angle_deg = angle_rad * 180.0 / M_PI;

			reg.sprites[it.first].angle = angle_deg;
		}
	}
};
#pragma once
#include <vector>
#include <SDL.h>
#include <string>
#include "SDL.h"

struct mobility_system
{
	void update(registry& reg, double deltaTime)
	{
		for (auto& it : reg.movements)
		{
			if (reg.sprites.find(it.first) != reg.sprites.end())
			{
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
	}
};

struct sprite_system
{
	void update(registry& reg, SDL_Renderer* renderer)
	{
		for (auto& it : reg.sprites)
		{
			SDL_RenderCopyExF(renderer, it.second.texture, NULL, &it.second.src, NULL, NULL, SDL_FLIP_NONE);
		}
	}
};

struct input_system
{
	void update(registry& reg, SDL_Event& e, entity player)
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
			if (reg.movements.find(it.first) != reg.movements.end())
			{
				reg.movements[it.first].vel_y = it.second.input_y;
				reg.movements[it.first].vel_x = it.second.input_x;
			}
		}
	}
};
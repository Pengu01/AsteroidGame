#pragma once
#include <vector>
#include <SDL.h>
#include <string>
#include "SDL.h"
#include <iostream>

using entity = std::size_t;

// mobility_system updates the position of entities based on their movement components
// @param reg is the memory adress to the registry struct
// @param deltatime is the time between frames
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

			if (reg.controllers.find(it.first) != reg.controllers.end())
			{
				it.second.vel_x = reg.controllers[it.first].controller_x;
				it.second.vel_y = reg.controllers[it.first].controller_y;
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

// sprite_system renders the sprites of entities
// @param reg is the memory adress to the registry struct
// @param renderer is the SDL renderer used to render
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

// controller_system updates the controller components based on user input
// @param reg is the memory adress to the registry struct
// @param e is the event variable used by SDL
struct controller_system
{
	void update(registry& reg, SDL_Event& e)
	{
		for (auto& it : reg.controllers)
		{
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP: it.second.controller_y--; break;
				case SDLK_w: it.second.controller_y--; break;

				case SDLK_DOWN: it.second.controller_y++; break;
				case SDLK_s: it.second.controller_y++; break;

				case SDLK_LEFT: it.second.controller_x--; break;
				case SDLK_a: it.second.controller_x--; break;

				case SDLK_RIGHT: it.second.controller_x++; break;
				case SDLK_d: it.second.controller_x++; break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP: it.second.controller_y++; break;
				case SDLK_w: it.second.controller_y++; break;

				case SDLK_DOWN: it.second.controller_y--; break;
				case SDLK_s: it.second.controller_y--; break;

				case SDLK_LEFT: it.second.controller_x++; break;
				case SDLK_a: it.second.controller_x++; break;

				case SDLK_RIGHT: it.second.controller_x--; break;
				case SDLK_d: it.second.controller_x--; break;
				}
			}
		}
	}
};

// velocity_system updates the position of entities based on their velocity components
// @param reg is the memory adress to the registry struct
// @param deltatime is the time between frames
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
			if (reg.controllers.find(it.first) == reg.controllers.end())
			{
				continue;
			}

			it.second.vel_x += reg.controllers[it.first].controller_x * deltaTime * it.second.speed;
			it.second.vel_y += reg.controllers[it.first].controller_y * deltaTime * it.second.speed;

			it.second.vel_x *= pow(it.second.drag, deltaTime);
			it.second.vel_y *= pow(it.second.drag, deltaTime);

			reg.sprites[it.first].src.x += it.second.vel_x * deltaTime;
			reg.sprites[it.first].src.y += it.second.vel_y * deltaTime;
		}
	}
};

// rotation_system updates the rotation angle of entities
// @param reg is the memory adress to the registry struct
// @param deltatime is the time between frames
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

// tracking_system updates the rotation angle of entities to track a target or the mouse
// @param reg is the memory adress to the registry struct
struct tracking_system
{
	void update(registry& reg)
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

				float angle_deg = atan2(mouse_y - reg.sprites[it.first].src.y - reg.sprites[it.first].src.h / 2, mouse_x - reg.sprites[it.first].src.x - reg.sprites[it.first].src.w / 2) * 180.0 / M_PI;

				reg.sprites[it.first].angle = angle_deg + 90;
				continue;
			}
			if (reg.sprites.find(it.second.target) == reg.sprites.end())
			{
				continue;
			}
			float angle_deg = atan2(reg.sprites[it.second.target].src.y + reg.sprites[it.second.target].src.h / 2 - reg.sprites[it.first].src.y - reg.sprites[it.first].src.h / 2, reg.sprites[it.second.target].src.x + reg.sprites[it.second.target].src.w / 2 - reg.sprites[it.first].src.x - reg.sprites[it.first].src.w / 2) * 180.0 / M_PI;

			reg.sprites[it.first].angle = angle_deg + 90;
		}
	}
};

// lifespan_system removes entities that have exceeded their lifespan
// @param reg is the memory adress to the registry struct
// @param deltatime is the time between frames
struct lifespan_system
{
	void update(registry& reg, double deltaTime)
	{
		for (auto it = reg.lifespans.begin(); it != reg.lifespans.end(); )
		{
			it->second.lifespan -= deltaTime;
			if (it->second.lifespan <= 0)
			{
				if (reg.sprites.find(it->first) != reg.sprites.end())
				{
					reg.sprites.erase(it->first);
				}
				if (reg.movements.find(it->first) != reg.movements.end())
				{
					reg.movements.erase(it->first);
				}
				if (reg.controllers.find(it->first) != reg.controllers.end())
				{
					reg.controllers.erase(it->first);
				}
				if (reg.velocities.find(it->first) != reg.velocities.end())
				{
					reg.velocities.erase(it->first);
				}
				if (reg.rotations.find(it->first) != reg.rotations.end())
				{
					reg.rotations.erase(it->first);
				}
				if (reg.trackers.find(it->first) != reg.trackers.end())
				{
					reg.trackers.erase(it->first);
				}
				if (reg.collisions.find(it->first) != reg.collisions.end())
				{
					reg.collisions.erase(it->first);
				}
				it = reg.lifespans.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
};

// collision_system handles collisions between entities
// @param reg is the memory adress to the registry struct
struct collision_system
{
	void update(registry& reg)
	{
		for (auto it1 = reg.collisions.begin(); it1 != reg.collisions.end(); )
		{
			if (reg.sprites.find(it1->first) == reg.sprites.end())
			{
				++it1;
				continue;
			}
			for (auto it2 = reg.collisions.begin(); it2 != reg.collisions.end(); )
			{
				if (it1 == it2)
				{
					++it2;
					continue;
				}
				if (reg.sprites.find(it2->first) == reg.sprites.end())
				{
					++it2;
					continue;
				}
				if (!SDL_HasIntersectionF(&reg.sprites[it1->first].src, &reg.sprites[it2->first].src))
				{
					++it2;
					continue;
				}
				switch (it1->second.tag)
				{
				case 'a':
				{
					if (it2->second.tag == 'p')
					{
						reg.lifespans[it2->first] = { 0 };
					}
					if (it2->second.tag == 'b')
					{
						reg.lifespans[it1->first] = { 0 };
						reg.lifespans[it2->first] = { 0 };
					}
					break;
				}
				case 'p':
				{
					if (it2->second.tag == 'a')
					{
						reg.lifespans[it1->first] = { 0 };
					}
					break;
				}
				case 'b':
				{
					if (it2->second.tag == 'a')
					{
						reg.lifespans[it2->first] = { 0 };
						reg.lifespans[it1->first] = { 0 };
					}
					break;
				}
				default:
					break;
				}
				++it2;
			}
			++it1;
		}
	}
};

// asteroid_system spawns asteroids at regular intervals
// @param reg is the memory adress to the registry struct
// @param deltatime is the time between frames
// @param sdl is the memory adress of the SDL class
struct asteroid_system
{
	void update(registry& reg, double deltaTime, SDL& sdl)
	{
		for (auto& it : reg.asteroids)
		{
			it.second.spawn_timer -= deltaTime;
			if (it.second.spawn_timer <= 0)
			{
				it.second.spawn_timer = it.second.spawn_delay;
				entity asteroid = sdl.create_entity();
				reg.collisions[asteroid] = { 'a' };
				reg.sprites[asteroid] =
				{
					{
						(sdl.SCREEN_WIDTH / 2) - (((sdl.SCREEN_WIDTH / 2) + it.second.width) * it.second.vel_x) + ((rand() % (int)(1 + it.second.vel_y * (sdl.SCREEN_WIDTH - it.second.width))) - ((sdl.SCREEN_WIDTH / 2) * abs(it.second.vel_y))),
						(sdl.SCREEN_HEIGHT / 2) - (((sdl.SCREEN_HEIGHT / 2) + it.second.height) * it.second.vel_y) + ((rand() % (int)(1 + it.second.vel_x * (sdl.SCREEN_HEIGHT - it.second.height))) - ((sdl.SCREEN_HEIGHT / 2) * abs(it.second.vel_x))),
						it.second.width,
						it.second.height
					},
						sdl.textures[2],
						0
				};
				reg.movements[asteroid] = { it.second.vel_x,it.second.vel_y,200 };
				reg.lifespans[asteroid] = { 5 };
			}
		}
	}
};

// input_system handles user input for player actions
// @param reg is the memory adress to the registry struct
// @param sdl is the memory adress of the SDL class
// @param player is the id of the player entity
// @param e is the event variable used by SDL
struct input_system
{
	void update(registry& reg, entity player, SDL_Event& e, SDL& sdl)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_LSHIFT:
			{
				if (reg.movements.find(player) == reg.movements.end())
				{
					if (reg.velocities.find(player) != reg.velocities.end())
					{
						reg.velocities.erase(player);
						reg.movements[player] = { 0,0, 200 };
						return;
					}
				}
			}
			case SDLK_SPACE:
			{
				if (reg.sprites.find(player) == reg.sprites.end())
				{
					return;
				}
				entity bullet = sdl.create_entity();
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				float delta_x = mouse_x - (reg.sprites[player].src.x + (reg.sprites[player].src.w / 2));
				float delta_y = mouse_y - (reg.sprites[player].src.y + (reg.sprites[player].src.h / 2));
				float angle_deg = atan2(delta_y, delta_x) * 180.0 / M_PI;
				float diff = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
				if (diff != 0)
				{
					delta_x /= diff;
					delta_y /= diff;
				}
				reg.sprites[bullet] = { {reg.sprites[player].src.x + (reg.sprites[player].src.w / 2) - 7,reg.sprites[player].src.y + (reg.sprites[player].src.h / 2) - 5.5f,14,11} ,sdl.textures[1], angle_deg + 90 };
				reg.movements[bullet] = { delta_x, delta_y, 700 };
				reg.lifespans[bullet] = { 1 };
				reg.collisions[bullet] = { 'b' };
			}

			default:
				return;
			}
		}
		if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_LSHIFT:
			{
				if (reg.velocities.find(player) == reg.velocities.end())
				{
					if (reg.movements.find(player) != reg.movements.end())
					{
						float tempX = reg.movements[player].vel_x;
						float tempY = reg.movements[player].vel_y;
						float speed = reg.movements[player].speed;
						float diff = sqrt(pow(tempX, 2) + pow(tempY, 2));

						if (diff != 0)
						{
							tempX /= diff;
							tempY /= diff;
						}
						reg.movements.erase(player);
						reg.velocities[player] = { tempX * speed, tempY * speed, 0.5f, 600 };
						return;
					}
				}
			}
			}
		}
	}
};
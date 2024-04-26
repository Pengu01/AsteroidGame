#pragma once
#include <vector>
#include <SDL.h>
#include <string>

using entity = std::size_t;

// sprite_component represents the visual aspect of an entity
struct sprite_component
{
    // src is the source rectangle of the texture to be rendered
    SDL_FRect src;
    // texture is the SDL_Texture to be rendered
    SDL_Texture* texture;
    // angle is the rotation angle of the texture
    float angle;
};

// movement_component represents the movement properties of an entity
struct movement_component
{
    // vel_x is the horizontal velocity of the entity
    float vel_x;
    // vel_y is the vertical velocity of the entity
    float vel_y;
    // speed is the maximum speed of the entity
    float speed;
};

// controller_component represents the user input for controlling an entity
struct controller_component
{
    // controller_x is the horizontal input value from the controller
    float controller_x;
    // controller_y is the vertical input value from the controller
    float controller_y;
};

// velocity_component represents the velocity and drag of an entity
struct velocity_component
{
    // vel_x is the horizontal velocity of the entity
    float vel_x;
    // vel_y is the vertical velocity of the entity
    float vel_y;
    // drag is the drag coefficient of the entity
    float drag;
    // speed is the maximum speed of the entity
    float speed;
};

// rotation_component represents the rotational deviation of an entity
struct rotation_component
{
    // deviation is the rotational deviation of the entity
    float deviation;
};

// tracking_component represents the target or mouse tracking behavior of an entity
struct tracking_component
{
    // target is the entity to be tracked
    entity target;
    // follow_mouse is a boolean indicating whether the entity should follow the mouse
    bool follow_mouse;
};

// lifespan_component represents the remaining lifespan of an entity
struct lifespan_component
{
    // lifespan is the remaining lifespan of the entity
    double lifespan;
};

// collision_component represents the collision tag of an entity
struct collision_component
{
    // tag is the collision tag of the entity
    char tag;
};

// asteroid_component represents the spawning properties of asteroids
struct asteroid_component
{
    // spawn_timer is the timer for spawning asteroids
    double spawn_timer;
    // spawn_delay is the delay between asteroid spawns
    double spawn_delay;
    // vel_x is the horizontal velocity of the asteroid
    float vel_x;
    // vel_y is the vertical velocity of the asteroid
    float vel_y;
    // width is the width of the asteroid
    float width;
    // height is the height of the asteroid
    float height;
};
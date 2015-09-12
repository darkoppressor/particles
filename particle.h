/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef particle_h
#define particle_h

#include "particle_type.h"

#include <string>
#include <stdint.h>

class Particle{
public:

    std::string type;

    bool moved;

    bool alt_color;

    Particle();

    Particle_Type* get_type();
    bool is_rendered();
    std::string get_vertical_movement();
    std::string get_grow_movement();
    uint32_t vertical_chance();
    uint32_t horizontal_chance();
    uint32_t burn_chance();
    uint32_t grow_chance();
    bool is_flammable();
    bool is_burnable();
    bool is_solid();
    bool is_windblown();
    std::string get_decay_type();
    uint32_t get_decay_chance();
    std::string melts_into();
    std::string freezes_into();
    std::string evaporates_into();
    uint32_t get_mass();
    std::vector<std::string> get_move_tries();
    uint32_t get_allowed_moves();
    std::string annihilate(std::string particle);

    std::string get_color();

    void set_type(std::string get_type="air");

    void reset_moved();
    void flag_moved();

    //These two functions return false if the particle left the screen, or true otherwise
    bool move_vertical(uint32_t& move_to_x,uint32_t& move_to_y);
    bool move_horizontal(uint32_t& move_to_x,uint32_t& move_to_y);
    void move_to_position(uint32_t& x,uint32_t& y,uint32_t move_to_x,uint32_t move_to_y);

    bool decay_check();
    bool temperature_check();
    void burn_check(uint32_t x,uint32_t y);
    void grow_check(uint32_t x,uint32_t y);
    void movement(uint32_t x,uint32_t y);

    void render(uint32_t x,uint32_t y);
};

#endif

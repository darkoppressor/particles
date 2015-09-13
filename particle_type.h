/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef particle_type_h
#define particle_type_h

#include <string>
#include <vector>
#include <map>
#include <stdint.h>

class Particle_Type{
public:

    std::string name;

    bool is_rendered;

    std::string vertical_movement;
    std::string grow_movement;
    uint32_t vertical_chance;
    uint32_t horizontal_chance;
    uint32_t burn_chance;
    uint32_t grow_chance;
    bool flammable;
    bool burnable;
    bool solid;
    bool windblown;

    std::string decay_type;
    uint32_t decay_chance;

    std::string melts_into;
    std::string freezes_into;
    std::string evaporates_into;

    uint32_t mass;

    std::vector<std::string> move_tries;
    uint32_t allowed_moves;

    std::map<std::string,std::string> annihilations;

    Particle_Type();
};

#endif

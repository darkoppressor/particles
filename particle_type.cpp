/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "particle_type.h"

using namespace std;

Particle_Type::Particle_Type(){
    name="";

    is_rendered=false;

    vertical_movement="";
    grow_movement="";
    vertical_chance=0;
    horizontal_chance=0;
    burn_chance=0;
    grow_chance=0;
    flammable=false;
    burnable=false;
    solid=false;
    windblown=false;

    decay_type="";
    decay_chance=0;

    melts_into="";
    freezes_into="";
    evaporates_into="";

    mass=0;

    allowed_moves=0;
}

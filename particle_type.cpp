#include "particle_type.h"

using namespace std;

Particle_Type::Particle_Type(){
    name="";

    is_rendered=false;

    vertical_movement="";
    vertical_chance=0;
    horizontal_chance=0;
    flammable=false;
    solid=false;
    windblown=false;

    decay_type="";
    decay_chance=0;

    mass=0;

    allowed_moves=0;
}

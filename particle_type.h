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
    uint32_t vertical_chance;
    uint32_t horizontal_chance;
    bool flammable;
    bool solid;
    bool windblown;

    std::string decay_type;
    uint32_t decay_chance;

    uint32_t mass;

    std::vector<std::string> move_tries;
    uint32_t allowed_moves;

    std::map<std::string,std::string> annihilations;

    Particle_Type();
};

#endif

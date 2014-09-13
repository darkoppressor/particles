#ifndef game_world_h
#define game_world_h

#include "particle.h"
#include "collision.h"

#include <vector>
#include <string>

class Game_World{
public:

    uint32_t width;
    uint32_t height;

    uint32_t particle_size;

    uint32_t current_particle_type;

    uint32_t day_counter;
    uint32_t day;
    std::string season;

    std::string weather;
    uint32_t weather_intensity;

    bool wind_direction;
    uint32_t wind_strength;

    int temperature;

    std::vector< std::vector <Particle> > particles;

    void clear_world();
    void generate_world();

    void spawn_particles(std::string type,Collision_Rect box);

    void change_weather(std::string new_weather="");
    void change_wind();
    void change_temperature();

    void tick();
    void ai();
    void movement();
    void events();
    void animate();
    void render();

    void update_background();
    void render_background();
};

#endif

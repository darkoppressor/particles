#ifndef season_h
#define season_h

#include <string>
#include <stdint.h>

class Season{
public:

    std::string name;
    std::string next;

    uint32_t weather_change_chance;

    uint32_t rain_chance;
    uint32_t snow_chance;
    uint32_t sleet_chance;
    uint32_t cloud_chance;
    uint32_t sand_chance;

    uint32_t weather_intensity_min;
    uint32_t weather_intensity_max;

    uint32_t wind_strength_min;
    uint32_t wind_strength_max;

    uint32_t temperature_min;
    uint32_t temperature_max;

    Season();
};

#endif

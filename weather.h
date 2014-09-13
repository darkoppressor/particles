#ifndef weather_h
#define weather_h

#include <string>
#include <stdint.h>

class Weather{
public:

    std::string name;

    uint32_t wind_strength_min;
    uint32_t wind_strength_max;

    uint32_t temperature_min;
    uint32_t temperature_max;

    Weather();
};

#endif

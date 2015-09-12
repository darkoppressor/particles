/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

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

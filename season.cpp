#include "season.h"

using namespace std;

Season::Season(){
    name="";
    next="";

    weather_change_chance=0;

    rain_chance=0;
    snow_chance=0;
    sleet_chance=0;
    cloud_chance=0;
    sand_chance=0;

    weather_intensity_min=0;
    weather_intensity_max=0;

    wind_strength_min=0;
    wind_strength_max=0;

    temperature_min=0;
    temperature_max=0;
}

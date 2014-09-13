#ifndef game_constants_h
#define game_constants_h

#include <string>
#include <stdint.h>

extern double ZOOM_RATE;
extern double ZOOM_MIN;
extern double ZOOM_MAX;

extern double DAY_LENGTH;
extern uint32_t SEASON_LENGTH;

extern int FREEZING_POINT;

void set_game_constant(std::string name,std::string value);

#endif

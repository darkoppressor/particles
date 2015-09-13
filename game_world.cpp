/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "game_world.h"
#include "world.h"
#include "render.h"

using namespace std;

void Game_World::clear_world(){
    width=0;
    height=0;

    particle_size=0;

    current_particle_type=0;

    day_counter=0;
    day=0;
    season="spring";

    weather="none";
    weather_intensity=0;

    wind_direction=false;
    wind_strength=0;

    temperature=0;

    particles.clear();
}

void Game_World::generate_world(){
    clear_world();

    width=main_window.SCREEN_WIDTH;
    height=main_window.SCREEN_HEIGHT;

    particle_size=1;

    particles.resize(width,vector<Particle>(height));

    for(int x=0;x<width;x++){
        for(int y=height-game.rng.weighted_random_range(1,20,20,"strong");y<height;y++){
            particles[x][y].set_type("grass");
        }
    }

    change_weather();
    change_wind();
    change_temperature();
}

void Game_World::spawn_particles(string type,Collision_Rect box){
    for(int x=(int)box.x;x<(int)box.x+(int)box.w;x++){
        for(int y=(int)box.y;y<(int)box.y+(int)box.h;y++){
            if(x>0 && y>0 && x<width && y<height){
                particles[x][y].set_type(type);
            }
        }
    }
}

void Game_World::change_weather(string new_weather){
    Season* p_season=engine_interface.get_season(season);

    if(new_weather.length()>0 || game.rng.random_range(0,99)<p_season->weather_change_chance){
        wind_direction=game.rng.random_range(0,1);

        weather_intensity=game.rng.random_range(p_season->weather_intensity_min,p_season->weather_intensity_max);

        if(new_weather.length()==0){
            uint32_t chance_rain=p_season->rain_chance;
            uint32_t chance_snow=chance_rain+p_season->snow_chance;
            uint32_t chance_sleet=chance_snow+p_season->sleet_chance;
            uint32_t chance_cloud=chance_sleet+p_season->cloud_chance;
            uint32_t chance_sand=chance_cloud+p_season->sand_chance;

            uint32_t random=game.rng.random_range(0,99);

            if(p_season->rain_chance>0 && random>=0 && random<chance_rain){
                weather="rain";
            }
            else if(p_season->snow_chance>0 && random>=chance_rain && random<chance_snow){
                weather="snow";
            }
            else if(p_season->sleet_chance>0 && random>=chance_snow && random<chance_sleet){
                weather="sleet";
            }
            else if(p_season->cloud_chance>0 && random>=chance_sleet && random<chance_cloud){
                weather="cloud";
            }
            else if(p_season->sand_chance>0 && random>=chance_cloud && random<chance_sand){
                weather="sand";
            }
            else{
                weather="none";
            }
        }
        else{
            weather=new_weather;
        }
    }
}

void Game_World::change_wind(){
    Season* p_season=engine_interface.get_season(season);
    Weather* p_weather=engine_interface.get_weather(weather);

    wind_strength=game.rng.random_range(p_season->wind_strength_min,p_season->wind_strength_max);
    wind_strength+=game.rng.random_range(p_weather->wind_strength_min,p_weather->wind_strength_max);
}

void Game_World::change_temperature(){
    Season* p_season=engine_interface.get_season(season);
    Weather* p_weather=engine_interface.get_weather(weather);

    temperature=(int)game.rng.random_range(p_season->temperature_min,p_season->temperature_max);
    temperature-=(int)game.rng.random_range(p_weather->temperature_min,p_weather->temperature_max);
}

void Game_World::tick(){
    if(++day_counter>(uint32_t)(DAY_LENGTH*UPDATE_RATE)){
        day_counter=0;

        if(++day>=SEASON_LENGTH){
            day=0;

            season=engine_interface.get_season(season)->next;
        }

        change_weather();
        change_wind();
        change_temperature();
    }
}

void Game_World::ai(){
}

void Game_World::movement(){
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            particles[x][y].reset_moved();
        }
    }

    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            particles[x][y].movement(x,y);
        }
    }
}

void Game_World::events(){
    if(weather!="none"){
        if(game.rng.random_range(0,99)<weather_intensity/4){
            uint32_t CLOUD_SIZE=weather_intensity/2;

            uint32_t x=CLOUD_SIZE/2;
            uint32_t y=game.rng.random_range(0,height/3);
            if(!wind_direction){
                x=width-CLOUD_SIZE;
            }

            string weather_type="cloud";
            if(weather=="rain" || weather=="snow" || weather=="sleet" || weather=="sand"){
                weather_type=weather+"_cloud";
            }

            spawn_particles(weather_type,Collision_Rect(x,y,CLOUD_SIZE,CLOUD_SIZE));
        }
    }
}

void Game_World::animate(){
}

void Game_World::render(){
    for(int x=0;x<particles.size();x++){
        for(int y=0;y<particles[x].size();y++){
            particles[x][y].render(x,y);
        }
    }

    string message="";

    message+="Day: "+string_stuff.num_to_string(day+1)+"/"+string_stuff.num_to_string(SEASON_LENGTH)+"\n";
    message+="Season: "+string_stuff.first_letter_capital(season)+"\n";
    message+="Weather: "+string_stuff.first_letter_capital(weather)+" ("+string_stuff.num_to_string(weather_intensity)+")"+"\n";

    if(!wind_direction){
        message+="Wind: "+string_stuff.num_to_string(wind_strength)+" kn West"+"\n";
    }
    else{
        message+="Wind: "+string_stuff.num_to_string(wind_strength)+" kn East"+"\n";
    }

    message+="Temperature: "+string_stuff.num_to_string(temperature)+" "+string(1,(unsigned char)167)+"C"+"\n";

    message+="\n";
    message+="Particle Type: "+string_stuff.capitalize_all_words(string_stuff.underscore_to_space(engine_interface.particle_types[game.world.current_particle_type].name))+"\n";

    engine_interface.get_font("small")->show(2.0,8.0,message,"ui_white");
}

void Game_World::update_background(){
}

void Game_World::render_background(){
    string dark="";
    if(weather!="none"){
        dark="_dark";
    }

    render_rectangle(0,0,main_window.SCREEN_WIDTH,main_window.SCREEN_HEIGHT,1.0,"background_"+season+dark);
}

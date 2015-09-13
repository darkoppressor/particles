/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "engine_interface.h"
#include "world.h"
#include "render.h"

#include <boost/algorithm/string.hpp>

using namespace std;

void Engine_Interface::load_data_game(){
    load_data("particle_type");
    load_data("season");
    load_data("weather");
}

void Engine_Interface::load_data_script_game(string script,File_IO_Load* load){
    if(script=="particle_type"){
        load_particle_types(load);
    }
    else if(script=="season"){
        load_seasons(load);
    }
    else if(script=="weather"){
        load_weather(load);
    }
}

void Engine_Interface::unload_data_game(){
    particle_types.clear();
    seasons.clear();
    weather.clear();
}

void Engine_Interface::load_particle_types(File_IO_Load* load){
    particle_types.push_back(Particle_Type());

    bool multi_line_comment=false;

    while(!load->eof()){
        string line="";

        string str_name="name:";
        string str_is_rendered="is_rendered:";
        string str_vertical_movement="vertical_movement:";
        string str_grow_movement="grow_movement:";
        string str_vertical_chance="vertical_chance:";
        string str_horizontal_chance="horizontal_chance:";
        string str_burn_chance="burn_chance:";
        string str_grow_chance="grow_chance:";
        string str_flammable="flammable:";
        string str_burnable="burnable:";
        string str_solid="solid:";
        string str_windblown="windblown:";
        string str_decay_type="decay_type:";
        string str_decay_chance="decay_chance:";
        string str_melts_into="melts_into:";
        string str_freezes_into="freezes_into:";
        string str_evaporates_into="evaporates_into:";
        string str_mass="mass:";
        string str_move_tries="move_tries:";
        string str_allowed_moves="allowed_moves:";
        string str_annihilation="annihilation:";

        load->getline(&line);
        boost::algorithm::trim(line);

        if(boost::algorithm::contains(line,"*/")){
            multi_line_comment=false;
        }
        if(!multi_line_comment && boost::algorithm::starts_with(line,"/*")){
            multi_line_comment=true;
        }
        else if(!multi_line_comment && boost::algorithm::starts_with(line,"//")){
        }

        //name
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_name)){
            line.erase(0,str_name.length());

            particle_types[particle_types.size()-1].name=line;
        }
        //is_rendered
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_is_rendered)){
            line.erase(0,str_is_rendered.length());

            particle_types[particle_types.size()-1].is_rendered=string_stuff.string_to_bool(line);
        }
        //vertical_movement
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_vertical_movement)){
            line.erase(0,str_vertical_movement.length());

            particle_types[particle_types.size()-1].vertical_movement=line;
        }
        //grow_movement
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_grow_movement)){
            line.erase(0,str_grow_movement.length());

            particle_types[particle_types.size()-1].grow_movement=line;
        }
        //vertical_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_vertical_chance)){
            line.erase(0,str_vertical_chance.length());

            particle_types[particle_types.size()-1].vertical_chance=string_stuff.string_to_unsigned_long(line);
        }
        //horizontal_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_horizontal_chance)){
            line.erase(0,str_horizontal_chance.length());

            particle_types[particle_types.size()-1].horizontal_chance=string_stuff.string_to_unsigned_long(line);
        }
        //burn_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_burn_chance)){
            line.erase(0,str_burn_chance.length());

            particle_types[particle_types.size()-1].burn_chance=string_stuff.string_to_unsigned_long(line);
        }
        //grow_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_grow_chance)){
            line.erase(0,str_grow_chance.length());

            particle_types[particle_types.size()-1].grow_chance=string_stuff.string_to_unsigned_long(line);
        }
        //flammable
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_flammable)){
            line.erase(0,str_flammable.length());

            particle_types[particle_types.size()-1].flammable=string_stuff.string_to_bool(line);
        }
        //burnable
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_burnable)){
            line.erase(0,str_burnable.length());

            particle_types[particle_types.size()-1].burnable=string_stuff.string_to_bool(line);
        }
        //solid
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_solid)){
            line.erase(0,str_solid.length());

            particle_types[particle_types.size()-1].solid=string_stuff.string_to_bool(line);
        }
        //windblown
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_windblown)){
            line.erase(0,str_windblown.length());

            particle_types[particle_types.size()-1].windblown=string_stuff.string_to_bool(line);
        }
        //decay_type
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_decay_type)){
            line.erase(0,str_decay_type.length());

            particle_types[particle_types.size()-1].decay_type=line;
        }
        //decay_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_decay_chance)){
            line.erase(0,str_decay_chance.length());

            particle_types[particle_types.size()-1].decay_chance=string_stuff.string_to_unsigned_long(line);
        }
        //melts_into
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_melts_into)){
            line.erase(0,str_melts_into.length());

            particle_types[particle_types.size()-1].melts_into=line;
        }
        //freezes_into
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_freezes_into)){
            line.erase(0,str_freezes_into.length());

            particle_types[particle_types.size()-1].freezes_into=line;
        }
        //evaporates_into
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_evaporates_into)){
            line.erase(0,str_evaporates_into.length());

            particle_types[particle_types.size()-1].evaporates_into=line;
        }
        //mass
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_mass)){
            line.erase(0,str_mass.length());

            particle_types[particle_types.size()-1].mass=string_stuff.string_to_unsigned_long(line);
        }
        //move_tries
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_move_tries)){
            line.erase(0,str_move_tries.length());

            vector<string> entries;
            boost::algorithm::split(entries,line,boost::algorithm::is_any_of(","));

            for(int i=0;i<entries.size();i++){
                particle_types[particle_types.size()-1].move_tries.push_back(entries[i]);
            }
        }
        //allowed_moves
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_allowed_moves)){
            line.erase(0,str_allowed_moves.length());

            particle_types[particle_types.size()-1].allowed_moves=string_stuff.string_to_unsigned_long(line);
        }
        //annihilation
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_annihilation)){
            line.erase(0,str_annihilation.length());

            vector<string> entries;
            boost::algorithm::split(entries,line,boost::algorithm::is_any_of(","));

            if(entries.size()>=2){
                particle_types[particle_types.size()-1].annihilations[entries[0]]=entries[1];
            }
        }

        else if(!multi_line_comment && boost::algorithm::starts_with(line,"</particle_type>")){
            return;
        }
    }
}

void Engine_Interface::load_seasons(File_IO_Load* load){
    seasons.push_back(Season());

    bool multi_line_comment=false;

    while(!load->eof()){
        string line="";

        string str_name="name:";
        string str_next="next:";
        string str_weather_change_chance="weather_change_chance:";
        string str_rain_chance="rain_chance:";
        string str_snow_chance="snow_chance:";
        string str_sleet_chance="sleet_chance:";
        string str_cloud_chance="cloud_chance:";
        string str_sand_chance="sand_chance:";
        string str_weather_intensity="weather_intensity:";
        string str_wind_strength="wind_strength:";
        string str_temperature="temperature:";

        load->getline(&line);
        boost::algorithm::trim(line);

        if(boost::algorithm::contains(line,"*/")){
            multi_line_comment=false;
        }
        if(!multi_line_comment && boost::algorithm::starts_with(line,"/*")){
            multi_line_comment=true;
        }
        else if(!multi_line_comment && boost::algorithm::starts_with(line,"//")){
        }

        //name
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_name)){
            line.erase(0,str_name.length());

            seasons[seasons.size()-1].name=line;
        }
        //next
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_next)){
            line.erase(0,str_next.length());

            seasons[seasons.size()-1].next=line;
        }
        //weather_change_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_weather_change_chance)){
            line.erase(0,str_weather_change_chance.length());

            seasons[seasons.size()-1].weather_change_chance=string_stuff.string_to_unsigned_long(line);
        }
        //rain_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_rain_chance)){
            line.erase(0,str_rain_chance.length());

            seasons[seasons.size()-1].rain_chance=string_stuff.string_to_unsigned_long(line);
        }
        //snow_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_snow_chance)){
            line.erase(0,str_snow_chance.length());

            seasons[seasons.size()-1].snow_chance=string_stuff.string_to_unsigned_long(line);
        }
        //sleet_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_sleet_chance)){
            line.erase(0,str_sleet_chance.length());

            seasons[seasons.size()-1].sleet_chance=string_stuff.string_to_unsigned_long(line);
        }
        //cloud_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_cloud_chance)){
            line.erase(0,str_cloud_chance.length());

            seasons[seasons.size()-1].cloud_chance=string_stuff.string_to_unsigned_long(line);
        }
        //sand_chance
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_sand_chance)){
            line.erase(0,str_sand_chance.length());

            seasons[seasons.size()-1].sand_chance=string_stuff.string_to_unsigned_long(line);
        }
        //weather_intensity
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_weather_intensity)){
            line.erase(0,str_weather_intensity.length());

            vector<string> entries;
            boost::algorithm::split(entries,line,boost::algorithm::is_any_of("-"));

            if(entries.size()>=2){
                seasons[seasons.size()-1].weather_intensity_min=string_stuff.string_to_unsigned_long(entries[0]);
                seasons[seasons.size()-1].weather_intensity_max=string_stuff.string_to_unsigned_long(entries[1]);
            }
        }
        //wind_strength
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_wind_strength)){
            line.erase(0,str_wind_strength.length());

            vector<string> entries;
            boost::algorithm::split(entries,line,boost::algorithm::is_any_of("-"));

            if(entries.size()>=2){
                seasons[seasons.size()-1].wind_strength_min=string_stuff.string_to_unsigned_long(entries[0]);
                seasons[seasons.size()-1].wind_strength_max=string_stuff.string_to_unsigned_long(entries[1]);
            }
        }
        //temperature
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_temperature)){
            line.erase(0,str_temperature.length());

            vector<string> entries;
            boost::algorithm::split(entries,line,boost::algorithm::is_any_of("-"));

            if(entries.size()>=2){
                seasons[seasons.size()-1].temperature_min=string_stuff.string_to_unsigned_long(entries[0]);
                seasons[seasons.size()-1].temperature_max=string_stuff.string_to_unsigned_long(entries[1]);
            }
        }

        else if(!multi_line_comment && boost::algorithm::starts_with(line,"</season>")){
            return;
        }
    }
}

void Engine_Interface::load_weather(File_IO_Load* load){
    weather.push_back(Weather());

    bool multi_line_comment=false;

    while(!load->eof()){
        string line="";

        string str_name="name:";
        string str_wind_strength="wind_strength:";
        string str_temperature="temperature:";

        load->getline(&line);
        boost::algorithm::trim(line);

        if(boost::algorithm::contains(line,"*/")){
            multi_line_comment=false;
        }
        if(!multi_line_comment && boost::algorithm::starts_with(line,"/*")){
            multi_line_comment=true;
        }
        else if(!multi_line_comment && boost::algorithm::starts_with(line,"//")){
        }

        //name
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_name)){
            line.erase(0,str_name.length());

            weather[weather.size()-1].name=line;
        }
        //wind_strength
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_wind_strength)){
            line.erase(0,str_wind_strength.length());

            vector<string> entries;
            boost::algorithm::split(entries,line,boost::algorithm::is_any_of("-"));

            if(entries.size()>=2){
                weather[weather.size()-1].wind_strength_min=string_stuff.string_to_unsigned_long(entries[0]);
                weather[weather.size()-1].wind_strength_max=string_stuff.string_to_unsigned_long(entries[1]);
            }
        }
        //temperature
        else if(!multi_line_comment && boost::algorithm::starts_with(line,str_temperature)){
            line.erase(0,str_temperature.length());

            vector<string> entries;
            boost::algorithm::split(entries,line,boost::algorithm::is_any_of("-"));

            if(entries.size()>=2){
                weather[weather.size()-1].temperature_min=string_stuff.string_to_unsigned_long(entries[0]);
                weather[weather.size()-1].temperature_max=string_stuff.string_to_unsigned_long(entries[1]);
            }
        }

        else if(!multi_line_comment && boost::algorithm::starts_with(line,"</weather>")){
            return;
        }
    }
}

Particle_Type* Engine_Interface::get_particle_type(string name){
    Particle_Type* ptr_object=0;

    for(int i=0;i<particle_types.size();i++){
        if(particle_types[i].name==name){
            ptr_object=&particle_types[i];

            break;
        }
    }

    if(ptr_object==0){
        message_log.add_error("Error accessing particle type '"+name+"'");
    }

    return ptr_object;
}

Season* Engine_Interface::get_season(string name){
    Season* ptr_object=0;

    for(int i=0;i<seasons.size();i++){
        if(seasons[i].name==name){
            ptr_object=&seasons[i];

            break;
        }
    }

    if(ptr_object==0){
        message_log.add_error("Error accessing season '"+name+"'");
    }

    return ptr_object;
}

Weather* Engine_Interface::get_weather(string name){
    Weather* ptr_object=0;

    for(int i=0;i<weather.size();i++){
        if(weather[i].name==name){
            ptr_object=&weather[i];

            break;
        }
    }

    if(ptr_object==0){
        message_log.add_error("Error accessing weather '"+name+"'");
    }

    return ptr_object;
}

void Engine_Interface::open_window(Window* window){
    if(!is_window_open(window)){
        window_z_order.insert(window_z_order.begin(),window);

        reset_gui_selected_object();
    }
}

void Engine_Interface::close_window(Window* window){
    for(int i=0;i<window_z_order.size();i++){
        if(window_z_order[i]==window){
            window_z_order.erase(window_z_order.begin()+i);

            reset_gui_selected_object();

            break;
        }
    }
}

void Engine_Interface::render_title_background(){
    Bitmap_Font* font=get_font("small");

    render_rectangle(0,0,main_window.SCREEN_WIDTH,main_window.SCREEN_HEIGHT,1.0,"ui_black");

    font->show(0,main_window.SCREEN_HEIGHT-font->spacing_y*2.0,"Version "+get_version()+"\nChecksum "+CHECKSUM,"ui_white");

    Image_Data* logo=image.get_image("logo");

    double logo_scale_x=(double)main_window.SCREEN_WIDTH/(double)1280.0;
    double logo_scale_y=(double)main_window.SCREEN_HEIGHT/(double)720.0;

    render_texture(main_window.SCREEN_WIDTH-logo->w*logo_scale_x,main_window.SCREEN_HEIGHT-logo->h*logo_scale_y,*logo,1.0,logo_scale_x,logo_scale_y);
}

void Engine_Interface::render_pause(){
    Bitmap_Font* font=get_font("standard");

    string msg="Paused";
    font->show((main_window.SCREEN_WIDTH-(font->spacing_x*msg.length()))/2,(main_window.SCREEN_HEIGHT-font->spacing_y)/2,msg,"ui_white");
}

void Engine_Interface::render_fps(int render_rate,double ms_per_frame,int logic_frame_rate){
    get_font("small")->show(2,2,"FPS: "+string_stuff.num_to_string(render_rate)+"\n"+network.get_stats(),"ui_white");
}

void Engine_Interface::render_loading_screen(double percentage,string load_message){
    Bitmap_Font* font=get_font("standard");

    SDL_SetRenderDrawColor(main_window.renderer,0,0,0,255);
    SDL_RenderClear(main_window.renderer);

    ///If images are loaded
    /**render_texture(0,0,image.loading_screen_main,0.25);
    render_texture((main_window.SCREEN_WIDTH-image.logo_hubert.w)/2.0,30,image.logo_hubert);*/

    render_rectangle(0,0,main_window.SCREEN_WIDTH,main_window.SCREEN_HEIGHT,1.0,"ui_black");

    double bar_width=240.0*percentage;
    double max_bar_width=240.0*1.0;
    render_rectangle(main_window.SCREEN_WIDTH/2.0-120-2,main_window.SCREEN_HEIGHT-75-2,max_bar_width+4,30+4,1.0,"ui_3");
    render_rectangle(main_window.SCREEN_WIDTH/2.0-120,main_window.SCREEN_HEIGHT-75,bar_width,30,1.0,"ui_1");

    string msg=string_stuff.num_to_string((int)(percentage*100.0))+"%";

    font->show(main_window.SCREEN_WIDTH/2.0-120+(max_bar_width-msg.length()*font->spacing_x)/2.0,main_window.SCREEN_HEIGHT-75+font->spacing_y/4.0,msg,"ui_0");

    font->show((main_window.SCREEN_WIDTH-load_message.length()*font->spacing_x)/2.0,main_window.SCREEN_HEIGHT-75+font->spacing_y*2.0,load_message,"ui_0");

    SDL_RenderPresent(main_window.renderer);
}

string Engine_Interface::get_game_window_caption(){
    string msg="";

    return msg;
}

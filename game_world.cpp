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
    season=0;

    weather="none";
    weather_intensity=0;

    wind_direction=false;
    wind_strength=0;

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

    ///
    weather="none";
    weather_intensity=20;
    wind_strength=25;
    ///
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

void Game_World::tick(){
    if(++day_counter>(uint32_t)(2.0*UPDATE_RATE)){
        day_counter=0;

        if(++day>30){
            day=0;

            if(++season>3){
                season=0;
            }
        }

        /**if(game.rng.random_range(0,99)<10){
            int random=game.rng.random_range(0,99);
            if(random>=0 && random<30){
                weather="rain";
            }
            else if(random>=30 && random<60){
                weather="snow";
            }
            else if(random>=60 && random<90){
                weather="sleet";
            }
            else if(random>=90 && random<100){
                weather="none";
            }
        }*/
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

    message+="Day: "+string_stuff.num_to_string(day)+"\n";
    message+="Season: "+string_stuff.num_to_string(season)+"\n";
    message+="Weather: "+string_stuff.first_letter_capital(weather)+"\n";

    if(!wind_direction){
        message+="Wind: West "+string_stuff.num_to_string(wind_strength)+"\n";
    }
    else{
        message+="Wind: East "+string_stuff.num_to_string(wind_strength)+"\n";
    }

    message+="Particle Type: "+string_stuff.capitalize_all_words(string_stuff.underscore_to_space(engine_interface.particle_types[game.world.current_particle_type].name))+"\n";

    engine_interface.get_font("small")->show(2.0,8.0,message,"ui_white");
}

void Game_World::update_background(){
}

void Game_World::render_background(){
    render_rectangle(0,0,main_window.SCREEN_WIDTH,main_window.SCREEN_HEIGHT,1.0,"background");
}

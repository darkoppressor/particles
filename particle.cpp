/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "particle.h"
#include "world.h"
#include "render.h"

using namespace std;

Particle::Particle(){
    type="air";

    reset_moved();

    alt_color=false;
}

Particle_Type* Particle::get_type(){
    return engine_interface.get_particle_type(type);
}

bool Particle::is_rendered(){
    return get_type()->is_rendered;
}

string Particle::get_vertical_movement(){
    return get_type()->vertical_movement;
}

string Particle::get_grow_movement(){
    return get_type()->grow_movement;
}

uint32_t Particle::vertical_chance(){
    return get_type()->vertical_chance;
}

uint32_t Particle::horizontal_chance(){
    return get_type()->horizontal_chance;
}

uint32_t Particle::burn_chance(){
    return get_type()->burn_chance;
}

uint32_t Particle::grow_chance(){
    return get_type()->grow_chance;
}

bool Particle::is_flammable(){
    return get_type()->flammable;
}

bool Particle::is_burnable(){
    return get_type()->burnable;
}

bool Particle::is_solid(){
    return get_type()->solid;
}

bool Particle::is_windblown(){
    return get_type()->windblown;
}

string Particle::get_decay_type(){
    return get_type()->decay_type;
}

uint32_t Particle::get_decay_chance(){
    return get_type()->decay_chance;
}

string Particle::melts_into(){
    return get_type()->melts_into;
}

string Particle::freezes_into(){
    return get_type()->freezes_into;
}

string Particle::evaporates_into(){
    return get_type()->evaporates_into;
}

uint32_t Particle::get_mass(){
    return get_type()->mass;
}

vector<string> Particle::get_move_tries(){
    return get_type()->move_tries;
}

uint32_t Particle::get_allowed_moves(){
    return get_type()->allowed_moves;
}

string Particle::annihilate(string particle){
    map<string,string>::iterator it=get_type()->annihilations.find(particle);

    if(it!=get_type()->annihilations.end()){
        return it->second;
    }
    else{
        return "none";
    }
}

string Particle::get_color(){
    if(is_rendered()){
        if(!alt_color){
            return "particle_"+type+"1";
        }
        else{
            return "particle_"+type+"2";
        }
    }
    else{
        return "white";
    }
}

void Particle::set_type(string get_type){
    type=get_type;

    alt_color=game.rng.random_range(0,1);
}

void Particle::reset_moved(){
    moved=false;
}

void Particle::flag_moved(){
    moved=true;
}

bool Particle::move_vertical(uint32_t& move_to_x,uint32_t& move_to_y){
    if(get_vertical_movement()!="none"){
        uint32_t vertical_chance_bounded=vertical_chance();
        if(vertical_chance_bounded>100){
            vertical_chance_bounded=100;
        }

        if(vertical_chance_bounded==100 || game.rng.random_range(0,99)<vertical_chance_bounded){
            if(get_vertical_movement()=="up"){
                if(move_to_y>0){
                    move_to_y--;
                }
                else if(!is_solid()){
                    flag_moved();
                    set_type("air");
                    return false;
                }
            }
            else if(get_vertical_movement()=="down"){
                if(move_to_y<game.world.height-1){
                    move_to_y++;
                }
            }
            else if(get_vertical_movement()=="random"){
                if(game.rng.random_range(0,99)<50){
                    if(move_to_y>0){
                        move_to_y--;
                    }
                    else if(!is_solid()){
                        flag_moved();
                        set_type("air");
                        return false;
                    }
                }
                else{
                    if(move_to_y<game.world.height-1){
                        move_to_y++;
                    }
                }
            }
        }
    }

    return true;
}

bool Particle::move_horizontal(uint32_t& move_to_x,uint32_t& move_to_y){
    uint32_t horizontal_chance_bounded=horizontal_chance();
    if(horizontal_chance_bounded>0 && is_windblown()){
        horizontal_chance_bounded+=(uint32_t)floor((double)game.world.wind_strength*(1.0/((double)get_mass()*8.0)));
    }
    if(horizontal_chance_bounded>100){
        horizontal_chance_bounded=100;
    }

    if(horizontal_chance_bounded>0){
        if(game.rng.random_range(0,99)<horizontal_chance_bounded){
            int left_chance=50;
            if(is_windblown()){
                if(!game.world.wind_direction){
                    left_chance+=game.world.wind_strength;
                    if(left_chance>100){
                        left_chance=100;
                    }
                }
                else{
                    left_chance-=game.world.wind_strength;
                    if(left_chance<0){
                        left_chance=0;
                    }
                }
            }

            if(game.rng.random_range(0,99)<left_chance){
                if(move_to_x>0){
                    move_to_x--;
                }
                else if(!is_solid()){
                    flag_moved();
                    set_type("air");
                    return false;
                }
            }
            else{
                if(move_to_x<game.world.width-1){
                    move_to_x++;
                }
                else if(!is_solid()){
                    flag_moved();
                    set_type("air");
                    return false;
                }
            }
        }
    }

    return true;
}

void Particle::move_to_position(uint32_t& x,uint32_t& y,uint32_t move_to_x,uint32_t move_to_y){
    Particle* particle=&game.world.particles[move_to_x][move_to_y];

    string annihilate_particle=annihilate(particle->type);

    bool mass_check=false;
    if(!particle->is_solid()){
        if(move_to_y>y){
            if(get_mass()>=particle->get_mass()){
                mass_check=true;
            }
        }
        else{
            mass_check=true;
        }
    }

    if(!particle->moved && type!=particle->type && (annihilate_particle!="none" || mass_check)){
        particle->flag_moved();
        flag_moved();

        x=move_to_x;
        y=move_to_y;

        if(annihilate_particle=="none"){
            string particle_type=particle->type;
            particle->set_type(type);
            set_type(particle_type);
        }
        else{
            string remainder="air";
            if((type=="fire" && particle->is_flammable()) || (is_flammable() && particle->type=="fire")){
                remainder="fire";
            }
            else if((type=="oil_fire" && particle->is_flammable()) || (is_flammable() && particle->type=="oil_fire")){
                remainder="fire";
                if(type=="oil" || particle->type=="oil"){
                    remainder="oil_fire";
                }
            }

            particle->set_type(annihilate_particle);
            set_type(remainder);
        }
    }
}

bool Particle::decay_check(){
    if(get_decay_type()!="none"){
        if(game.rng.random_range(0,9999)<get_decay_chance()){
            set_type(get_decay_type());

            return true;
        }
    }

    return false;
}

bool Particle::temperature_check(){
    if(melts_into()!="none" && game.world.temperature>FREEZING_POINT){
        if(game.rng.random_range(0,99999)<(uint32_t)ceil((double)game.world.temperature/1.45)){
            set_type(melts_into());

            return true;
        }
    }

    if(evaporates_into()!="none" && game.world.temperature>FREEZING_POINT){
        if(game.rng.random_range(0,99999)<(uint32_t)ceil((double)game.world.temperature/1.45)){
            set_type(evaporates_into());

            return true;
        }
    }

    if(freezes_into()!="none" && game.world.temperature<=FREEZING_POINT){
        if(game.rng.random_range(0,99999)<(uint32_t)ceil(abs((double)game.world.temperature)*3.5)){
            set_type(freezes_into());

            return true;
        }
    }

    return false;
}

void Particle::burn_check(uint32_t x,uint32_t y){
    if(burn_chance()>0){
        if(game.rng.random_range(0,99)<burn_chance()){
            uint32_t burn_x=x;
            uint32_t burn_y=y;

            if(game.rng.random_range(0,99)<50){
                if(game.rng.random_range(0,99)<50){
                    if(burn_x>0){
                        burn_x--;
                    }
                }
                else{
                    if(burn_x<game.world.width-1){
                        burn_x++;
                    }
                }
            }

            if(game.rng.random_range(0,99)<50){
                if(game.rng.random_range(0,99)<50){
                    if(burn_y>0){
                        burn_y--;
                    }
                }
                else{
                    if(burn_y<game.world.height-1){
                        burn_y++;
                    }
                }
            }

            Particle* particle=&game.world.particles[burn_x][burn_y];

            if(particle->is_burnable()){
                string annihilate_particle=particle->annihilate("fire");

                if(annihilate_particle!="none"){
                    particle->set_type(annihilate_particle);
                }
            }
        }
    }
}

void Particle::grow_check(uint32_t x,uint32_t y){
    if(grow_chance()>0){
        if(game.rng.random_range(0,99)<grow_chance()){
            uint32_t grow_x=x;
            uint32_t grow_y=y;

            if(get_grow_movement()=="both" || get_grow_movement()=="horizontal"){
                if(game.rng.random_range(0,99)<50){
                    if(game.rng.random_range(0,99)<50){
                        if(grow_x>0){
                            grow_x--;
                        }
                    }
                    else{
                        if(grow_x<game.world.width-1){
                            grow_x++;
                        }
                    }
                }
            }

            if(get_grow_movement()=="both" || get_grow_movement()=="vertical"){
                if(game.rng.random_range(0,99)<50){
                    if(game.rng.random_range(0,99)<50){
                        if(grow_y>0){
                            grow_y--;
                        }
                    }
                    else{
                        if(grow_y<game.world.height-1){
                            grow_y++;
                        }
                    }
                }
            }

            Particle* particle=&game.world.particles[grow_x][grow_y];

            if(particle->type=="air"){
                particle->set_type(type);
            }
        }
    }
}

void Particle::movement(uint32_t x,uint32_t y){
    if(get_mass()>0 && !decay_check() && !temperature_check()){
        vector<string> move_tries=get_move_tries();

        for(uint32_t i=0,moves=0;i<move_tries.size() && !moved;i++){
            uint32_t move_to_x=x;
            uint32_t move_to_y=y;

            if(move_tries[i]=="both" || move_tries[i]=="vertical"){
                if(!move_vertical(move_to_x,move_to_y)){
                    break;
                }
            }

            if(move_tries[i]=="both" || move_tries[i]=="horizontal"){
                if(!move_horizontal(move_to_x,move_to_y)){
                    break;
                }
            }

            move_to_position(x,y,move_to_x,move_to_y);

            if(moved){
                if(++moves<get_allowed_moves() && i+1<move_tries.size()){
                    reset_moved();
                }
            }
        }

        if(!moved){
            burn_check(x,y);

            grow_check(x,y);
        }
    }
}

void Particle::render(uint32_t x,uint32_t y){
    if(is_rendered()){
        double particle_size=(double)game.world.particle_size;

        Collision_Rect box((double)x*particle_size,(double)y*particle_size,particle_size,particle_size);

        if(collision_check_rect(box,game.camera)){
            render_rectangle(box.x*game.camera_zoom-game.camera.x,box.y*game.camera_zoom-game.camera.y,particle_size,particle_size,1.0,get_color());
        }
    }
}

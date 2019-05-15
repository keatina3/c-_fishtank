#include <string>
#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include "fish.h"
#include "site.h"

Site::Site(){
    try {       // testing bad memory alloc //
        fish.resize(3);     // resizing to 3. One vector for each fish type //
    } catch(std::bad_alloc const &err) {
        std::cerr << "Bad allocation on Site" << std::endl;
        std::cerr << err.what() << std::endl;
        exit(1);
    }
}

Site::~Site(){
    // looping through and freeing all allocated memory //
    for(int i=0;i<3;i++)
        for(Fish_vec::iterator f = fish[i].begin(); f != fish[i].end(); f++)
            delete (*f);
}

// returns ptr to Fish type fish_id @ index //
Fish *Site::get_fish(const int fish_id, const int index) const {
    // throw/catch out of bounds tests //
    if(index >= (int)fish[fish_id].size() || fish_id < 0 || fish_id > 2)
        throw std::range_error(__FILE__);
    
    Fish* tmp = fish[fish_id][index];
    return tmp;
}

// adds fish of type fish_id to Site //
void Site::add_fish(Fish *new_fish){
    int id = new_fish->get_id();

    try {
        fish[id].push_back(new_fish);
    } catch(std::bad_alloc const &err) {
        std::cerr << "Bad allocation adding fish" << std::endl;
        std::cerr << err.what() << std::endl;
        exit(1);
    }
}

// deletes a fish from vector on site. If "kill", also frees fish entirely //
void Site::del_fish(const int fish_id, const int index, const bool kill){
    // custom throw to demonstrate throwing an error message //
    if(index >= (int)fish[fish_id].size() || fish_id < 0 || fish_id > 2){
        std::stringstream err_msg;
        err_msg << "Dummy error message for out-of-range error";
        err_msg << "Error in " << __FILE__ << "on line " << __LINE__ << "\n";
        throw std::range_error(err_msg.str());
    }

    if(kill)
        delete fish[fish_id][index];

    try {
        fish[fish_id].erase(fish[fish_id].begin() + index);
    } catch(std::exception const &err) {
        std::cerr << "Error deleting fish from vector." << std::endl;
        std::cerr << err.what() << std::endl;
        exit(1);
    }
}

// returns total # of fish of type fish_id on Site //
int Site::get_count(const int fish_id) const {
    // assert to make sure fish_id is a valid number (0,1,2) //
    assert(fish_id >= 0 && fish_id < 3);
    
    int tmp = fish[fish_id].size();

    return tmp; 
}

// returns number of "fed" fish of type fish_id at Site //
int Site::count_fed(const int fish_id) const {
    assert(fish_id >= 0 && fish_id < 3);
    
    int count=0;
    for(Fish_vec::const_iterator f = fish[fish_id].begin(); f != fish[fish_id].end(); f++){
        if((*f)->is_hungry()){
            count++;
        }
    }

    return count;
}

// feeds all fish of type fish_id at Site //
void Site::feed_fish(const int fish_id){ 
    assert(fish_id >= 0 && fish_id < 3);
    
    for(Fish_vec::iterator f = fish[fish_id].begin(); f != fish[fish_id].end(); f++){
        if((*f)->is_hungry()){
            (*f)->feed();
        }
    }
}

// kills & deletes all fish of type fish_id at Site //
int Site::kill_fish(const int fish_id){
    assert(fish_id >= 0 && fish_id < 3);
    
    int sum = 0;
    try {
        for(int i = (fish[fish_id].size()-1); i>=0; i--){
            del_fish(fish_id, i, 1);
            sum++;
        }
    } catch(std::exception const &err) {
        throw err;      // demonstrating throwing lower error back up to Tank function //
    }

    return sum;
}

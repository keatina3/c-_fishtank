#include <string>
#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include "fish.h"
#include "site.h"

Site::Site(){
    try {
        fish.resize(3);
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

Fish *Site::get_fish(const int fish_id, const int index) const {
    // insert out of bounds tests //
    if(index >= (int)fish[fish_id].size() || fish_id < 0 || fish_id > 2)
        throw std::range_error(__FILE__);
    
    Fish* tmp = fish[fish_id][index];
    return tmp;
}

void Site::add_fish(Fish *new_fish){
    // insert null ptr exception //

    int id = new_fish->get_id();
    try {
        fish[id].push_back(new_fish);
    } catch(std::bad_alloc const &err) {
        std::cerr << "Bad allocation adding fish" << std::endl;
        std::cerr << err.what() << std::endl;
        exit(1);
    }
}

void Site::del_fish(const int fish_id, const int index, const bool kill){
    // insert error checking for correct index & fish id
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
        std::cerr << "Error deleting fish." << std::endl;
        std::cerr << err.what() << std::endl;
        exit(1);
    }
}

int Site::get_count(const int fish_id) const {
    assert(fish_id >= 0 && fish_id < 3);
    
    int tmp = fish[fish_id].size();

    return tmp; 
}

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

void Site::feed_fish(const int fish_id){ 
    assert(fish_id >= 0 && fish_id < 3);
    
    for(Fish_vec::iterator f = fish[fish_id].begin(); f != fish[fish_id].end(); f++){
        if((*f)->is_hungry()){
            (*f)->feed();
        }
    }
}

int Site::kill_fish(const int fish_id){
    assert(fish_id >= 0 && fish_id < 3);
    
    int sum = 0;
    try {
        for(int i = (fish[fish_id].size()-1); i>=0; i--){
            del_fish(fish_id, i, 1);
            sum++;
        }
    } catch(std::exception const &err) {
        throw err;
    }

    return sum;
}

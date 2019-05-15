#include <vector>
#include "fish.h"
#include "site.h"

Site::Site(){
    fish.resize(3);
}

Site::~Site(){
    // use iterator for loop here //
    for(int i=0;i<3;i++)
        for(unsigned int j=0;j<fish[i].size();j++)
            delete fish[i][j];
}

Fish *Site::get_fish(const int fish_id, const int index) const {
    // insert out of bounds tests //

    Fish* tmp = fish[fish_id][index];
    return tmp;
}

void Site::add_fish(Fish *new_fish){
    // insert null ptr exception //

    int id = new_fish->get_id();
    fish[id].push_back(new_fish);     // test for this //
}

void Site::del_fish(const int fish_id, const int index, const bool kill){
    // insert error checking for correct index & fish id
    
    // test this also //
    if(kill)
        delete fish[fish_id][index];

    // insert error checking for succesful deletion //
    fish[fish_id].erase(fish[fish_id].begin() + index);
}

int Site::get_count(const int fish_id) const {
    int tmp = fish[fish_id].size();

    return tmp; 
}

void Site::feed_fish(const int fish_id){ 
    for(unsigned int i = fish[fish_id].size()-1; i>=0; i--)
        if(fish[fish_id][i]->is_hungry())
            fish[fish_id][i]->feed();
}

void Site::kill_fish(const int fish_id){
    for(unsigned int i = fish[fish_id].size()-1; i>=0; i--)
       del_fish(fish_id, i, 1);
}

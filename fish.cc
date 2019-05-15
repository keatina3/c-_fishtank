#include <cstdlib>
#include "fish.h"

#include <iostream>

Fish::Fish(){
    moves=0;
    hungry=true;
}

int Fish::get_id() const {
    int id = fish_id;
    return id;
}

int Fish::get_moves() const {
    int moves = this->moves;
    return moves;
}

void Fish::feed(){
    hungry = false;
}

bool Fish::is_hungry() const {
    bool hungry = this->hungry;
    return hungry;
}

Minnow::Minnow(){
    fish_id=0;
}

void Minnow::move(const int *src, int *dest){
    int dx[3];

    moves++;

    while(true){
        dx[0] = (rand()%3)-1; dx[1] = (rand()%3)-1; dx[2] = (rand()%3)-1;
        if (dx[0] != 0 || dx[1] != 0 || dx[2] != 0)
            break;
    }
    
    for(int i=0;i<3;i++)
        dest[i] = ((( src[i]+dx[i])%5 ) + 5 )%5;
}

Tuna::Tuna(){
    fish_id=1;
}

void Tuna::move(const int *src, int *dest){
    int dx[3];
    
    moves++;

    for(int i=0;i<3;i++){
        dx[i] = rand()%2 > 0 ? 1 : -1;
        dest[i] = ((( src[i]+dx[i])%5 ) + 5 )%5;
    }
}

Shark::Shark(){
    fish_id=2;
}

void Shark::move(const int *src, int *dest){
    int dx[3];
    int perp = rand()%3, len = rand()%2;

    //dx[perp] = 0;
    moves++;
    
    for(int i=0;i<3;i++){
        if(i==perp){
            dest[i] = src[i];
            continue;
        }
        
        dx[i] = rand()%2 > 0 ? 1 : -1;
        dx[i] += dx[i]*len;
        dest[i] = ((( src[i]+dx[i])%5 ) + 5 )%5;
        
        len = (len+1)%2;
    }
    
}

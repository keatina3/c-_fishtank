#include <cstdlib>
#include "fish.h"


///////////////// ABSTRACCT FISH ////////////////
// default contructor for abstract class //
Fish::Fish(){
    moves=0;
    hungry=true;
}

// returns 0,1,2 for Minnow, Tuna, Shark //
int Fish::get_id() const {
    int id = fish_id;
    return id;
}

// returns #moves since eating //
int Fish::get_moves() const {
    int moves = this->moves;
    return moves;
}

// sets huger to false //
void Fish::feed(){
    hungry = false;
    moves = 0;
}

// checks if fish has eaten since birth //
bool Fish::is_hungry() const {
    bool hungry = this->hungry;
    return hungry;
}
/////////////////////////////////////////


///////////////// MINNOW ////////////////
// derived constructor //
Minnow::Minnow(){
    fish_id=0;
}

// Move fn for Minnow. Picks random vals dx = -1,0,1 and //
// adds to current src coords //
void Minnow::move(const int *src, int *dest){
    int dx[3];      // displacement //

    moves++;
    while(true){
        dx[0] = (rand()%3)-1; dx[1] = (rand()%3)-1; dx[2] = (rand()%3)-1;
        if (dx[0] != 0 || dx[1] != 0 || dx[2] != 0)
            break;
    }
    
    for(int i=0;i<3;i++)
        dest[i] = ((( src[i]+dx[i])%5 ) + 5 )%5;
}
///////////////////////////////////////


///////////////// TUNA ////////////////

// see above //
Tuna::Tuna(){
    fish_id=1;
}

// choses random value dx -1,1 and adds //
// to src in 2 dims, other dim stays //
void Tuna::move(const int *src, int *dest){
    int dx[3];
    int stay = rand()%3;        // since planar, one dim doesn't change //

    moves++;
    for(int i=0;i<3;i++){
        if(i==stay)
            dx[i] = 0;
        else
            dx[i] = rand()%2 > 0 ? 1 : -1;
        dest[i] = ((( src[i]+dx[i])%5 ) + 5 )%5;
    }
}
////////////////////////////////////////


///////////////// SHARK ////////////////

Shark::Shark(){
    fish_id=2;
}

// adds +-1 to one dim, +-2 to one dim, +0 to last dim //
void Shark::move(const int *src, int *dest){
    int dx[3];
    int perp = rand()%3, len = rand()%2;    // dim which doesn't change, dim which changes +-1

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
///////////////////////////////////////

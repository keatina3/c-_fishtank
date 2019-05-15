#include <cstdlib>
#include <vector>
#include "fish.h"
#include "site.h"
#include "tank.h"

Tank::Tank(){
    Fish *tmp;
    int m=150, t=10, s=5;

    tot_count[0]=m; tot_count[1]= t; tot_count[2]=s;
    for(int i=0;i<m;i++){
        tmp = new Minnow();         // tests here
        tank[rand()%5][rand()%5][rand()%5].add_fish(tmp);
    }
    for(int i=0;i<t;i++){
        tmp = new Tuna();         // tests here
        tank[rand()%5][rand()%5][rand()%5].add_fish(tmp);
    }
    for(int i=0;i<m;i++){
        tmp = new Shark();         // tests here
        tank[rand()%5][rand()%5][rand()%5].add_fish(tmp);
    }
}

Tank::Tank(const int minnows, const int tuna, const int sharks){
    Fish *tmp;
    int m=minnows, t=tuna, s=sharks;

    tot_count[0]=m; tot_count[1]= t; tot_count[2]=s;
    for(int i=0;i<m;i++){
        tmp = new Minnow();         // tests here
        tank[rand()%5][rand()%5][rand()%5].add_fish(tmp);
    }
    for(int i=0;i<t;i++){
        tmp = new Tuna();           // tests here
        tank[rand()%5][rand()%5][rand()%5].add_fish(tmp);
    }
    for(int i=0;i<m;i++){
        tmp = new Shark();          // tests here
        tank[rand()%5][rand()%5][rand()%5].add_fish(tmp);
    }
}

void Tank::sweep(){
    int fish_id, p_move;
    int src[3], dest[3];

    // use proper error management here too // 
    if(tot_count[0]==0 || tot_count[1]==0 || tot_count[2]==0)
        exit(1);
    
    fish_id = rand()%3;
    while(true){
        src[0] = rand()%5; src[1] = rand()%5; src[2] = rand()%5;
        if(fish_present(src, fish_id))
                break;
    }

    ///// MOVING /////
    p_move = rand()%10;
     
    if(p_move!=0)
        move(dest, fish_id);
    else
        dest[0] = src[0]; dest[1] = src[1]; dest[2] = src[2];
}

bool Tank::fish_present(const int *site, const int fish_id) const {
    if(fish_count[fish_id][site[0]][site[1]][site[2]] > 0)
        return 1;
    else
        return 0;
}

void Tank::move(const int *site, const int fish_id){
    Site *src, *dest;
    Fish *fish_tmp;
    int count, rand_fish, dest_coords[3];

    src = &tank[site[0]][site[1]][site[2]];
    
    count = src->get_count(fish_id);

    rand_fish = rand()%count;

    fish_tmp = src->get_fish(fish_id, rand_fish);

    fish_tmp->move(site, dest_coords);

    dest = &tank[dest_coords[0]][dest_coords[1]][dest_coords[2]];

    dest->add_fish(fish_tmp);
    src->del_fish(fish_id, rand_fish, 0);
}

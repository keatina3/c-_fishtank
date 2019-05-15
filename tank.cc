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
        move(src, fish_id);
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

int Tank::check_outcomes(const int *site){

}

void Tank::minnow_breed(const int *site){
    Fish *tmp;
    
    for(int i=0;i<3;i++){
        tmp = new Minnow();
        tank[site[0]][site[1]][site[2]].add_fish(tmp);
    }
}

void Tank::tuna_breed(const int *site){
    Fish *tmp;

    tmp = new Tuna();
    tank[site[0]][site[1]][site[2]].add_fish(tmp);
}

void Tank::shark_breed(const int *site){
    Fish *tmp;
    
    tmp = new Shark();
    tank[site[0]][site[1]][site[2]].add_fish(tmp);
}

void Tank::tuna_feed(const int *site){
    Site *src;

    src = &tank[site[0]][site[1]][site[2]];

    // need other way to fix this //
    //for(int i=src->get_count(0)-1; i>=0; i--)
    //    src->del_fish(0, i, 1);
    src->kill_fish(0);

    src->feed_fish(1);
}

void Tank::shark_feed(const int *site){
    Site *src;
    int count;

    src = &tank[site[0]][site[1]][site[2]];
    count = src->get_count(1);

    src->del_fish(1, rand()%count, 1);

    src->feed_fish(2);
}

void Tank::feeding_frenzy(const int *site){
    Site *src, *nbr_site;
    int nbr[3];

    src = &tank[site[0]][site[1]][site[2]];

    // need other way to fix this //
    //for(int i=src->get_count(0)-1; i>=0; i--)
    //    src->del_fish(0, i, 1);
    src->kill_fish(0);

    for(int i=-1;i<2;i++){
        nbr[0] = ((( site[0]+i )%5) + 5 )%5;
        for(int j=-1;i<2;j++){
            nbr[1] = ((( site[1]+j )%5) + 5 )%5;
            for(int k=-1;k<2;k++){            
                nbr[2] = ((( site[2]+k )%5) + 5 )%5;
                nbr_site = &tank[nbr[0]][nbr[1]][nbr[2]];
                nbr_site->kill_fish(0);
            }
        }
    }
    
    src->feed_fish(2);
}

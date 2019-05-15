#include <cstdlib>
#include <vector>
#include "fish.h"
#include "site.h"
#include "tank.h"

#include <iostream>

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
    int fish_id, p_move, num_out;;
    int src[3], dest[3];
    void (Tank::*outcome_fns[6])(const int *);

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
        move(src, dest, fish_id);
    else
        dest[0] = src[0]; dest[1] = src[1]; dest[2] = src[2];

    num_out = check_outcomes(dest, outcome_fns);
    if(num_out)
        (this->*outcome_fns[rand()%num_out])(dest);
}

void Tank::move(const int *site, int *dest_coords, const int fish_id){
    Site *src, *dest;
    Fish *fish_tmp;
    int count, rand_fish;

    src = &tank[site[0]][site[1]][site[2]];
    
    count = src->get_count(fish_id);
    
    rand_fish = rand()%count;

    fish_tmp = src->get_fish(fish_id, rand_fish);
    
    if(fish_tmp->get_moves()==4 && (fish_id==1 || fish_id==2)){
        src->del_fish(fish_id, rand_fish, 1);
        tot_count[fish_id]--;
        return;
    }

    fish_tmp->move(site, dest_coords);

    dest = &tank[dest_coords[0]][dest_coords[1]][dest_coords[2]];

    dest->add_fish(fish_tmp);
    src->del_fish(fish_id, rand_fish, 0);
}

int Tank::check_outcomes(const int *site, void (Tank::**outcome_fns)(const int *)){
    Site *src;
    int index;

    src = &tank[site[0]][site[1]][site[2]];
    index = 0;

    if(src->get_count(0) > 1){
        outcome_fns[index] = &Tank::minnow_breed;
        index++;
    }
    if(src->count_fed(1) > 1){
        outcome_fns[index] = &Tank::tuna_breed;
        index++;
    }
    if(src->count_fed(2) > 1){
        outcome_fns[index] = &Tank::shark_breed;
        index++;
    }
    if(fish_present(site, 0) && fish_present(site, 1)){
        outcome_fns[index] = &Tank::tuna_feed;
        index++;
    }
    if(fish_present(site, 1) && fish_present(site, 2)){
        outcome_fns[index] = &Tank::shark_feed;
        index++;
    }
    if(fish_present(site,0) && fish_present(site,2)){
        outcome_fns[index] = &Tank::feeding_frenzy;
        index++;
    }

    return index;
}

bool Tank::fish_present(const int *site, const int fish_id) const {
    const Site *src;
    
    src = &tank[site[0]][site[1]][site[2]];
     
    if(src->get_count(fish_id) > 0)
        return 1;
    else
        return 0;
}

void Tank::minnow_breed(const int *site){
    Fish *tmp;
    
    std::cout << "minnow breed" << std::endl;
    
    for(int i=0;i<3;i++){
        tmp = new Minnow();
        tank[site[0]][site[1]][site[2]].add_fish(tmp);
    }

    tot_count[0] += 3;
}

void Tank::tuna_breed(const int *site){
    Fish *tmp;

    std::cout << "tuna breed" << std::endl;
    
    tmp = new Tuna();
    tank[site[0]][site[1]][site[2]].add_fish(tmp);

    tot_count[1]++;
}

void Tank::shark_breed(const int *site){
    Fish *tmp;
    
    std::cout << "Shark breed" << std::endl;
    
    tmp = new Shark();
    tank[site[0]][site[1]][site[2]].add_fish(tmp);

    tot_count[2]++;
}

void Tank::tuna_feed(const int *site){
    Site *src;

    std::cout << "Tuna feed" << std::endl;
    
    src = &tank[site[0]][site[1]][site[2]];

    tot_count[0] -= src->kill_fish(0);
    
    src->feed_fish(1);
}

void Tank::shark_feed(const int *site){
    Site *src;
    int count;

    std::cout << "Shark feed" << std::endl;
    
    src = &tank[site[0]][site[1]][site[2]];
    count = src->get_count(1);

    src->del_fish(1, rand()%count, 1);
    tot_count[1] -= 1;

    src->feed_fish(2);
}

void Tank::feeding_frenzy(const int *site){
    Site *src, *nbr_site;
    int nbr[3];
    
    std::cout << "Feeding frenzy" << std::endl;

    src = &tank[site[0]][site[1]][site[2]];
    
    //src->kill_fish(0);

    for(int i=-1;i<2;i++){
        nbr[0] = ((( site[0]+i )%5) + 5 )%5;
        for(int j=-1;j<2;j++){
            nbr[1] = ((( site[1]+j )%5) + 5 )%5;
            for(int k=-1;k<2;k++){            
                nbr[2] = ((( site[2]+k )%5) + 5 )%5;
                //std::cout << "loc = " << nbr[0] << "," << nbr[1] << "," << nbr[2] << std::endl;
                nbr_site = &tank[nbr[0]][nbr[1]][nbr[2]];
                if(fish_present(nbr, 0))
                    tot_count[0] -= nbr_site->kill_fish(0);
            }
        }
    }
    
    src->feed_fish(2);
}

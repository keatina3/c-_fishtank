#include <iostream>
#include <cstdlib>
#include <vector>
#include <getopt.h>
#include <time.h>
#include "fish.h"
#include "site.h"
#include "tank.h"

int main(int argc, char **argv){
    int count, opt;
    int m = 10000, t = 300, s = 15;
    bool verbose = false;

    srand(time(NULL));
    
    while((opt = getopt(argc, argv, "m:t:s:v")) != -1){
        switch(opt) {
            case 'm':
                m = atoi(optarg);
                break;
            case 't':
                t = atoi(optarg);
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'v':
                verbose = true;
                break;
            default:
                std::cout << "Incorrect options entered" << std::endl;
                exit(1);
        }
    }     

    Tank tank(m, t, s);    
    count = 0;

    while(true){
        std::cout << "Sweep #" << count++ << std::endl;
        std::cout << "Total count of fish: " << tank.get_count(0) << "," << tank.get_count(1) << "," << tank.get_count(2) << std::endl;
        std::cout << "====================================================" << std::endl;
        if(verbose) 
            std::cout << tank;
        tank.sweep();
    }

    return 0;
}

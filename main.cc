#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include "fish.h"
#include "site.h"
#include "tank.h"

int main(int argc, char **argv){
    Tank t(100, 10, 1);    
    srand(time(NULL));
    int count;

    count = 0;
    
    while(true){
        t.sweep();
        std::cout << "count = " << ++count << std::endl;
    }

    return 0;
}

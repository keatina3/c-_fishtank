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

    t.sweep();

    return 0;
}

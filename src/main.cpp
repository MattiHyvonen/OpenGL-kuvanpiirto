#include "glmems.h"
#include <iostream>

int main() {
    ikkuna i,j;
    
    bool run = true;
    while(run) {
        i.suorita();
        j.suorita();

        bool irun = i.tarkasta();
        bool jrun = j.tarkasta();
        
        if(irun || jrun)
            run = true;
        else
            run = false;
    }
    return 0;
}

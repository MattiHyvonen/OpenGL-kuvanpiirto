#include "glmems.h"
#include <iostream>

#include <memory> //std::shared_ptr

int main() {
    ikkuna i;
    ikkuna j;
    
    bool run = true;
    while(run) {
        if(i.tarkasta() )
            i.suorita();
        if(j.tarkasta() )
            j.suorita();
        
        if(!i.tarkasta() && !j.tarkasta() )
            run = false;
    }
    return 0;
}

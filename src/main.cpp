#include "ikkuna.h"
#include "buffer.h"
#include <iostream>

int main() {
    ikkuna i;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);
    
    buffer bv, bu;
    
    float s = 0.8;
    bv.laitaVertekseja(teeSuorakulmio(-s, -s, 2*s, 2*s));
    bu.laitaUVta(teeSuorakulmio(0, 0, 1, 1) );
    
    bool run = true;
    while(run) {
        piirra(bv);
        run = i.tarkasta();
        i.suorita();
    }

    return 0;
}

#include "ikkuna.h"
#include "buffer.h"
#include "tekstuuri.h"
#include <iostream>


class suorakulmio : public VAO {
private:
    buffer verteksiBuffer;
    buffer uvBuffer;
public:
    suorakulmio() {
        float s = 0.8;
        std::vector<glm::vec2> verteksit = teeSuorakulmio(-s, -s, 2*s, 2*s);
        std::vector<glm::vec2> UVt = teeSuorakulmio(0, 0, 1, 1);
        
        verteksiBuffer.laitaVertekseja(verteksit);
        uvBuffer.laitaUVta(UVt);

        asetaVerteksienMaara(verteksit.size() );
    }
    

    suorakulmio(const suorakulmio& toinen) : suorakulmio() {}
    
};


class suorakulmionPiirtaja : public ikkuna, public suorakulmio {};


int main() {

    suorakulmionPiirtaja S;
    
    bool run = true;
    while(run) {
        S.piirra();
        S.suorita();
        run = S.tarkasta();
    }
    
    return 0;
}

#include "piirtaja.h"

std::vector<glm::vec2> teeSuorakulmio(float x, float y, float w, float h) {
    std::vector<glm::vec2> S = {
        glm::vec2(x, y),
        glm::vec2(x+w, y),
        glm::vec2(x, y+h),
        
        glm::vec2(x+w, y),
        glm::vec2(x, y+h),
        glm::vec2(x+w, y+h)
    };
    return S;
}


suorakulmio::suorakulmio() {
    float s = 1;
    std::vector<glm::vec2> verteksit = teeSuorakulmio(-s, -s, 2*s, 2*s);
    std::vector<glm::vec2> UVt = teeSuorakulmio(0, 0, 1, 1);
    
    VAO::liita();
    verteksiBuffer.laitaVertekseja(verteksit);
    uvBuffer.laitaUVta(UVt);

    VAO::asetaVerteksienMaara(verteksit.size() );
    
    irrotaVAO();
}



kuvanPiirtaja::kuvanPiirtaja() {
    shader::asetaUniform("texture0", 0);
}
    
    
bool kuvanPiirtaja::piirra() {
    
    if(!kaytaKontekstia())
        return false;

    if(!shader::kayta() )
        return false;
    
    //piirrä VAO
    if(!suorakulmio::piirra()) {
        irrotaShader();
        return false;
    }
    
    //käännä bufferit ja tarkasta sulkupyynnöt
    if(!ikkuna::toteuta()) {
        irrotaShader();
        return false;
    }

    irrotaShader();
    return true;
}
    
    
bool kuvanPiirtaja::kaytaTekstuuria(tekstuuri& t, int paikka) {
    if(!kaytaKontekstia())
        return false;

    return t.liita(paikka);
}

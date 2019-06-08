#include "buffer.h"
#include <iostream>


bufferPerusT::bufferPerusT() {
    //Jos kontekstia ei ole, ei voida tehdä mitään => keskeytetään.
    // Tunnus on silloin HUONO_TUNNUS,
    // ja siitä tiedetään, että tätä bufferia ei luotu onnistuneesti.
    std::cout << "Luodaan buffer...\n";
    
    if(!kontekstiOnOlemassa() ) {
        std::cout << "  Kontekstia ei ole! \n";
        return;
    }
    
    glGenBuffers(1, &tunnus);
    
    std::cout << "  Luotiin buffer " << tunnus << "\n";
}


bufferPerusT::~bufferPerusT() {
    tuhoa();
}


//Kopiokonstruktori: kutsutaan sen sijaan yleistä konstruktoria
bufferPerusT::bufferPerusT(const bufferPerusT& toinen) : bufferPerusT() {
}


int bufferPerusT::haeTunnus() const {
    return tunnus;
}


void bufferPerusT::tuhoa() {
    std::cout << "Tuhotaan buffer " << tunnus << "...\n";
    if(!kontekstiOnOlemassa() ) {
        std::cout << "  Kontekstia ei ole! \n";
        return;
    }
    glDeleteBuffers(1, &tunnus);
    tunnus = HUONO_TUNNUS;
    std::cout << "  Tuhottiin, tunnus on nyt " << tunnus << "\n";    
}


buffer::buffer() {
    liita();
}


int buffer::haeDatanMaara() const {
    return datanMaara;
}


bool buffer::onHyva() const {
    if(!kontekstiOnOlemassa())
        return false;
    if(haeTunnus() == HUONO_TUNNUS)
        return false;
    
    if(glIsBuffer(haeTunnus() ) )
        return true;
    else 
        return false;
}


bool buffer::onLiitetty() const {
    if(!kontekstiOnOlemassa() )
        return false;
    if(haeTunnus() == HUONO_TUNNUS)
        return false;
    
    int liitos;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &liitos);
    
    if(liitos == haeTunnus() )
        return true;
    else
        return false;
}


bool buffer::liita() {
    if(!kontekstiOnOlemassa() )
        return false;
    if(haeTunnus() == HUONO_TUNNUS)
        return false;
    
    glBindBuffer(GL_ARRAY_BUFFER, haeTunnus() );
    
    if(onLiitetty() )
        return true;
    else
        return false;
}


bool buffer::laita(const std::vector<glm::vec2>& data, int attrib) {
    if(!liita() )
        return false;
    
    int kokoTavuina = sizeof(glm::vec2) * data.size();
    
    glBufferData(GL_ARRAY_BUFFER, kokoTavuina, &data[0], GL_STATIC_DRAW);

    glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

    datanMaara = data.size();
    
    std::cout << "Määriteltiin verteksiattribuutti " << attrib << "\n";
    std::cout << "Laitettiin " << data.size() << " * " << sizeof(glm::vec2) << " tavua\n";
    
    return true;
}


bool buffer::laitaVertekseja(const std::vector<glm::vec2>& verteksit) {
    if(!laita(verteksit, 0) )
        return false;
    return true;
}


bool buffer::laitaUVta(const std::vector<glm::vec2>& UVt) {
    if(!laita(UVt, 1) )
        return false;
    return true;
}


bool piirra(buffer& b) {
    if(!b.liita())
        return false;
    
    //Attribuutti 0 on verteksit
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, b.haeDatanMaara() );
    //std::cout << "Piirrettiin " << b.haeDatanMaara() << " verteksiä\n";
    
    glDisableVertexAttribArray(0);
    irrotaBufferit();
    return true;
}


void irrotaBufferit() {
    if(!kontekstiOnOlemassa() )
        return;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

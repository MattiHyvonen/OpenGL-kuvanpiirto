#include "buffer.h"
#include <iostream>


/* VAOperusT -luokka */


VAOperusT::VAOperusT() {
    //Jos kontekstia ei ole, ei voida tehdä mitään => keskeytetään.
    // Tunnus on silloin HUONO_TUNNUS,
    // ja siitä tiedetään, että tätä bufferia ei luotu onnistuneesti.
    std::cout << "Luodaan VAO...\n";
    
    if(!kontekstiOnOlemassa() ) {
        std::cout << "  Kontekstia ei ole! \n";
        return;
    }
    
    glGenVertexArrays(1, &tunnus);
    
    std::cout << "  Luotiin VAO " << tunnus << "\n";
}


VAOperusT::~VAOperusT() {
    tuhoa();
}


//Kopiokonstruktori: kutsutaan sen sijaan yleistä konstruktoria
VAOperusT::VAOperusT(const VAOperusT& toinen) : VAOperusT() {
}


int VAOperusT::haeTunnus() const {
    return tunnus;
}


void VAOperusT::tuhoa() {
    std::cout << "Tuhotaan VAO " << tunnus << "...\n";
    if(!kontekstiOnOlemassa() ) {
        std::cout << "  Kontekstia ei ole! \n";
        return;
    }
    glDeleteVertexArrays(1, &tunnus);
    tunnus = HUONO_TUNNUS;
    std::cout << "  Tuhottiin, tunnus on nyt " << tunnus << "\n";
}


/* VAO -luokka */


//Liitetään heti, että array tulee luoduksi.
VAO::VAO() {
    liita();
}


bool VAO::liita() {
    if(!kontekstiOnOlemassa() )
        return false;
    if(haeTunnus() == HUONO_TUNNUS)
        return false;
    
    glBindVertexArray(haeTunnus() );
    
    return true;
}


//HUOM! Ei ole varmistettu mitenkään, onko verteksejä todella laitettu bufferiin
//  tässä annettu määrä. Se on tätä luokkaa käyttävän vastuulla.
//  OpenGL kuitenkin suojautuu vääriltä datamääriltä tässä ihan hyvin.
int VAO::haeVerteksienMaara() const {
    return verteksienMaara;
}


void VAO::asetaVerteksienMaara(unsigned int N) {
    if(N > MAX_VERTEKSEJA) {
        std::cout   << "Liian monta verteksiä: " << N << "!\n"
                    << "Piirretään vain " << MAX_VERTEKSEJA << "\n";
        N = MAX_VERTEKSEJA;
    }
    verteksienMaara = N;
}


bool VAO::piirra() {
    piirraVAO(*this);
}


/* BufferPerusT -luokka */


bufferPerusT::bufferPerusT() {
    //ks. VAOperusT():n kommentti
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


/* buffer -luokka */


buffer::buffer() {
    liita();
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


bool piirraVAO(VAO& b) {
    if(!b.liita())
        return false;
    
    //Attribuutti 0 on verteksit, 1 on UV:t
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glDrawArrays(GL_TRIANGLES, 0, b.haeVerteksienMaara() );
    
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    
    irrotaBufferit();
    return true;
}


void irrotaBufferit() {
    if(!kontekstiOnOlemassa() )
        return;
    
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

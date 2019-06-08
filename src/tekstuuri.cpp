#include "tekstuuri.h"
#include <iostream>


tekstuuriPerusT::tekstuuriPerusT() {
    std::cout << "Luodaan tekstuuri...\n";
    if(!kontekstiOnOlemassa() ) {
        std::cout << "  Kontekstia ei ole! \n";
        return;
    }
    
    glGenTextures(1, &tunnus);
    
    std::cout << "  Luotiin tekstuuri " << tunnus << "\n";    
}


tekstuuriPerusT::~tekstuuriPerusT() {
    tuhoa();
}


tekstuuriPerusT::tekstuuriPerusT(const tekstuuriPerusT& toinen) : tekstuuriPerusT() {}


int tekstuuriPerusT::haeTunnus() const {
    return tunnus;
}


void tekstuuriPerusT::tuhoa() {
    std::cout << "Tuhotaan tekstuuri " << tunnus << "...\n";
    if(!kontekstiOnOlemassa() ) {
        std::cout << "  Kontekstia ei ole! \n";
        return;
    }
    glDeleteTextures(1, &tunnus);
    tunnus = HUONO_TUNNUS;
    std::cout << "  Tuhottiin, tunnus on nyt " << tunnus << "\n";    
}

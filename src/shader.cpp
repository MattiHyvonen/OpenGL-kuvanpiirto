#include "shader.h"
#include "loadShaders.h"

#include <iostream>


shaderPerusT::shaderPerusT(std::string vpolku, std::string fpolku) {
    std::cout << "Luodaan shader...\n";
    if(!kontekstiOnOlemassa() ) {
        std::cout << "  Kontekstia ei ole! \n";
        return;
    }
    
    tunnus = loadShaders(vpolku.c_str(), fpolku.c_str());

    /* Tarkasta onko hyvä:
        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(success == GL_FALSE) 
            //epäonnistui
            ...
    */
    
    std::cout << "  Luotiin shader " << tunnus << "\n";    
}


shaderPerusT::~shaderPerusT() {
    tuhoa();
}


shaderPerusT::shaderPerusT(const shaderPerusT& toinen) : shaderPerusT() {}


int shaderPerusT::haeTunnus() const {
    return tunnus;
}


void shaderPerusT::tuhoa() {
    std::cout << "Tuhotaan shader " << tunnus << "...\n";
    if(!kontekstiOnOlemassa() ) {
        std::cout << "  Kontekstia ei ole! \n";
        return;
    }

    glDeleteProgram(tunnus);
    tunnus = HUONO_TUNNUS;
    std::cout << "  Tuhottiin, tunnus on nyt " << tunnus << "\n";    
}


/* shader -luokka */


bool shader::onHyva() {     
    if(!kontekstiOnOlemassa() )
        return false;
    if(haeTunnus() == HUONO_TUNNUS)
        return false;
    
    int palaute;
    glGetProgramiv(haeTunnus(), GL_LINK_STATUS, &palaute);
    if(palaute == GL_FALSE)
        return false;
    else
        return true;
}


bool shader::kayta() {
    if(!onHyva() ) {
        std::cout << "Shader " << haeTunnus() << " on huono! Ei voi käyttää\n";
        return false;
    }
    std::cout << "Käytetään shaderia " << haeTunnus() << "\n";
    glUseProgram(haeTunnus());
    return true;
}

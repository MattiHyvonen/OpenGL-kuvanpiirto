#include "GL.h"
#include <string>

const std::string OLETUS_VPOLKU = "data/default.vertexShader";
const std::string OLETUS_FPOLKU = "data/default.fragmentShader";


int haeAktiivinenShader();


class shaderPerusT{
private:
    unsigned int tunnus = HUONO_TUNNUS;
public:
    shaderPerusT(std::string vpolku = OLETUS_VPOLKU, std::string fpolku = OLETUS_FPOLKU);
    
    ~shaderPerusT();
    
    shaderPerusT(const shaderPerusT& toinen);
    
    int haeTunnus() const;
    
    void tuhoa();    
};


class shader : public shaderPerusT{
public:
    bool onHyva();
    bool kayta();
    bool asetaUniform(std::string nimi, int arvo);
};


void irrotaShader();

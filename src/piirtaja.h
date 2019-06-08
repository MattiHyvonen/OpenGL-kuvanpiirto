#include "GL.h"

#include "ikkuna.h"
#include "buffer.h"
#include "tekstuuri.h"
#include "shader.h"

class suorakulmio : public VAO {
private:
    buffer verteksiBuffer;
    buffer uvBuffer;

public:
    //Laita buffereihin suorakulmion verteksit ja UV:t
    suorakulmio();
};


class kuvanPiirtaja : public ikkuna, public shader, public suorakulmio {
public:
    //aseta tekstuurin nimi univormuun
    kuvanPiirtaja();
    
    //Piirrä tekstuurit ruudulle, päivitä ja tarkasta sulkupyynnöt.
    bool piirra();
    
    //Käytä tekstuuria annetussa tekstuuripaikassa.
    //  Tätä funktiota käyttämällä varmistetaan, että tekstuurit tulevat tähän kontekstiin.
    bool kaytaTekstuuria(tekstuuri& t, int paikka=0);
};

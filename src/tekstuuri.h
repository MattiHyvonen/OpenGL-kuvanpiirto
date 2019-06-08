#include "GL.h"
#include <string>

/* Tekstuuriperustyyppi: Hallitsee tekstuuria tunnuksen avulla */
class tekstuuriPerusT {
    unsigned int tunnus = HUONO_TUNNUS;
public:
    tekstuuriPerusT();
    
    ~tekstuuriPerusT();
    
    tekstuuriPerusT(const tekstuuriPerusT& toinen);
    
    unsigned int haeTunnus() const;
    
    void tuhoa();
};


class tekstuuri : public tekstuuriPerusT {
public:
    tekstuuri();
    tekstuuri(std::string kuvatiedosto);
    
    bool liita(int tekstuuripaikka = 0);

    bool asetaPikselit( int leveys, 
                        int korkeus, 
                        unsigned char* pikselit, 
                        int kanavia=3,
                        GLenum tyyppi = GL_UNSIGNED_BYTE
                      );

    bool asetaPikselit( int leveys, 
                        int korkeus, 
                        std::vector<unsigned char> pikselit,
                        int kanavia=3,
                        GLenum tyyppi = GL_UNSIGNED_BYTE
                      );
    
    bool asetaTestikuvioksi();
    
    bool lataa(std::string kuvatiedosto);
};

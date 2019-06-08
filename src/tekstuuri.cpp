#include "tekstuuri.h"
#include "stb_image.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>


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


unsigned int tekstuuriPerusT::haeTunnus() const {
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


/* tekstuuri -luokka */


tekstuuri::tekstuuri() {
    liita();
}


tekstuuri::tekstuuri(std::string kuvatiedosto) {
    lataa(kuvatiedosto);
}


bool tekstuuri::liita(int tekstuuripaikka) {
    if(!kontekstiOnOlemassa() ) {
        std::cout << "Kontekstia ei ole!\n";
        return false;
    }
    
    if(tekstuuripaikka < 0 || tekstuuripaikka > 15) {
        std::cout << "Huono tekstuuripaikka: " << tekstuuripaikka << "\n";
        return false;
    }
    
    if(haeTunnus() == HUONO_TUNNUS)
        return false;
    
    //TODO: tarkistetaan ehkä vielä jotain

    glActiveTexture(GL_TEXTURE0 + tekstuuripaikka);
    glBindTexture(GL_TEXTURE_2D, haeTunnus() );
    return true;
}


bool tekstuuri::asetaPikselit(  int leveys, 
                                int korkeus, 
                                unsigned char* pikselit, 
                                int kanavia,
                                GLenum tyyppi
                             ) {
    
    GLenum muoto;
    switch(kanavia) {
        case 4:
            muoto = GL_RGBA;
            break;
        default:
            std::cout << "Huono määrä kanavia: " << kanavia << "! Käytetään 3 kanavaa\n";
        case 3:
            muoto = GL_RGB;
            break;
        case 2:
            muoto = GL_RG;
            break;
        case 1:
            muoto = GL_RED;
    }
    
    if(!liita())
        return false;

    glTexImage2D(   GL_TEXTURE_2D,
                    0,
                    GL_RGBA32F,
                    leveys,
                    korkeus,
                    0,
                    muoto,
                    tyyppi,
                    pikselit
                );
    
    //Reuna-asetukset ensin vaaka- ja sitten pystysuunnalle
    // Vaihtoehdot: GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    
    //Interpolointiasetukset ensin pienennykselle ja sitten suurennukselle
    // Vaihtoehdot: GL_LINEAR, GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    return true;
}


bool tekstuuri::asetaPikselit(  int leveys, 
                                int korkeus, 
                                std::vector<unsigned char> pikselit, 
                                int kanavia,
                                GLenum tyyppi
                             ) {
    
    GLenum muoto;
    switch(kanavia) {
        case 4:
            muoto = GL_RGBA;
            break;
        default:
            std::cout << "Huono määrä kanavia: " << kanavia << "! Käytetään 3 kanavaa\n";
        case 3:
            muoto = GL_RGB;
            break;
        case 2:
            muoto = GL_RG;
            break;
        case 1:
            muoto = GL_RED;
    }
    
    if(!liita())
        return false;

    glTexImage2D(   GL_TEXTURE_2D,
                    0,
                    GL_RGBA32F,
                    leveys,
                    korkeus,
                    0,
                    muoto,
                    tyyppi,
                    &pikselit[0]
                );
    
    //Reuna-asetukset ensin vaaka- ja sitten pystysuunnalle
    // Vaihtoehdot: GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    
    //Interpolointiasetukset ensin pienennykselle ja sitten suurennukselle
    // Vaihtoehdot: GL_LINEAR, GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    return true;
}


bool tekstuuri::asetaTestikuvioksi() {
    int channels = 3;
    int w = 512;
    int h = 512;
    long long int size = w * h * channels;
    std::vector<float> pixels(size);
    
    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            float f_y = (float)y;
            float f_x = (float)x;
            long long int i = (long long int)y * w * channels + (long long int)x * channels;

            pixels[i] = f_x / w;
            pixels[i+1] = f_y / h;
            pixels[i+2] = 0.5;
        }
    }
    asetaPikselit(w, h, (unsigned char*)&pixels[0], channels, GL_FLOAT);
}


bool tekstuuri::lataa(std::string kuvatiedosto) {
    std::cout << "Ladataan kuva " << kuvatiedosto << "\n";
    int leveys, korkeus, kanavia;
    
    if(!liita())
        return false;
    
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(    kuvatiedosto.c_str(),
                                            &leveys,
                                            &korkeus,
                                            &kanavia,
                                            0
                                        );

    if(data == NULL) {
        std::cout << "Kuvaa ei voitu ladata!\n";
        return false;
    }
    else {
        std::cout   << "  Ladattiin kuva: " 
                    << leveys << " x " 
                    << korkeus << ", " 
                    << kanavia << " kanavaa\n";
    }

    std::vector<unsigned char> pikselit(data, data + leveys*korkeus*kanavia);
    stbi_image_free(data);

    //TODO: pitäisikö tarkistaa jotain?
    //TODO: 16-bittiset kuvat 
    bool palaute = asetaPikselit(leveys, korkeus, pikselit, kanavia, GL_UNSIGNED_BYTE);
    
    return true;
}

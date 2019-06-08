#include "ikkuna.h"

#include <iostream>


/* ikkunaPerusT -luokka: */

GLFWwindow* ikkunaPerusT::osoite() {
    return ikkuna_p;
}


ikkunaPerusT::ikkunaPerusT() {
    //Jos GLFW:tä ei ole vielä alustettu, alusta se. Jos ei onnistu, ei jatketa.
    // Ikkuna_p jää silloin NULLiksi, ja siitä tiedetään että tämä ikkuna on huono.
    std::cout << "Luodaan ikkuna...\n";
    if(!glfwInit())
        return;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    ikkuna_p = glfwCreateWindow(640, 512, "glmems", NULL, NULL);
    
    if(osoite() == NULL)
        return;
    
    glfwMakeContextCurrent(osoite());
    
    // "Initialize the extension entry points." (glewin dokumentaatiosta)
    glewExperimental = GL_TRUE;
    GLenum palaute = glewInit();
    if(palaute != GLEW_OK)
        return;
    
    if(osoite() != NULL)
        std::cout << "Ikkuna " << osoite() << " luotiin onnistuneesti\n";
}


ikkunaPerusT::~ikkunaPerusT() {
    sulje();
}


// Kutsu yleistä konstruktoria kopiokonsturktorin sijaan
ikkunaPerusT::ikkunaPerusT(const ikkunaPerusT& j) : ikkunaPerusT() {
}


void ikkunaPerusT::sulje() {
    if(osoite() != NULL) {
        glfwDestroyWindow(osoite());
        std::cout << "Tuhottiin ikkuna " << osoite() << "\n";
        ikkuna_p = NULL;
    }
    else {
        std::cout << "Ikkunaa ei voitu tuhota: Se on NULL" << "\n";
    }    
}


const GLFWwindow* const ikkunaPerusT::osoite() const {
    return ikkuna_p;
}


bool ikkunaPerusT::kontekstiOnKaytossa() const {
    if(osoite() == NULL)
        return false;
    if(glfwGetCurrentContext() == osoite())
        return true;
    else
        return false;
}


/* ikkuna -luokka: */


ikkuna::ikkuna() {
    //Rajoita päivitystiheyttä
    //glfwSwapInterval(1);

    //Hae ikkunan koko ja aseta piirtoalue sen mukaan
    int leveys, korkeus;
    glfwGetFramebufferSize(osoite(), &leveys, &korkeus);
    glViewport(0,0,leveys,korkeus);
    
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);    
}


bool ikkuna::kaytaKontekstia() {
    //Ota tämä konteksti käyttöön, jos se ei ole tällä hetkellä käytössä
    if(!kontekstiOnKaytossa() ) {
        if(osoite() != NULL)
            glfwMakeContextCurrent(osoite());
        else
            return false;
    }

    if(kontekstiOnKaytossa() )
        return true;
    else
        return false;
}


bool ikkuna::toteuta() {
    if(!kaytaKontekstia() )
        return false;
    
    //Päivitä puskurit
    glfwSwapBuffers(osoite() );
    
    //Katso eventit. Tulkitse ESCin painaminen sulkemispyyntönä.
    glfwPollEvents();
    if(glfwGetKey(osoite(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(osoite(), true);

    //Palauta false, jos halutaan sulkea.
    if(glfwWindowShouldClose(osoite()) ) {
        std::cout << "Käyttäjä sulki ikkunan\n";
        return false;
    }
    
    return true;
}


bool ikkuna::tarkasta() {
    if(!kaytaKontekstia() )
        return false;
    
    //Palauta false, jos ESCiä on painettu tai ikkuna on suljettu.
    if(glfwWindowShouldClose(osoite()) ) {
        std::cout << "Käyttäjä sulki ikkunan\n";
        return false;
    }
    
    return true;
}


#include "glmems.h"
/* Ikkunaperustyyppi:
 *  Sisältää GLFW-ikkunan osoitteen, pystyy luomaan ja tuhoamaan sen.
 *  Luodessa alustetaan GLFW ja GLEW, jos niitä ei ole vielä alustettu.
 *  Luodessa luodaan ikkunaan GL-konteksti.
 *  Ikkuna suljetaan, kun olio tuhoutuu.
 *  Kopiointi: Kopio on uusi, tyhjä ikkuna. Jos halutaan esim. antaa ikkuna funktioargumenttina,
 *  käytetään viitettä.
 */
class ikkunaPerusT{
private:    
    GLFWwindow* ikkuna_p = NULL;

protected:
    //Palauta osoite
    // Tämä luokka ja perilliset saavat käyttää ei-const-versiota, koska
    // GLFW-funktiot tarvitsevat sitä.
    GLFWwindow* osoite();
    
public:
    //Luo uusi GLFW-ikkuna ja GL-konteksti. 
    //Alusta GLFW ja GLEW tarvittaessa. (Eli aja glfwInit() ja glewInit() )
    ikkunaPerusT();
    
    //Tuhoa GLFW-ikkuna.
    ~ikkunaPerusT();
    
    //Kopiokonstruktori
    // Kopioidessa luodaan uusi ikkuna
    ikkunaPerusT(const ikkunaPerusT& j);
    
    //sulje ikkuna
    void sulje();
    
    //Palauta osoite, const-versio
    const GLFWwindow* const osoite() const;
    
    //Tarkista onko tämän ikkunan konteksti tällä hetkellä käytössä oleva konteksti.
    bool kontekstiOnKaytossa() const;
};


/* Ikkuna joka sisältää GL-kontekstin.
 * Hallitsee päivitystä ja sulkemistoimintoa */
class ikkuna : public ikkunaPerusT{
public:
    
    //Rajoita päivitystiheyttä, aseta piirtoalue, tyhjennä
    ikkuna();
    
    //Ota tämä konteksti käyttöön => tulevat GL-operaatiot toimivat tässä kontekstissa.
    bool kaytaKontekstia();
    
    //Päivitä puskurit ja sulkemispyynnöt.
    bool suorita();

    //Palauta true, jos ikkuna on käynnissä.
    // Sulje jos halutaan sulkea.
    bool tarkasta();
};


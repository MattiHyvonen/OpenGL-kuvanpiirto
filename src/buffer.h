#include "GL.h"


//Kuinka monta verteksiä voidaan enintään piirtää kerralla
const int MAX_VERTEKSEJA = 1000000;


/* Vertex Array Object -perustyyppi
 *   eli verteksitietokenttäolioperustyyppi.
 *   Hallitsee VAO:a tunnuksen avulla. */
class VAOperusT{
private:
    unsigned int tunnus = HUONO_TUNNUS;
    
public:
    VAOperusT();
    
    ~VAOperusT();
    
    //Kopioitaessa luodaan kopion sijaan uusi olio käyttäen yleistä konstruktoria.
    VAOperusT(const VAOperusT& toinen);

    int haeTunnus() const;

    void tuhoa();
};


/* Vertex Array Object
 * Sisältää VAO:n ja pystyy liittämään sen. */
class VAO : public VAOperusT {
private:
    unsigned int verteksienMaara = 0;
    
public:
    VAO();
    bool liita();
    
    int haeVerteksienMaara() const;
    void asetaVerteksienMaara(unsigned int N);
    bool piirra();
};


/* Buffer-perustyyppi: Hallitsee verteksibufferia tunnuksen avulla. */
class bufferPerusT{ 
private:
    unsigned int tunnus = HUONO_TUNNUS;

public:
    bufferPerusT();
    
    ~bufferPerusT();
    
    //Kopioitaessa luodaan kopion sijaan uusi buffer.
    bufferPerusT(const bufferPerusT& toinen);

    int haeTunnus() const;
    
    void tuhoa();
};


/* Verteksibuffer-olio
 *  Sisältää verteksibufferin.
 *  Pystyy liittämään verteksibufferin ja laittamaan sinne dataa.
 */
class buffer : public bufferPerusT {
private:
public:
    
    //Liitä ja määrittele attribuutit
    buffer();
    
    //Palauta true jos buffer on olemassa (glIsBuffer() )
    bool onHyva() const;
    
    //Palauta true, jos tämä buffer on liitetty ARRAY_BUFFER:iin.
    bool onLiitetty() const;
    
    //HUOM: seuraavien funktioidenkin olisi mahdollista olla const, 
    // mutta koska ne tekevät toimituksia olion edustamalle datalle, 
    // on ne määritelty ei-consteiksi.

    //Liitä tämä buffer ARRAY_BUFFER:iin (glBindBuffer() ).
    bool liita();

    //Määrittele verteksiattribuutti attrib ja laita dataa bufferiin.
    bool laita(const std::vector<glm::vec2>& data, int attrib = 0);

    //Määrittele verteksiattribuutti 0 ja laita verteksit bufferiin.
    // Tallenna verteksien määrä, jota käytetään piirtäessä.
    bool laitaVertekseja(const std::vector<glm::vec2>& verteksit);
    
    //Määrittele verteksiattribuutti 1 ja laita UVt bufferiin.
    bool laitaUVta(const std::vector<glm::vec2>& UVt);    
};


//Irrota ARRAY_BUFFER:in liitokset
void irrotaBuffer();
void irrotaVAO();


//Piirrä annettu Vertex Array -olio kolmioina
bool piirraVAO(VAO& b);

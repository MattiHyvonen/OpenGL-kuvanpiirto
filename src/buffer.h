#include "glmems.h"
/* Buffer-perustyyppi: Hallitsee verteksibufferia tunnuksen avulla. */
class bufferPerusT{ 
private:
    unsigned int tunnus = HUONO_TUNNUS;

public:
    //Luo buffer.
    bufferPerusT();
    
    //Tuhoa buffer.
    ~bufferPerusT();
    
    //Kopioitaessa luodaan kopion sijaan uusi buffer.
    bufferPerusT(const bufferPerusT& toinen);

    int haeTunnus() const;
    
    void tuhoa();
    
};


/* Verteksibuffer-olio */
class buffer : public bufferPerusT {
private:
    int datanMaara = 0;
    
public:
    
    //Liitä ja määrittele attribuutit
    buffer();
    
    //Datan (l. verteksien) määrää käytetään piirrossa
    int haeDatanMaara() const;
    
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
void irrotaBufferit();


//Piirrä annettu buffer-olio kolmioina
//TODO: VAO
bool piirra(buffer& b);

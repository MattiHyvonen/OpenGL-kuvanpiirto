#include "glmems.h"

class tekstuuriPerusT {
    unsigned int tunnus = HUONO_TUNNUS;
public:
    tekstuuriPerusT();
    
    ~tekstuuriPerusT();
    
    tekstuuriPerusT(const tekstuuriPerusT& toinen);
    
    int haeTunnus() const;
    
    void tuhoa();
};

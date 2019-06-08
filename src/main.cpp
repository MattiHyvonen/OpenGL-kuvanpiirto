#include "piirtaja.h"
#include <iostream>
#include <time.h>


int main() {

    kuvanPiirtaja P;
    tekstuuri t("data/tux.jpg");
    P.kaytaTekstuuria(t, 0);
    
    while(P.piirra())
        ;    
    return 0;
}

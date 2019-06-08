#include "GL.h"


void lopeta() {
    glfwTerminate();
}


bool kontekstiOnOlemassa() {
    if(glfwGetCurrentContext() == NULL)
        return false;
    else
        return true;
}

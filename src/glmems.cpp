#include "glmems.h"


void lopeta() {
    glfwTerminate();
}


bool kontekstiOnOlemassa() {
    if(glfwGetCurrentContext() == NULL)
        return false;
    else
        return true;
}


std::vector<glm::vec2> teeSuorakulmio(float x, float y, float w, float h) {
    std::vector<glm::vec2> S = {
        glm::vec2(x, y),
        glm::vec2(x+w, y),
        glm::vec2(x, y+h),
        
        glm::vec2(x+w, y),
        glm::vec2(x, y+h),
        glm::vec2(x+w, y+h)
    };
    return S;
}

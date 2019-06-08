#pragma once
#include <GL/glew.h> //glewInit
#include <GLFW/glfw3.h> //GLFWwindow
#include <vector>
#include <glm/vec2.hpp>

const int HUONO_TUNNUS = 0;


/* Lopeta GLFW-toiminnot ja sulje kaikki ikkunat*/
void lopeta();


//Palauta true jos on käytössä joku käyttökelpoinen konteksti.
bool kontekstiOnOlemassa();



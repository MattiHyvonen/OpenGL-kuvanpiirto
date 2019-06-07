SRC = src/glmems.cpp \
src/main.cpp

CFLAGS = -std=c++17
LFLAGS = -lGLEW -lGL -lglfw

EXECUTABLE = glmems

all:
	g++ $(SRC) $(CFLAGS) $(LFLAGS) -o $(EXECUTABLE)

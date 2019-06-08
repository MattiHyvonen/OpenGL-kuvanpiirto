SRC = src/glmems.cpp \
src/ikkuna.cpp \
src/buffer.cpp \
src/tekstuuri.cpp \
src/main.cpp

CFLAGS = -std=c++17
LFLAGS = -lGLEW -lGL -lglfw

EXECUTABLE = glmems

all:
	g++ $(SRC) $(CFLAGS) $(LFLAGS) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)

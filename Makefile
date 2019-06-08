SRC = src/stbImage.cpp \
src/GL.cpp \
src/ikkuna.cpp \
src/buffer.cpp \
src/tekstuuri.cpp \
src/shader.cpp \
src/piirtaja.cpp \
src/main.cpp

CFLAGS = -std=c++17
LFLAGS = -lGLEW -lGL -lglfw

EXECUTABLE = kuvanpiirto

all:
	g++ $(SRC) $(CFLAGS) $(LFLAGS) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)

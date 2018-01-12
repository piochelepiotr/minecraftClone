TARGET=main
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system -lglut -lGL -lGLU -lGLEW -lglfw
INCLUDE_PATH=src
CPPFLAGS=-Wall -Wextra -I $(INCLUDE_PATH)

OBJS=src/renderEngine/displayManager.o \
	 src/mainLoop.o \
	 src/models/rawModel.o \
	 src/renderEngine/loader.o \
	 src/renderEngine/renderer.o \
	 src/shaders/shaderProgram.o \
	 src/shaders/staticShader.o \
	 src/textures/modelTexture.o \
	 src/models/texturedModel.o \
	 src/toolbox/maths.o \
	 src/entities/Entity.o

all: $(TARGET)

$(TARGET) : $(OBJS)
	g++ $^ $(LDLIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
	rm -rf *.o

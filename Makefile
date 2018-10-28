MACOS=1
TARGET=main
INCLUDE_PATHS =
LIBRARY_PATHS =
ifeq ($(MACOS),1)
	INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include
	LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib
endif
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system -framework OpenGL -lGLEW -lglfw
INCLUDE_PATH=src
CPPFLAGS=-Wall -Wextra -I $(INCLUDE_PATH) $(INCLUDE_PATHS) $(LIBRARY_PATHS) -std=c++11 -DGLM_ENABLE_EXPERIMENTAL

OBJS=src/renderEngine/displayManager.o \
	 src/mainLoop.o \
	 src/models/rawModel.o \
	 src/renderEngine/loader.o \
	 src/renderEngine/renderer.o \
	 src/shaders/shaderProgram.o \
	 src/shaders/staticShader.o \
         src/shaders/guishader.o \
         src/textures/modelTexture.o \
	 src/models/texturedModel.o \
	 src/toolbox/maths.o \
         src/toolbox/p.o \
         src/toolbox/vertex.o \
         src/toolbox/perlinnoise.o \
         src/toolbox/mousepicker.o \
         src/toolbox/hash.o \
         src/entities/Entity.o \
         src/entities/camera.o \
         src/entities/light.o \
         src/entities/player.o \
         src/renderEngine/objloader.o \
         src/renderEngine/masterrenderer.o \
         src/renderEngine/terrainrenderer.o \
         src/shaders/terrainshader.o \
         src/world/world.o \
         src/world/chunk.o \
         src/world/block.o \
         src/terrain/terrain.o \
         src/guis/guirenderer.o \
         src/guis/guitexture.o \
         src/game/gameState.o \
         src/game/game.o

all: $(TARGET)

$(TARGET) : $(OBJS)
	g++ $^ $(LDLIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)

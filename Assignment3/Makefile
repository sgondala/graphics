CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw3 -lXxf86vm -lX11 -lpthread -lXrandr -lXinerama -lXi -lXcursor
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) -ldl
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=07_hierarchical_modelling
SRCS=07_hierarchical_modelling.cpp gl_framework.cpp shader_util.cpp hierarchy_node.cpp
INCLUDES=gl_framework.hpp shader_util.hpp 07_hierarchical_modelling.hpp hierarchy_node.hpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)

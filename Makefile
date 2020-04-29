CC=g++
CFLAGS=-c -Wall -I./Engine -fpermissive -fopenmp
LDFLAGS=-L./Engine -lengineGlut  -fopenmp
SOURCES=main.cpp Point2D.cpp Matrix.cpp Mathematics.cpp Render.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mandelbrot

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS)

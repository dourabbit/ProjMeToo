
XX = g++
CFLAGS =  -Wall -O -Wno-deprecated `sdl-config --cflags --libs` -fopenmp
LIB = -L ./lib/
INC = -I ./SDL
TARGET = ./MeToo


%.o:%.cpp
	$(XX) $(CFLAGS) $(LIB) $(INC) -c $< -o $@ -lSDL 

SOURCES = $(wildcard *.c *.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))

$(TARGET) : $(OBJS)
	$(XX) $(OBJS) -o $(TARGET) $(LIB) -lSDL -fopenmp
	chmod a+x $(TARGET)

clean:	
	rm -rf *.o MeToo

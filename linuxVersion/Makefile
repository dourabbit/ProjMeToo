
XX = g++
CFLAGS =  -Wall -O -fopenmp
LIB = -L /Library/Frameworks/SDL.framework
INC = -I /Library/Frameworks/SDL.framework/Headers
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

DIR=./src  
BIN=$(DIR)bin/  
INCLUDE=  
SRC=$(wildcard *.cpp *.c)  
OBJECTS=$(patsubst %.cpp, $(DIR)%.o,$(SRC))  
  
target=test  
CC=g++  
$(target):$(SRC)  
	-mkdir $(BIN) -p  
	$(info $(SRC))  
	$(CC)  $(SRC) $(INCLUDE) -o $(BIN)$@  
	-$(BIN)$@  
clean:  
	-rm -fr $(DIR)  
src=$(wildcard *.c ./src/*.c ./src/Cam/*.c)
dir=$(notdir $(src))
obj=$(patsubst %.c,%.o,$(dir) )

all:
	@echo $(src)
	@echo $(dir)
	@echo $(obj)
	@echo "end"
DIR_SRC := $(shell pwd)
DIR_LINK := /home/jiesiny/ffmpeg_build
CC := gcc
CFLAGS += -Os -I$(DIR_LINK)/include
LINKLIBS = -lavcodec -lavutil -lavformat -lswscale

TARGET = simple_sdl
OBJS = simple_sdl.o
.PHONY: all install
all: install
install: $(TARGET)

$(TARGET): %: %.o
	@echo -e "\033[32minstall $@ \033[0m"
	$(CC) -o $@ $^ -lSDLmain -lSDL -L$(DIR_LINK)/lib $(LINKLIBS)

%.o: %.c
	@echo -e "\033[32mcompile $@ \033[0m"
	$(CC) $(CFLAGS) -c $^ -o $@
install:
	@if [ -e $(DIR_LINK)/lib/libavcodec.a ]; then \
		mkdir -p $(DIR_SRC)/sdlbin; \
		for i in "$(TARGET)"; \
		do mv $$i $(DIR_SRC)/sdlbin; done \
	fi
clean:
	rm -rf *.o
	rm -rf $(TARGET)
	rm -rf $(DIR_SRC)/sdlbin

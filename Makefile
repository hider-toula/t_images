C_FLAGS = -g -Wall

all: guimpe_basic

image.o : image.c
	gcc $(C_FLAGS) -c image.c

pgm_image.o : pgm_image.c
	gcc $(C_FLAGS) -c pgm_image.c

trans_image.o : trans_image.c
	gcc $(C_FLAGS) -c trans_image.c

noyau.o : noyau.c
	gcc $(C_FLAGS) -c noyau.c

pile_image_basic.o : pile_image_basic.c pile_image.h
	gcc $(C_FLAGS) -c pile_image_basic.c `pkg-config --cflags gtk+-2.0`

guimpe_callback.o : guimpe_callback.c
	gcc $(C_FLAGS) -c guimpe_callback.c `pkg-config --cflags gtk+-2.0`

guimpe.o : guimpe.c
	gcc $(C_FLAGS) -c guimpe.c `pkg-config --cflags gtk+-2.0`

guimpe_basic	: guimpe.o guimpe_callback.o image.o pgm_image.o trans_image.o noyau.o pile_image_basic.o
	gcc $(C_FLAGS) -o guimpe_basic guimpe.o guimpe_callback.o image.o pgm_image.o trans_image.o noyau.o pile_image_basic.o `pkg-config --libs gtk+-2.0`

clean	:
	rm -f *.o guimpe_basic

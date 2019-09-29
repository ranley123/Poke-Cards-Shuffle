LFLAGS = -Wall -Wextra
all: faro_shuffle

faro_shuffle: faro_shuffle.c shuffle_functions.c shuffle.h print_faro_val.h node.h node_imple.c
	gcc ${LFLAGS} -o faro_shuffle -std=c99 -ggdb3 shuffle_functions.c faro_shuffle.c node_imple.c 
clean:
	rm *.o faro_shuffle


LFLAGS = -Wall -Wextra
all: extension mix_shuffle

extension: extension.c shuffle_functions.c shuffle.h print_faro_val.h node.h node_imple.c
	clang ${LFLAGS} -o extension extension.c node_imple.c shuffle_functions.c
mix_shuffle: mix_shuffle.c shuffle_functions.c shuffle.h node.h node_imple.c
	clang ${LFLAGS} -o mix_shuffle mix_shuffle.c shuffle_functions.c node_imple.c
clean:
	rm *.o faro_shuffle extension mix_shuffle

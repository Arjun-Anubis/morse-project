#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


#define TIME_FACTOR 100000
#define MASK_COUNT 0b00000111
#define GENERAL_MASK 0b0000001

char arr_init( int fd, char * arr ) {
	char first_char;
	
	read( fd, &first_char, 1 );
	printf( "The length was %ld\n", read( fd, arr, 1024 ) );
	return first_char;

}

int morse( char c, char * arr, char first_char, void (*func) (int, int, int)  ) {
	int offset = c - first_char;
	char code = arr[ offset ];

	int bit_count = code & MASK_COUNT;

	printf( "The bit count is %d and the code is %x\n", bit_count, code );

	code >>= 3;

	for ( ; bit_count; bit_count-- ) {
		printf( "Beep for %d seconds\n", code & GENERAL_MASK );
		func( 2, ( (code & GENERAL_MASK) + 1 ) * TIME_FACTOR, TIME_FACTOR/2 );
		code >>= 1;
	}
}

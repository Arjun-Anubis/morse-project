#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "morse.h"
#include "gpio.h"

char code_arr[1024];
int main() {
	int fd;
	char c;
	open_pin( 2 );
	set_out( 2 );
	void (*send_pulse)(int, int, int) = &pulse;

	if ( (fd = open( "morse", O_RDONLY ))  > 0 ) {
		char first_char;
		first_char = arr_init(fd, code_arr);
		printf( "First char is %c\n", first_char );
		while ( 1 ) {
			c = getchar();
			if ( c == EOF ) break;
			morse( c, code_arr, first_char, send_pulse );
			printf( "\n" );
			
		}

	}
	else {
		printf( "Error opening file\n" );
	}
}

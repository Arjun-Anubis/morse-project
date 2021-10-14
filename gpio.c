#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define IN "in"
#define OUT "out"
#define HIGH 1
#define LOW 0
#define GPIO_PATH "/sys/class/gpio/gpio"
#define EXPORT_PATH "/sys/class/gpio/export"
#define UNEXPORT_PATH "/sys/class/gpio/unexport"


char mybuffer[1024];

int open_pin( int pin ) { int fd;
	const char pin_no = pin + '0';
	
	printf( "GPIO : %c\n", pin_no );

	if ( ( fd = open( EXPORT_PATH , O_WRONLY ) )  < 0 )  {
		printf("open failed\n");
		return -1;
	} else {
		if ( write( fd, &pin_no, 1 ) ) {
			printf("Opened pin %d\n", pin);
			close( fd );
			return 1;
		}
		else {
			return -1;
		}
	}
}

int close_pin( int pin ) { 
	int fd;
	const char pin_no = pin + '0';

	if ( ( fd = open( UNEXPORT_PATH , O_WRONLY ) )  < 0 )  {
		printf( "open failed\n" ); return -1;
	} else {
		if ( write( fd, &pin_no, 1 ) ) {
			printf( "Closed pin %d\n", pin);
			close( fd );
			return 1;
		}
		else {
			return -1;
		}
	}
}

int raise_high( int pin ) {
	int fd;
	const char pin_no = pin + '0';
	sprintf( mybuffer, "%s%c%s", GPIO_PATH, pin_no, "/value"  );

	if ( ( fd = open( mybuffer, O_WRONLY ) )  < 0 ) {
		printf("open failed\n");
		return -1;
	}
	else {
		if ( write( fd, "1", 1 ) ) {
			
			close( fd );
			return 1;
		}
		else {
			return -1;
		}
	}
}

int raise_low( int pin ) {
	int fd;
	const char pin_no = pin + '0';
	sprintf( mybuffer, "%s%c%s", GPIO_PATH, pin_no, "/value" );

	if ( ( fd = open( mybuffer, O_WRONLY ) )  < 0 ) {
		return -1;
	}
	else {
		if ( write( fd, "0", 1 ) ) {
			close( fd );
			return 1;
		}
		else {
			return -1;
		}
	}
}
 
int set_inp( int pin ) {
	int fd;
	const char pin_no = pin + '0';
	sprintf( mybuffer, "%s%c%s", GPIO_PATH, pin_no , "/direction" );

	if ( ( fd = open( mybuffer, O_WRONLY ) )  < 0 ) 
		return -1;
	else {
		if ( write( fd, "in", 1 ) ) {
			close( fd );
			return 1;
		}
		else {
			return -1;
		}
	}
}
 
int set_out( int pin ) {
	int fd;
	const char pin_no = pin + '0';
	sprintf( mybuffer, "%s%c%s", GPIO_PATH, pin_no , "/direction" );

	if ( ( fd = open( mybuffer, O_WRONLY ) )  < 0 ) 
		return -1;
	else {
		if ( write( fd, "out", 1 ) ) {
			close( fd );
			return 1;
		}
		else {
			return -1;
		}
	}
}
int read_pin( int pin ) {
	int fd;
	char value;
	const char pin_no = pin + '0';
	sprintf( mybuffer, "%s%c%s", GPIO_PATH, pin_no , "/value" );
	
	
	if ( ( fd = open( mybuffer, O_WRONLY ) )  < 0 ) 
		return -1;
	else {
		read( fd, &value, 1 );
	}
	

	if ( value == '1' ) {
		return 1;
	}
	else if ( value == '0' ) {
		return 0;
	}
}
		
void pulse( int pin, int duration, int time_after ) {
	printf( "GPIO : Pulsing...\n" );
	printf ( "\a" );
	raise_high( pin );
	usleep( duration );
	raise_low( pin );
	usleep( time_after );
}

#include <errno.h>
#include <wiringSerial.h>
#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
	int fd;
	int secs, mics;

	if (gpioInitialise() < 0) return 1;
	gpioTime(PI_TIME_ABSOLUTE, &secs, &mics);


	if ((fd = serialOpen ("/dev/rfcomm0", 9600))<0)
	{
	fprintf(stderr, "unable to open serial device");
	return 1;
	}

	if (wiringPiSetup () == -1)
	{
	fprintf(stdout, "Unable to start WiringPi: %s\n", strerror (errno));
	return 1;
	}

	//serialPutchar(fd, 'e');
	//serialPutchar(fd, 'n');
	//serialPutchar(fd, 'd');
	serialPrintf(fd, "%d.%06d", secs, mics);
	fprintf(stdout, "%d\n", serialGetchar(fd));
	//serialClose(fd);
	return 0;
	}

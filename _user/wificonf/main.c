#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


ssize_t write_cstr(int fd, const char *cstr)
{
	return write(fd, cstr, strlen(cstr));
}


int main (int argc, char *argv[])
{
	int fd = -1;
	ssize_t res = 0;
	char *buf = NULL;

	do {
		fd = open("/dev/wifi", O_RDWR);
		if (fd < 0) {
			perror("open");
			res = errno;
			break;
		}

		res = write_cstr(fd, "timeout 0");
		if (res < 0) {
			perror("write");
			res = errno;
			break;
		}

		res = write_cstr(fd, "ssid laid-dongle-wifi");
		if (res < 0) {
			perror("write");
			res = errno;
			break;
		}

		res = write_cstr(fd, "key abcdefghijk");
		if (res < 0) {
			perror("write");
			res = errno;
			break;
		}

		res = write_cstr(fd, "start");
		if (res < 0) {
			perror("write");
			res = errno;
			break;
		}

		res = 0;
	} while (0);

	if (fd != -1) {
		close(fd);
	}
	if (buf != NULL) {
		free(buf);
	}

	return res;
}
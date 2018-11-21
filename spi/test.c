#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <linux/types.h>
#include <linux/spi/spidev.h>


static void dumpstat(const char *name, int fd)
{
	__u8	mode, lsb, bits;
	__u32	speed;
	__u8	moder =0;
	__u8 lsbr =0; __u8 bitsr =8;
	__u32	speedr =1000000;
//	moder |= SPI_LOOP; mode |= SPI_CPHA; mode |= SPI_CPOL; mode |= SPI_LSB_FIRST; mode |= SPI_CS_HIGH; mode |= SPI_3WIRE; mode |= SPI_NO_CS; mode |= SPI_READY;
	if (ioctl(fd, SPI_IOC_WR_MODE, &moder) < 0) {
		perror("SPI rd_mode");
		return;
	}
	if (ioctl(fd, SPI_IOC_WR_LSB_FIRST, &lsbr) < 0) {
		perror("SPI rd_lsb_fist");
		return;
	}
	if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bitsr) < 0) {
		perror("SPI bits_per_word");
		return;
	}
	if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speedr) < 0) {
		perror("SPI max_speed_hz");
		return;
	}
	if (ioctl(fd, SPI_IOC_RD_MODE, &mode) < 0) {
		perror("SPI rd_mode");
		return;
	}
	if (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) {
		perror("SPI rd_lsb_fist");
		return;
	}
	if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
		perror("SPI bits_per_word");
		return;
	}
	if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) {
		perror("SPI max_speed_hz");
		return;
	}
	printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n",
		name, mode, bits, lsb ? "(lsb first) " : "", speed);
}

int main(void)
{
unsigned char* name ="/dev/spidev1.0";
unsigned char* buf ="asdfghjkl";
unsigned char bytes_written, bytes_read;
unsigned char read_buffer[9];
int fd;
	fd = open(name, O_RDWR);
	if (fd < 0) {
	perror("open");
	return 1;
	}
	dumpstat(name, fd);
	bytes_written =write(fd,buf,9);
	printf("\n	%d Bytes written to %s", bytes_written,name);
	memset (read_buffer,0,9);
	bytes_read = read(fd,&read_buffer,9); /* Read the data*/
	printf("\n	%d Bytes received from %s", bytes_read,name); /* Print the number of bytes read */
	printf("\n	Data:%s\n",read_buffer);
	close(fd);
	return 0;
}
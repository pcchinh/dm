all: out out1 out2

out: spi.c
	arm-linux-gnueabihf-gcc spi.c -o spi
out1: spidev_fdx.c
	arm-linux-gnueabihf-gcc spidev_fdx.c -o ex
out2: test.c
	arm-linux-gnueabihf-gcc test.c -o test
clean:
	rm spi ex test
flash:
	scp test ex spi udooer@192.168.7.2:/home/udooer

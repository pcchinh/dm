all: out

out: spi.c
	arm-linux-gnueabihf-gcc spi.c -o spi
clean:
	rm spi
flash:
	scp spi udooer@192.168.7.2:/home/odooer

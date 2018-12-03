all:
	g++ -c ./*.cpp
	g++ ./Gtest.cpp -I /usr/include/ /usr/lib/libgtest.a -o Gtest.bin -fPIC -O2 -g -Wall -lpthread -coverage

clean:
	rm *.o
	rm ./Gtest.bin

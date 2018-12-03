all:
	g++ -c ./*.cpp
	g++ ./Gtest_example.cpp -I /usr/include/ /usr/lib/libgtest.a -o Gtest_example.bin -fPIC -O2 -g -Wall -lpthread -coverage

clean:
	rm *.o
	rm ./Gtest_example.bin



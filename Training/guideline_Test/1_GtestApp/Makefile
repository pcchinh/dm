all:
	g++ -c ./*.cpp
	g++ ./google_test_example.cpp Employee_details.o /usr/lib/libgtest.a -o google_test_example.bin -fPIC -O2 -g -Wall -lpthread

clean:
	rm *.o
	rm ./google_test_example.bin

all: gtest

gtest: coder.o tests/gtest.o
	g++ -std=c++17 -g coder.o tests/gtest.o -lgtest -lgtest_main -pthread -o gtest
	./gtest
coder.o: coder.cpp coder.h
	g++ -std=c++17 -g -c coder.cpp -o coder.o

tests/gtest.o: tests/gtest.cpp coder.h
	g++ -std=c++17 -g -c tests/gtest.cpp -o tests/gtest.o

clean:
	rm -f coder.o tests/gtest.o gtest

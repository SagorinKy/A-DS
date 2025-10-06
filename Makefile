default: main.cpp gauss.cpp gauss.h
	g++ main.cpp gauss.cpp -o run

test: gtest.cpp gauss.cpp gauss.h
	g++ gtest.cpp gauss.cpp -lgtest -lpthread -o test
	./test

clean:
	rm -f test run *.csv
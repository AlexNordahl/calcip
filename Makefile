# Makefile

main: clean
	g++ -std=c++20 main.cpp headers/utils.cpp -o main

clean:
	rm -f main
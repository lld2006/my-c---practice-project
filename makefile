# add makefile to the list, if makefile changed, still need to compile
1: 1.cpp makefile ../lib/tools.cpp ../lib/tools.h
	g++ -Wall -g 1.cpp ../lib/tools.cpp -std=c++0x -o 1

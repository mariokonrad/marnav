.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -ggdb

all : nmea_sentence

nmea_sentence : nmea_sentence.o
	$(CXX) -o $@ $^

clean :
	rm -f *.o nmea_sentence

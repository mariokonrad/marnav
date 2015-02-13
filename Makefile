.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -ggdb -O2

all : nmea_sentence

nmea_sentence : \
	angle.o \
	time.o \
	date.o \
	sentence.o \
	mtw.o \
	rmc.o \
	nmea.o \
	nmea_sentence.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean :
	rm -f *.o nmea_sentence

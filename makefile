CXX = g++

CXXFLAGS = -Wall -std=c++11

TARGET = main

all:	
	. /usr/share/Modules/init/bash; \
	module load gcc/5.4.0; \
	$(TARGET)

$(TARGET) : lcs.o timer.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) lcs.o timer.o

main.o: lcs.cpp timer.h
	$(CXX) $(CXXFLAGS) -c lcs.cpp

timer.o : timer.h

clean:
	$(RM) $(TARGET) *.o *~

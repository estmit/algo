CXX = g++

CXXFLAGS = -Wall -std=c++11

TARGET = main

<<<<<<< HEAD
all: $(TARGET)
=======
all:	$(TARGET)
>>>>>>> origin/master

$(TARGET): lcs.o timer.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) lcs.o timer.o

main.o: lcs.cpp timer.h
	$(CXX) $(CXXFLAGS) -c lcs.cpp

timer.o : timer.h

clean:
	$(RM) $(TARGET) *.o *~

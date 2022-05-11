CC = /usr/bin/llvm-g++
CPPFLAGS = -Wall -g -std=c++11 -stdlib=libc++

objects = Array.o 

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) -g -O2 $< -o $@

all: $(objects)
	$(CC) -o target $(objects)
clean:
	rm -f *.o 


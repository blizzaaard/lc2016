CC=g++
CFLAGS=-Wall

concordance: concordance.m.o concordance.o
	$(CC) -o concordance concordance.m.o concordance.o

concordance.m.o: concordance.m.cpp
	$(CC) -c $(CFLAGS) concordance.m.cpp

concordance.o: concordance.cpp
	$(CC) -c $(CFLAGS) concordance.cpp

all:
	concordance

clean:
	rm -rf *.o concordance

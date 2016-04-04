CC=g++
CFLAGS=-Wall -O3 -std=c++11
PROG=NaiveBayes
ARGS1=./test/breast_cancer.train ./test/breast_cancer.test 
ARGS2=./test/led.train ./test/led.test

all: assign3.o classifier.o
	$(CC) -o $(PROG) assign3.o classifier.o

assign3.o: assign3.cpp
	$(CC) $(CFLAGS) -c assign3.cpp

classifier.o: classifier.cpp
	$(CC) $(CFLAGS) -c classifier.cpp

clean:
	rm -f *.o $(PROG)

run1: $(PROG)
	./$(PROG) $(ARGS1) 

run2: $(PROG)
	./$(PROG) $(ARGS2) 


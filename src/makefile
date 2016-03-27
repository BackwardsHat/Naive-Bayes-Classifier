CC=clang++
CFLAGS=-Wall -O3 -std=c++11
PROG=NaiveBayes
ARGS=./test/breast_cancer.train ./test/breast_cancer.test 

all: assign3.o classifier.o
	$(CC) -o $(PROG) assign3.o classifier.o

assign3.o: assign3.cpp
	$(CC) $(CFLAGS) -c assign3.cpp

classifier.o: classifier.cpp
	$(CC) $(CFLAGS) -c classifier.cpp

clean:
	rm -f *.o $(PROG)

run: $(PROG)
	./$(PROG) $(ARGS) 


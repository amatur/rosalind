CC=g++
CFLAGS=-c -w

SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o main.out myout.txt

.SILENT:run

run:
	./main.out < input.txt > myout.txt ;\
	cat myout.txt ;\
	echo "\n" ;
	#@main.out < input.txt

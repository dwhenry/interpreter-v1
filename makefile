cc = gcc

CFLAGS = -std=c++11

all: main app_test

scan.o: src/scan.h src/scan.cc src/globals.h src/source_file.h
	g++ $(CFLAGS) -g -c src/scan.cc src/globals.h

source_file.o: src/source_file.cc src/globals.h
	g++ $(CFLAGS) -g -c src/source_file.cc

interpreter.o: src/interpreter.cc src/scan.cc src/source_file.cc src/globals.h
	g++ $(CFLAGS) -g -c src/interpreter.cc

main.o: src/main.cc src/scan.cc src/source_file.cc
	g++ $(CFLAGS) -g -c src/main.cc

main: main.o source_file.o scan.o interpreter.o
	g++ $(CFLAGS) -g -o main main.o source_file.o scan.o interpreter.o

interpreter_test.o: tests/interpreter_test.cc src/interpreter.cc src/scan.cc src/source_file.cc src/globals.h
	g++ $(CFLAGS) -g -c tests/interpreter_test.cc

test.o: tests/test.cc
	g++ $(CFLAGS) -g -c tests/test.cc

app_test: test.o interpreter_test.o interpreter.o scan.o source_file.o
	g++ $(CFLAGS) -g -o app_test test.o interpreter_test.o interpreter.o scan.o source_file.o

clean:
	rm -f app_test main ./*.o


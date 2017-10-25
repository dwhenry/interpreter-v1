cc = gcc

CFLAGS = -std=c++11

all: app

scan.o: src/scan.h src/scan.cc src/globals.h src/source_file.h
	g++ $(CFLAGS) -g -c src/scan.cc src/globals.h

source_file.o: src/source_file.cc src/globals.h
	g++ $(CFLAGS) -g -c src/source_file.cc

interpreter.o: src/main.cc src/interpreter.cc src/scan.cc src/source_file.cc
	g++ $(CFLAGS) -g -c src/interpreter.cc

main.o: src/main.cc src/scan.cc src/source_file.cc
	g++ $(CFLAGS) -g -c src/main.cc

app: main.o source_file.o scan.o interpreter.o
	g++ $(CFLAGS) -g -o main main.o source_file.o scan.o interpreter.o


# test.o: tests/test.cc
# 	g++ $(CFLAGS) -g -c tests/test.cc

# app_test: test.o source_file.o source_file_test.o config_test.o config.o scan_test.o scan.o tests/fakes/fake_config.h tests/fakes/fake_source_file.h
# 	g++ $(CFLAGS) -g -o app_test test.o source_file.o source_file_test.o config_test.o config.o scan_test.o scan.o

clean:
	rm -f app_test app ./*.o


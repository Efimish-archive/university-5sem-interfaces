all: build run clean

build:
	g++ main.cpp -o main.out

run:
	./main.out

clean:
	rm -f main.out

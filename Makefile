all: 1 dollars list-arguments 2 2-print-count

1:
	g++ src/1.cpp -o dist/1.out

dollars:
	g++ src/dollars.cpp -o dist/dollars.out

list-arguments:
	g++ src/list-arguments.cpp -o dist/list-arguments.out -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_program_options

2:
	g++ src/2.cpp -o dist/2.out -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_program_options

2-print-count:
	g++ src/2-print-count.cpp -o dist/2-print-count.out -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_program_options

clean:
	rm -f dist/*

CFLAGS=-Wall -g

all: clean ex1 ex2 ex3 ex7 ex8 ex9 ex10 ex11 ex12

clean:
	rm -f ex1 ex2 ex3 ex7 ex8 ex9 ex10 ex11 ex12
	rm -Rf ./*.dSYM

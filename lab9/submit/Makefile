# Makefile for lab 9
#   "make" or "make all : creates all three executables
#   "make symbol" : creates the symbol executable
#   (similarly for "make bounce" and "make funanim")
 
all: symbol bounce funanim

symbol: symbol.c 
	gcc symbol.c gfx.o -lX11 -lm -o symbol -Wall

bounce: bounce.c 
	gcc bounce.c gfx.o -lX11 -o bounce -Wall

funanim: funanim.c 
	gcc funanim.c gfx.o -lX11 -lm -o funanim -Wall

clean:
	rm symbol bounce funanim


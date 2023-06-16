# Makefile
# Author: Michal Krulich
CC=gcc
ERROR_FLAGS=-pedantic -Wall -Wextra -O2
CSWITCH=-g -std=c11
CFLAGS=$(CSWITCH) $(ERROR_FLAGS)

default: eraprimes

eraprimes: eraprimes.o error.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

eraprimes.o: eraprimes.c bitset.h
	$(CC) $(CFLAGS) -c $<

error.o: error.c
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -f *.o eraprimes

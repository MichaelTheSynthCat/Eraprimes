# Eraprimes
Eraprimes uses the well known algorithm "sieve of Eratosthenes" to find all prime numbers smaller than given limit.

## Implementation
The array of values (true/false) indicating whether a number is prime is implemented using an array of unsigned long, where each bit belongs to a certain number. The first element of this array is a number describing count of used bits.

## Usage
Compile the program with command `make`.
Run it with `./eraprimes` and the program will print out to stdout all prime numbers smaller than the given limit (default 1000000). If you want to change the limit, just type an extra integer as an argument (example `./eraprimes 1243`).

Extra switches:
- `-l` prints out only last 10 prime numbers smaller than the limit.
- `-s` prints out also to stderr time required to find all prime numbers.

# SelfDesc

This program finds all self-descriptive numbers from base 2 to the base given as argument.

A self-descriptive number is an integer *m* which in a given base *b* is *b* digits long. Each digit *d* at position *p* counts how many instances of digits *p* are in *m*. The most significant digit is at position 0 and the least significant digit is at position b-1.

For example, in base 10, the number 6210001000 is self-descriptive because of the following reasons:

- In base 10, the number has 10 digits, indicating its base;
- It contains 6 at position 0, indicating that there are six 0s in 6210001000;
- It contains 2 at position 1, indicating that there are two 1s in 6210001000;
- It contains 1 at position 2, indicating that there is one 2 in 6210001000;
- It contains 0 at position 3, indicating that there is no 3 in 6210001000;
- It contains 0 at position 4, indicating that there is no 4 in 6210001000;
- It contains 0 at position 5, indicating that there is no 5 in 6210001000;
- It contains 1 at position 6, indicating that there is one 6 in 6210001000;
- It contains 0 at position 7, indicating that there is no 7 in 6210001000;
- It contains 0 at position 8, indicating that there is no 8 in 6210001000;
- It contains 0 at position 9, indicating that there is no 9 in 6210001000.

The program takes advantage of the below constraints to find self descriptive number faster:
- The sum of its digits is *b* (6+2+1+1 = 10 in the above example);
- The number of non-zero digits at positions \[ 1 ... *b*-1 \] equals their sum - 1 (3 in the above example);
- The sum of the product of its digits and their respective position is also *b* (6\*0 + 2\*1 + 1\*2 + 1\*6 = 10 in the above example).

The search starts at position *b*-1 and ends at position 0. At each position, the program checks that it is still possible to generate a self-descriptive number, given the digits already selected.

It takes 0,6 seconds on my computer to find all self-descriptive numbers from base 2 to 100.

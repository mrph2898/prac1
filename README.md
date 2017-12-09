# prac1
Practice Task 1:

task1.c include function which forms an union of 2 lists L1, L2 in another list L3. Lists 1 and 2 don't contain repetitive elements. Elements of lists are strings of random size.
Program main.c is a testing program for this function. It prepares lists with a help of advanced functions in advanced_functions.c. Tests for this function is in T1.

task2.c works with files that give to program as arguments of command line. If in some file was find the string with a numbers, 
program change this string in the sum of this numbers. If there weren't numbers, string saves.

script1.sh compile main.c with function task1.c, run tests in T1. Then run a coverage with lcov. Herewith create file of valgrind analysis.

script2.sh does the same things with task2.c


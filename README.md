`Simpletron exercise from Deitel Books`

-> INTRODUCTION:

The SIMPLETRON contains an accumulator — a “special register” in which information is put before the SIMPLETRON uses that information in calculations or examines it in various ways. All information in the SIMPLETRON is handled in terms of words. A word is a signed decimal number such as +3364, -1293, +0007, -0001 and so on. The SIMPLETRON is equipped with a 100 - word memory ( in its default configuration, but this can be varied by changing the macro "MEM_SIZE" in "SIMPLETRON.h" ) and these words are referenced by their location numbers 00, 01, ..., 99. Before running an SML ( SIMPLETRON Machine Language ) program, we must load or place the program into memory. The first instruction (or statement) of every SML program is always placed in location 00. Each instruction written in SML occupies one word of the SIMPLETRON’s memory. Each location in the Simpletron’s memory may contain either an instruction, a data value used by a program or an unused (and hence undefined) area of memory. The first two digits of each SML instruction are the operation code, which specifies the operation to be performed. ALL SML operation codes are summarised later in the text. Subsequent digits of each SML instruction are the operand, which is the address of the memory location containing the word to which the operation applies. A dump of all registers and the memory is provided after execution of ALL programs.

The SIMPLETRON is capable of handling floating point numbers.

<-------------------->

-> A description of all the operation codes:

Input/Output operatons:
	10 Read a word from the terminal into a given location in memory.
	11 Write a word from a given location in memory to the terminal.
	12 Read a string of characters from the terminal in the given memory location. 
		Each memory location holds two characters except for the first one which holds one character + the length of the string. 
		Subsequent memory locations are used for the purpose as needed. 
	13 Write a string of characters to the terminal from a given memory location.
	14 Write a newline to the terminal

LOAD/STORE operatons:
	20 Load a word from a given location in memory into the accumulator.
	21 Store a word from the accumulator into a given location in memory.

Arithmetic operatons:
	30 Add a word from a given location in memory to the word in the accumulator (leave result in accumulator).
	31 Subtract a word from a given location in memory from the word in the accumulator (leave result in accumulator).
	32 Divide a word from a given location in memory into the word in the accumulator (leave result in accumulator).
	33 Multiply a word from a given location in memory by the word in the accumulator (leave result in accumulator).
	34 Divide what is in the accumulator by a word from a given location in memory and calculate the remainder (leave result in accumulator)
	35 Exponentiate what is in the accumulator by a word from a given location in memory (leave result in accumulator)

Transfer-of-control operations:
	40 Branch to a specific location in memory unconditionally.
	41 Branch to a specific location in memory if the accumulator is negative.
	42 Branch to a specific location in memory if the accumulator is zero.
	43 Halt - i.e., the program has completed its task and the program execution stops (all memory locations for variables to be reserved AFTER this instruction)

-> Note: All operands, when needed with a operation code and 00 otherwise, are memory locations. 

<-------------------->

-> Sample Program:

This program reads a series of numbers and determines and prints the smallest of them. The first number entered is taken as the number of subsequent inputs.

00  1021 ( Read a word from terminal into location 21 ) 
01  2021 ( Load into accumulator the contents of location 21 ) 
02  3120 ( Subtract from accumulator the word in location 20 )
03  2121 ( Store from accumulator into location 21 )
04  1018 ( Read a word from terminal into location 18 ) 
05  4216 ( Branch to location 16 if accumulator is zero )
06  1019 ( Read a word from terminal into location 19 )  
07  2018 ( Load into accumulator the contents of location 18 ) 
08  3119 ( Subtract from accumulator the word in location 19 )
09  4112 ( Branch to location 12 if accumulator is negative )
10  2019 ( Load into accumulator the contents of location 19 ) 
11  2118 ( Store from accumulator into location 18 )
12  2021 ( Load into accumulator the contents of location 21 ) 
13  3120 ( Subtract from accumulator the word in location 20 )
14  2121 ( Store from accumulator into location 21 )
15  4005 ( Branch to location 05 )
16  1118 ( Write word at location 18 to the terminal )
17  4300 ( HALT instruction for the simpletron )
18  0000 ( variable smaller )
19  0000 ( variable num )
20  0001 ( variable increment )
21  0000 ( variable num_of_loops )

<-------------------->


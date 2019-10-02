#include "SIMPLETRON.h"

//loads instructions for the simpletron into an array
void load( float * const mem ) {
	int i;
	int flag = 1;
	
	for( i = 0; i < MEM_SIZE; i++ ) {
		printf("%02i ->  ", i);
		scanf("%f", mem + i );
		
		if( mem[i] == -99999 )
			break;
		
		if( (int)( mem[i] / 100 ) == 43 )
			flag = 0;
			
		if( flag && check_invalid_instruction( mem[i] ) ) {
			printf("Invalid instruction on %02i\n", i);
			i--;
		}
	}
	memset( mem + i, 0, (MEM_SIZE - i) * sizeof(float) );
}

//executes verified instrcutions line by line and changes register values
void execute( float * mem, float * const accumulator, float * const instruction_register, int * const instruction_number ){
	int end = 0;
	int i;
	int char_count;
	char character;
	int operation_code = 0;
	int operand = 0;
	
	for( *instruction_number = 0; *instruction_number < MEM_SIZE && !end; (*instruction_number)++ ) {
		*instruction_register = mem[ *instruction_number ];
		operation_code = (int)*instruction_register / (int)( pow( 10, ceil( log10(MEM_SIZE) ) ) + 0.5 );
		operand = (int)*instruction_register % (int)( pow( 10, ceil( log10(MEM_SIZE) ) ) + 0.5 );
		
		//check for invalid operands
		if( operand >= MEM_SIZE || operand < 0 ) {
			printf("*** invalid memory location requested in line: %i ***\n"
				   "*** Simpletron execution abnormally terminated ***\n\n", *instruction_number);  //unsuccessfull termination
			break;
		}
		
		switch ( operation_code ) {
			 //Read a number from the terminal into a specific location in memory
			case 10:
				scanf("%f", &mem[ operand ] );
				break;
				
			//Write a number from a specific location in memory to the terminal
			case 11:
				printf("%f\n", mem[ operand ] );
				break;
				
			//Read a line of chars from the terminal and store them into the memory, 2 char per word, starting from a specific location of memory
			case 12: //does not handle first 31 characters of ascii because we have only 2 digits to represent a char
				mem[ operand ] = 0;
				getchar(); //to trash a useless '\n' in stdin
				for( char_count = 0; ( character = getchar() ) != '\n'; char_count++ ) {
					if( char_count % 2 == 0 ) {
						mem[ operand + char_count / 2 ] += character - 32; //write the ASCII code of the character minus 32 to right size of memory word
					} else {
						mem[ operand + char_count / 2 + 1 ] = 0;
						mem[ operand + char_count / 2 + 1 ] += 100 * ( character - 32 ); //write the ASCII code of the character minus 32 to left size of memory word
					}
				}
				mem[ operand ] += 100 * char_count; //write length of string to left side of first memory word
				break;
				
			//write a string which starts from a specific memory location to the terminal
			case 13:
				char_count = mem[ operand ] / 100;
				for( i = 0; i < char_count; i++ ) {
					if( i % 2 == 0 ) {
						putchar( (int)mem[ operand + i / 2 ] % 100 + 32 );
					} else {
						putchar( (int)mem[ operand + i / 2 + 1 ] / 100 + 32 );
					}
				}
				break;
				
			//write newline to the terminal
			case 14:
				putchar( '\n' );
				break;
				
			//Load a number from a specific location in memory into the accumulator
			case 20:
				*accumulator = mem[ operand ];
				
				check_overflow( *accumulator, &end );
				
				break;
				
			//Store a number from the accumulator into a specific location in memory
			case 21:
				mem[ operand ] = *accumulator;
				break;
				
			//Add a number from a specific location in memory to the number in the accumulator (leave result in accumulator)
			case 30:
				*accumulator += mem[ operand ];
				
				check_overflow( *accumulator, &end );
				
				break;
				
			//Subtract a number from a specific location in memory from the number in the accumulator (leave result in accumulator)
			case 31:
				*accumulator -= mem[ operand ];
				
				check_overflow( *accumulator, &end );
				
				break;
				
			//Divide what is in the accumulator by a number from a specific location in memory (leave result in accumulator)
			case 32:
				if( mem[ operand ] == 0 ) { //check for division by zero
					printf("*** Attempt to divide by zero ***\n"
						   "*** Simpletron execution abnormally terminated ***\n\n"); //unsuccessfull termination
					end = 1;
					break;
				}
				
				*accumulator /= mem[ operand ];
				
				check_overflow( *accumulator, &end );
				
				break;
				
			//Multiply a number from a specific location in memory by the number in the accumulator (leave result in accumulator)
			case 33:
				*accumulator *= mem[ operand ];
				
				check_overflow( *accumulator, &end );
				
				break;
				
			//Divide what is in the accumulator by a number from a specific location in memory and calculate the "remainder" (leave result in accumulator)
			case 34:
				if( mem[ operand ] == 0 ) { //check for division by zero
					printf("*** Attempt to divide by zero ***\n"
						   "*** Simpletron execution abnormally terminated ***\n\n"); //unsuccessfull termination
					end = 1;
				}
				
				*accumulator = fmod( *accumulator,  mem[ operand ] );
				
				check_overflow( *accumulator, &end );
				
				break;
				
			//Exponentiate what is in the accumulator by a number from a specific location in memory (leave result in accumulator)
			case 35:
				*accumulator = pow( *accumulator, mem[ operand ] );
				
				check_overflow( *accumulator, &end );
				
				break;
				
			//Branch to a specific location in memory.
			case 40:
				*instruction_number = operand - 1;
				break;
				
			//Branch to a specific location in memory if the accumulator is negative
			case 41:
				if( *accumulator < 0) *instruction_number = operand - 1;
				break;
				
			//Branch to a specific location in memory if the accumulator is zero
			case 42:
				if( *accumulator == 0) *instruction_number = operand - 1;
				break;
				
			//Halt == the program has completed its task
			case 43:
				printf("\n*** Simpletron execution terminated successfully ***\n\n"); //successfull termination
				end = 1;
				break;
				
			//won't happen normally because load() rejects all invalid instructions
			default:
				printf("\n*** Unknown operation code encoutered ***\n\n"); //unsuccessfull termination
				end = 1;
				break;
		}
	}
}

//display values of all registers and memory locations in a nice format
void dump( const float * const mem, const float accumu, const float ins_reg, const int ins_num ) {
	int i, j;
	int rows = (int)ceil( MEM_SIZE / (float)10 );
	int op_code = (int)ins_reg / (int)( pow( 10, ceil( log10(MEM_SIZE) ) ) + 0.5 );
	int operand = (int)ins_reg % (int)( pow( 10, ceil( log10(MEM_SIZE) ) ) + 0.5 );
	
	printf("REGISTERS: \n"
		   "    %-24s%+09f\n"      "    %-24s%02i\n"            "    %-24s%+05.0f\n"            "    %-24s%02i\n"       "    %-24s%02i\n\n",
		   "accumulator", accumu,  "instruction_number", ins_num,  "instruction_register", ins_reg,  "operation_code", op_code,  "operand", operand );
	
	printf("MEMORY:\n     ");
	
	for( i = 0; i < 10; i++ ) {
		printf("%12i", i);
	} puts("");
	
	for( i = 0; i < rows; i++ ) {
		printf("%3i  ", 10 * i );
		
		for( j = 0; j < 10; j++ ) {
			if( 10*i + j >= MEM_SIZE ) break;
			printf("   %+09.3f", mem[ 10*i + j ] );
		}
		
		puts("");
	}
}

//checks if given instruction is in word size range (which is determined by memory size) and if it has a valid operation code
bool check_invalid_instruction( const float instruction ) {
	int operation_code = (int)instruction / 100;
	int word_size = (int)( pow( 10, ceil( log10(MEM_SIZE) ) + 2 ) + 0.5 ) - 1;
	int flag = 0;
	
	if( instruction > word_size || instruction < -word_size )
		flag = 1;
	
	switch ( operation_code ) {
			
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		        
		case 20:
		case 21:
			
		case 30:    // these are all the valid operation codes
		case 31:  
		case 32:  
		case 33:  
		case 34:  
		case 35:  
				
		case 40:  
		case 41: 
		case 42: 
		case 43: 
			break;
			
		default:
			flag = 1;
			break;
	}
	
	return flag; //return 1 if instruction is invalid otherwise 0
}

void give_intro( void ) {
	printf("         *** Welcome to Simpletron! ***\n\n"
		   "*** Please enter your program one instruction ***\n"
		   "*** (or data word) at a time. I will type the ***\n"
		   "*** location number and a question mark (?).  ***\n"
		   "*** You then type the word for that location. ***\n"
		   "*** Type the sentinel -99999 to stop entering ***\n"
		   "*** your program. ***\n");
}

void check_overflow( const float to_be_checked, int * const the_flag ) {
	int word_size = (int)( pow( 10, ceil( log10(MEM_SIZE) ) + 2 ) + 0.5 ) - 1;
	
	if( to_be_checked > word_size || to_be_checked < -word_size ) {
		printf("*** accumulator overflow ***\n"
			   "*** Simpletron execution abnormally terminated ***\n\n"); //unsuccessfull termination
		*the_flag = 1;
	}
}



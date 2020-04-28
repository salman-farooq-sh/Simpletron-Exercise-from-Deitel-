#include <stdio.h>
#include "SIMPLETRON.h"

//const int MEM_SIZE = 100;

int main() {
	//sample programs to have a quick try. Uncomment one.	
	//float memory[MEM_SIZE] = { 1017,2018,3117,4215,2018,3021,2118,1019,2020,3119,4112,4001,2019,2120,4001,1120,4300,0000,0000,0000,0000,0001 };
	//float memory[MEM_SIZE] = { 1065, 2065, 1009, 3209, 2110, 1110, 4300 };
	//float memory[MEM_SIZE] = { 1250, 1350, 1400, 4300 };
	//float memory[MEM_SIZE] = { 1020, 2020, 4105, 1025, 1025, 1120, 4300 };
	//float memory[MEM_SIZE] = { 1009, 2009, 4106, 3008, 2108, 4000, 1108, 4300, 0000, 0000  };
	//float memory[MEM_SIZE] = { 1021,2021,3120,2121,1018,4216,1019,2018,3119,4112,2019,2118,2021,3120,2121,4005,1118,4300,0000,0000,0001,0000 };

	float memory[MEM_SIZE];
	
	//registers
	float accumulator = 0;
	float instruction_register = 0; // all instructions are first loaded here
	int instruction_number = 0;
	
	give_intro();
	
	printf("\nEnter instructions:\n");
	
	// comment the following line if you are using one of the sample programs above.
	load( memory );
	
	printf("\n*** Program loading completed ***\n*** Program execution begins"
		   "***\n\n--------------------------------------\n\n");
	
	execute( memory, &accumulator, &instruction_register, &instruction_number );
	
	//give a dump of everything at successfull AND unsuccessful executions at the end
	dump( memory, accumulator, instruction_register, instruction_number );
	
	
	//hold screen
	getchar();getchar();getchar();getchar();getchar();getchar();getchar();
}

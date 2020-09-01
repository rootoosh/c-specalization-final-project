#include <stdio.h>
#include <stdlib.h>

//struct of assembly command for validation on commands
typedef struct 
{
	char* name;
	//type of resident method can be the source operands
	int sourceResident[3];
	//type of resident method can be the dest operands
	int destResident[3];
	//num of operators should be in that command
	int numOperators;
}S_command;

//struct of binary code machine or data
//this is the requested output
//for the .ob file
typedef struct 
{
	unsigned char destRegister : 3;
	unsigned char destResident : 3;
	unsigned char sourceRegister : 3;
	unsigned char sourecResident : 3;
	unsigned char command : 4;
	//total: 16 bits
}S_binaryCodeMachineOrData;

//struct represent node in data list and in instruction list
typedef struct node
{
	int adress;
	char* label;
	char* command;
	char* firstOperand;
	char* secondOperand;
	S_binaryCodeMachineOrData binaryCode;
	node* next;
}*S_node;

typedef struct
{
	char* label;
	int address;
}S_symbol;

//make array that represent all the commands that valid in assembly
S_command cammoandTable[];


/*
need symbol tble with dynamic allocation
need data&instruction table with dynamic alocation
need IC and DC counters
need functino to initilize comandTable
need fucntion to firstCycleîòáø øàùåï and fill all
that possible: 
 */

S_node dataList = (S_node)malloc(sizeof(S_node));



#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef enum { local, entry, external } E_scopeLabel;
typedef enum { data, instruction }E_typeLabel;

//struct of binary code machine or data
//this is the requested output
//for the .ob file
//typedef struct binaryCode
//{
//	unsigned char destRegister : 3;
//	unsigned char destResident : 3;
//	unsigned char sourceRegister : 3;
//	unsigned char sourecResident : 3;
//	unsigned char command : 4;
//	//total: 16 bits
//}S_binaryCodeMachineOrData;

//struct represent node in instruction list
typedef struct nodeI
{
	int address;
	char* label;
	char command[3];
	char* firstOperand;
	char* secondOperand;
	/*S_binaryCodeMachineOrData binaryCode;*/
	unsigned int binaryCode : 16;
	char state;
	struct nodeI* next;
}S_nodeInstruction;

//struct represent node in Data list
typedef struct nodeD
{
	int address;
	char* label;
	//.data or .string
	char* type;
	//represent the content data in binary
	//should be node for every piece of data
	unsigned int binaryCode : 16;
	/*S_binaryCodeMachineOrData binaryCode;*/
	struct nodeD* next;
}S_nodeData;

//node in symbol table
typedef struct symbol
{
	char* label;
	int address;
	E_scopeLabel scope; //0- local 1- entry  2- extrnal
	E_typeLabel type; //instruction or data
	struct symbol* next;
}S_symbol;


 typedef struct arraySymbol
{
	struct symbol* head;
	/* head pointing the first element of Linked List at an index of Hash Table */

	struct symbol* tail;
	/* tail pointing the last element of Linked List at an index of Hash Table */
}S_arraySymbol;



//prototype of helpers function for all sulotion-helpers.c
char* f_ingnoreSpaces(char* string);

//prototype of initilize function-structures.c
struct nodeD* f_insertDirective();
struct nodeI* f_insertInstruction();

void freeList();

typedef struct
{
	//type of resident method can be the source operands
	int sourceResident[6];
	//type of resident method can be the dest operands
	int destResident[6];
	char name[4];
	//num of operators should be in that command
	int numOperands;
}S_command;

/*
need symbol tble with dynamic allocation
need data&instruction table with dynamic alocation
need IC and DC counters
need functino to initilize comandTable
need fucntion to firstCycle���� ����� and fill all
that possible:
 */
#endif

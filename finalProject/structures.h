#include <stdio.h>
#include <stdlib.h>

typedef enum  { local, entry, external } E_scopeLabel;
typedef enum  { data,instruction}E_typeLabel;

//struct of binary code machine or data
//this is the requested output
//for the .ob file
typedef struct binaryCode
{
	unsigned char destRegister : 3;
	unsigned char destResident : 3;
	unsigned char sourceRegister : 3;
	unsigned char sourecResident : 3;
	unsigned char command : 4;
	//total: 16 bits
}S_binaryCodeMachineOrData;

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
	//0 regular
	//1 entry
	//2 extrnal
	E_scopeLabel scope;
	//string or data
	E_typeLabel type;
	struct symbol* next;
}S_symbol;


//instruction counter
int IC;
//data counter
int DC;

//the list of instriction :1 pointer as head. 1 pointer as tail

struct nodeI* headInstrucionList;
struct nodeI* tailInstrucionList;
//the list of data: 1 pointer as 
struct nodeD* headDataList;
struct nodeD* tailDataList;


void initList()
{
struct nodeI* headInstrucionList = (struct nodeI*)malloc(sizeof(struct nodeI));
struct nodeI* tailInstrucionList = headInstrucionList;
//the list of data: 1 pointer as head, 1 pointer as tail
struct nodeD* headDataList = (struct nodeD*)malloc(sizeof(struct nodeD));
struct nodeD* tailDataList = headDataList;
IC = 0;
DC = 0;
}
/*
need symbol tble with dynamic allocation
need data&instruction table with dynamic alocation
need IC and DC counters
need functino to initilize comandTable
need fucntion to firstCycle���� ����� and fill all
that possible: 
 */




#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "validation.h"
#include "manageInstruction.h"
#include "manageDirective.h"
#include "structures.h"
#include "symbolsHash.h"

extern struct nodeI* headInstrucionList;


//function to read row, check is valid, 
//put in the suitable structure
void f_assembleFirstPass(FILE* inputFile)
{
	int hasError = 0;
	//has label in that row or not
	char* isLabelInRow = NULL;
	//number of row in the input file
	int rowNum = 0;
	int len = 0;
	size_t rowLength;
	char* row = (char*)malloc(sizeof(char));
	//is has error(0) in the row or:  is it insturction(1) or data(2).
	int status;
	//while there are rows in the file
	while ((len = getline(&row, &rowLength, inputFile)) != 0)
	{
		//print error of too many characters
		if (len > 80)
		{
			printf("in row %d too many charcters in row", rowNum);
			status = 0;
		}
		else
		{
			//if getline success to read from the file
			if (len != -1)
			{
				//chcek if the row is valid, and is it data or instructio
				status = f_checkIsValidRow(row, rowNum, &isLabelInRow);
				//status =1 mean is instrucion
				if ((status == 1) && (!hasError))
				{
					f_manamgeInstruction(row, isLabelInRow);
				}
				//status =2 mean is data instruction
				else if ((status == 2) && (!hasError))
				{
					f_manageDirective(row, isLabelInRow);
				}
				//status=0- mean has error in the row
				else if (status == 0)
				{
					hasError = 1;
				}
			}
		}
		//inc the row number
		rowNum++;
	}
}

//add new node in the middile of the list
S_nodeInstruction* f_OperandNewNode(int address, int labelAddress, E_scopeLabel scope)
{
	struct nodeI* newNode = (struct nodeI*)malloc(sizeof(struct nodeI));
	newNode->address = address;
	newNode->binaryCode = labelAddress;
	newNode->firstOperand = NULL;
	newNode->secondOperand = NULL;
	newNode->state = 'r';
	if (scope == external)
	{
		newNode->state = 'e';
	}

	return newNode;
}

void f_assembleSecondPass()
{
	S_nodeInstruction* ptr = headInstrucionList;
	S_nodeInstruction* nextPtr;
	S_nodeInstruction* newNode;
	struct symbol* correctSymbol;
	while (ptr != NULL)
	{
		if (ptr->firstOperand)
		{
			nextPtr = ptr->next;
			correctSymbol = search(ptr->firstOperand);
			if (correctSymbol == NULL)
			{
				printf("error, use label without decalre it");
			}
			else
			{
			newNode = f_OperandNewNode(ptr->address + 1, correctSymbol->address,correctSymbol->scope);
			ptr->next = newNode;
			newNode->next = nextPtr;
			}
		}
		if (ptr->secondOperand)
		{
			correctSymbol = search(ptr->secondOperand);
			if (correctSymbol == NULL)
			{
				printf("error, use label without decalre it");
			}
			else
			{
				nextPtr = ptr->next;
				//�� ����� ��� ���� ������ ��� ���� �� ����� ������,
				//���� ���� ��� ��� ������ ���� ������ ���
				//������� ������ ���� ����� ���� ����� ������ �� ���� �� ���� ����� ���� ���� ����
				if (nextPtr->address - 1 == ptr->address)
				{
					newNode = f_OperandNewNode(nextPtr->address + 1, correctSymbol->address, correctSymbol->scope);
					newNode->next = nextPtr->next;
					nextPtr->next = newNode;
				}
				//��� ����� �� ������ ���� ����� ��� �� ������ �� ���� �������
				else
				{
					newNode = f_OperandNewNode(ptr->address + 1, correctSymbol->address, correctSymbol->scope);
					ptr->next = newNode;
					newNode->next = nextPtr;
				}
			}
		}
		ptr = ptr->next;
	}
}


/*
the order of assembelr:

1.first pass
2.if error flag is true:
free alocation memory in list
and return file with errors
3.if error flag is false:
init hash table for symbols.convert form list to hash
second pass
in the second pass we shuold check all the nodes:
if the field "first operand" or "secondOperand "
not null- we shuld do something
for lebels should manage address
4.write output files
5.  free alocation memory
*/






#include "structures.h"

S_nodeInstruction* f_insertInstruction()
{
	struct nodeI* newNode = (struct nodeI*)malloc(sizeof(struct nodeI));
	newNode->address = IC;
	newNode->binaryCode = 0;
	newNode->firstOperand = NULL;
	newNode->secondOperand = NULL;
	newNode->next = NULL;
	if (headInstrucionList == NULL)
	{
		headInstrucionList = newNode;
		tailInstrucionList = headInstrucionList;
	}
	else
	{
		tailInstrucionList->next = newNode;
		tailInstrucionList = tailInstrucionList->next;
	}
	return newNode;
}


void initList()
{
		//the list of data: 1 pointer as head, 1 pointer as tail
	headDataList = (struct nodeD*)malloc(sizeof(struct nodeD));
	tailDataList = headDataList;
	IC = 0;
	DC = 0;
}

void freeList()
{
	tailDataList = headDataList->next;
	while (headDataList != NULL)
	{
		free(headDataList);
		headDataList = tailDataList;
		if (tailDataList != NULL)
		{
			tailDataList = tailDataList->next;
		}
	}

	tailInstrucionList = headInstrucionList->next;
	while (headInstrucionList != NULL)
	{
		free(headInstrucionList);
		headInstrucionList = tailInstrucionList;
		if (tailInstrucionList != NULL)
		{
			tailInstrucionList = tailInstrucionList->next;
		}
	}
}
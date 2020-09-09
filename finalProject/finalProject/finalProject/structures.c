
#include "structures.h"
#include <stdio.h>
//gloabel variables

//instruction counter-
 int IC = 0;
//data counter
int DC = 0;

//static variables

//the list of instriction :1 pointer as head. 1 pointer as tail
struct nodeI* headInstrucionList = NULL;
struct nodeI* tailInstrucionList;
//the list of data: 1 pointer as 
struct nodeD* headDataList = NULL;
struct nodeD* tailDataList;


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
S_nodeData* f_insertDirective()
{
	struct nodeD* newNode = (struct nodeD*)malloc(sizeof(struct nodeD));
	newNode->address = DC;
	newNode->binaryCode = 0;
	newNode->label = NULL;
	newNode->type = NULL;
	newNode->next = NULL;
	if (headDataList == NULL)
	{
		headDataList = newNode;
		tailDataList = headInstrucionList;
	}
	else
	{
		tailDataList->next = newNode;
		tailDataList = tailDataList->next;
	}
	return newNode;
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
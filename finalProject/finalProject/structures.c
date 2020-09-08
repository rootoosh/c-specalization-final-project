#include "structures.h"
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
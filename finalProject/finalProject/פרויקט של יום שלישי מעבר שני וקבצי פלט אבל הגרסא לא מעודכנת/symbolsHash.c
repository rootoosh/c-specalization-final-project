#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "structures.h"

//static viriables

//count the number of the node in the list
int sizeList = 0;
//pointers to the list
struct symbol* headSymbolList = NULL;
struct symbol* tailSymbolList;
S_arraySymbol* hashTabel;

//this functioin get detalis of label and insert into S_symbol struct
void f_insertLabel(char* label, E_typeLabel type, E_scopeLabel scope, int address)
{
	//create new node and initialization
	struct symbol* newNode = (struct symbol*)malloc(sizeof(struct symbol));
	newNode->label = label;
	newNode->address = address;
	newNode->type = type;
	sizeList++;
	//make head point only to the first node in the list
	if (!headSymbolList)
	{
		headSymbolList = newNode;
	}
	else {
		tailSymbolList->next = newNode;
	}
	tailSymbolList = newNode;
	newNode->next = NULL;
}

void f_initHash(int capacity)
{
	//allocate hash tabel in size sizeList
	hashTabel = (S_arraySymbol*)malloc(sizeof(S_arraySymbol) * sizeList);
	int i = 0;
	for (i = 0; i < sizeList; i++)
	{
		hashTabel[i].head = NULL;
		hashTabel[i].tail = NULL;
	}
}

//hash code function for a label name
int f_hashCode(char* label)
{
	unsigned int sum = 0;
	size_t j;
	for (j = 0; j < strlen(label); j++)
	{
		sum += pow(label[j], j);
	}
	return sum % sizeList;
}

//this function Take each node from the list S_symbol
//and puts it in the hash table and disconnects it from the list 
void f_convertFromListToHash()
{
	//pointer to the symbol list
	struct symbol* ptr;
	ptr = headSymbolList;
	int index;

	while (ptr->next != NULL)
	{
		//give the index in the hash tabel for this label 
		index = hashcode(ptr->label);

		if (!(hashTabel[index].head))
		{
			hashTabel[index].head = ptr;
		}
		else
		{
			hashTabel[index].tail->next = ptr;
		}
		headSymbolList = headSymbolList->next;
		ptr->next = NULL;
		hashTabel[index].tail = ptr;
		ptr = headSymbolList;
	}
	//insert the last node into the hash tabel
	hashTabel[index].tail->next = ptr;
	hashTabel[index].tail = ptr;
	ptr = headSymbolList;
}

struct symbol* search(char* key) {

	//get the hash 
	int hashIndex = f_hashCode(key);
	struct symbol* ptr;
	//ptr point to the list in the  hashTabel[hashIndex]
	ptr = hashTabel[hashIndex].head;
	while (ptr)
	{
		//check if the label name equal to the key  
		if (ptr->label == key)
		{
			return ptr;
		}
	}
	return NULL;
}


void f_updateScopeLabel(char* label, E_scopeLabel scope)
{

}

void f_modifyLabel(char* row, E_typeLabel type, E_scopeLabel scope)
{
	//the row point to the word:entry or:extern
	//note yoou souhuld find space and after him- the label to midify. cut it and
	//send to "updateScopeLabel(char * label,E_scopeLabel scope)"
	char* ptr;
	ptr = strchr(row, ' ');
	if (!ptr)
	{
		ptr = strchr(row, '\t');
	}
	row = f_ingnoreSpaces(ptr);
	ptr = row;
	while ((*ptr) && (*ptr != ' ') && (*ptr != '\t') && (*ptr != '\n'))
	{
		ptr++;
	}
	*ptr = '\0';
	f_insertLabel(row, type, scope, NULL);
}

struct symbol* f_getNextExtern(struct symbol* prevExtern)
{
	static int i = 0;
	struct symbol* currentExtern;
	if (prevExtern == NULL)
	{
		currentExtern = hashTabel[0].head;
	}
	else
	{
		currentExtern = prevExtern->next;
	}
	while (i < sizeList)
	{

		while (currentExtern != NULL)
		{
			if (currentExtern->scope == "extern")
				return currentExtern;
		}
		i++;
	}
	return NULL;
}

struct symbol* f_getNextEntry(struct symbol* prevEntry)
{
	static int i = 0;
	struct symbol* currentEntry;
	if (prevEntry == NULL)
	{
		currentEntry = hashTabel[0].head;
	}
	else
	{
		currentEntry = prevEntry->next;
	}
	while (i < sizeList)
	{

		while (currentEntry != NULL)
		{
			if (currentEntry->scope == "entry")
				return currentEntry;
		}
		i++;
	}
	return NULL;
}

////the function get label and type and insert it to the symbols table
//void f_insertLabel(char* label, E_typeLabel labelType,int address)
//{
//	/*
//
//
//	����� ���� ����� �� ����, ������ �� �����: �� ����� ��� ������ IC
//	  labelType��� ���
//	  ����� ��� ������
//	������ ����� ��� �� �����
//	����� �� ���� ���� ���, ������� ����� ���'
//	���� ����� ����� ����
//	���� ������ �����
//	��
//	*/
//}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "structures.h"
#include "symbolsHash.h"


//static viriables

//count the number of the node in the list
int sizeList = 0;
//pointers to the list
struct symbol* headSymbolList = NULL;
struct symbol* tailSymbolList;
S_arraySymbol* hashTabel;

//this functioin get detalis of label and insert into S_symbol struct
void f_insertLabel(char* label, E_typeLabel type,E_scopeLabel scope, int address)
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
int f_convertFromListToHash()
{
	int hasError = 0;
	//pointer to the symbol list
	struct symbol* ptr;
	struct symbol* hasThatSymb;
	ptr= headSymbolList;
	int index;
	if (ptr == NULL)
	{
		return;
	}
	while (ptr != NULL)
	{
		//give the index in the hash tabel for this label 
		index = hashcode(ptr->label);
		hasThatSymb = search(ptr->label);
		//if not have that symbol already
		if(hasThatSymb==NULL)
		{
			//for the first node in that index
		if (!(hashTabel[index].head))
		{
			hashTabel[index].head = ptr;
		}
		//for other nodes
		else
		{
			hashTabel[index].tail->next = ptr;
			
		}
		hashTabel[index].tail = ptr;
		//remove the node from the symbol list
		ptr->next = NULL;
		//the symbol list now not conation this symbol
		headSymbolList = headSymbolList->next;
		}
		//that symbol already exist
		else
		{
			//modify local to entry
			if ((hasThatSymb->scope == local) && (ptr->scope == entry))
			{
				hasThatSymb->scope = entry;
			}
			//modify entry with his address
			else if((hasThatSymb->scope==entry) && (ptr->scope==local))
			{
				hasThatSymb->address = ptr->address;
			}
			//if put twice entry or twice extern for the same label is not error. else is error
			else if (!((hasThatSymb->scope == ptr->scope) && (ptr->scope != local)))
			{
				hasError = 1;
				printf("there is eror with the scope of the label %s. maby you put conflict scope or the same label twice", ptr->label);
			}
			ptr->next = NULL;
			headSymbolList = headSymbolList->next;
			free(ptr);
		}
		
		//for the next iteration
		ptr = headSymbolList;
	}
	return hasError;
}
//return only pinter to node in hash table. not new copy
struct  symbol* search(char* key) 
{

	//get the hash 
	int hashIndex = f_hashCode(key);
	struct symbol* ptr;
	//ptr point to the list in the  hashTabel[hashIndex]
	ptr = hashTabel[hashIndex].head;
	while (ptr)
	{
		//check if the label name equal to the key  
		if (strcmp(ptr->label,key))
		{
			return ptr;
		}
	}
	return NULL;
}



void f_modifyLabel(char* row,E_typeLabel type, E_scopeLabel scope)
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

////the function get label and type and insert it to the symbols table
//void f_insertLabel(char* label, E_typeLabel labelType,int address)
//{
//	/*
//
//
//	ליצור מבנה מתאים של תוית, להכניס בו ערכים: שם כתובת לפי הכתובת IC
//	  labelTypeסוג לפי
//	  הסקופ הוא לוקאלי
//	להכניס לטבלת האש את התוית
//	לצורך זה צריך טבלת האש, פונקצית גיבוב וכו'
//	צריך להיות מוגדר מראש
//	מספר השורות בקובץ
//	כי
//	*/
//}
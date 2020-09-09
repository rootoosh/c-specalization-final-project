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
void f_insertLabel(char* label, E_typeLabel type, int address)
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
	ptr= headSymbolList;

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

struct  symbol* search(char* key) {

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

//the function get label and type and insert it to the symbols table
//void f_insertLabel(char* label, E_typeLabel type, int address)
//{
//	S_symbol* newSymbol = (S_symbol*)malloc(sizeof(S_symbol));
//	newSymbol->address = address;
//	newSymbol->label = label;
//	newSymbol->type = type;
//	newSymbol->next = NULL;
//	//get the hash 
//	int hashIndex = f_hashCode(label);
//
//	S_symbol* list = (s_symbol*)hashSymbols[hashIndex].head;
//	//move with pointer
//	S_symbol* pointer = ;
//	//move in array until an empty cell
//	while (pointer != NULL)
//	{
//		pointer = pointer->next;
//	}
//
//	pointer = newSy
//}
//
//void insert(int key, int value)
//{
//	float n = 0.0;
//	/* n => Load Factor, keeps check on whether rehashing is required or not */
//
//	int index = hashcode(key);
//
//	/* Extracting Linked List at a given index */
//	struct s_symbol* list = (s_symbol*)hashSymbols[index].head;
//
//	/* Creating an item to insert in the Hash Table */
//	struct node* item = (struct node*)malloc(sizeof(struct node));
//	item->key = key;
//	item->value = value;
//	item->next = NULL;
//
//	if (list == NULL)
//	{
//		/* Absence of Linked List at a given Index of Hash Table */
//
//		printf("Inserting %d(key) and %d(value) \n", key, value);
//		array[index].head = item;
//		array[index].tail = item;
//		size++;
//
//	}
//	else
//	{
//		/* A Linked List is present at given index of Hash Table */
//
//		int find_index = find(list, key);
//		if (find_index == -1)
//		{
//			/*
//			 *Key not found in existing linked list
//			 *Adding the key at the end of the linked list
//			*/
//
//			array[index].tail->next = item;
//			array[index].tail = item;
//			size++;
//
//		}
//		else
//		{
//			/*
//			 *Key already present in linked list
//			 *Updating the value of already existing key
//			*/
//
//			struct node* element = get_element(list, find_index);
//			element->value = value;
//
//		}
//
//	}
	
////get label and scope and modity the scope of the label in the hash symbols table
void f_updateScopeLabel(char* label, E_scopeLabel scope)
{

}

void f_modifyLabel(char* row, E_scopeLabel scope)
{
	//the row point to the word:entry or:extern
	//note yoou souhuld find space and after him- the label to midify. cut it and
	//send to "updateScopeLabel(char * label,E_scopeLabel scope)"
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
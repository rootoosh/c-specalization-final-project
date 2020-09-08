#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "structures.h"

//hold the size of hash table
int G_symbolsCapacity;

S_symbol* arraySymbol;

void f_initHash(int capacity)
{
	G_symbolsCapacity = capacity;
	hashSymbols = (S_symbol**)malloc(sizeof(S_symbol*) * G_symbolsCapacity);

}

int f_hashCode(char* label)
{
	unsigned int sum = 0;
	size_t j;
	for (j = 0; j < strlen(label); j++)
	{
		sum += pow(label[j], j);
	}
	return sum % G_symbolsCapacity;
}

struct DataItem* search(char* key) {
	//get the hash 
	int hashIndex = f_hashCode(key);

	//move in array until an empty 
	while (hashArray[hashIndex] != NULL) {

		if (hashArray[hashIndex]->key == key)
			return hashArray[hashIndex];

		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex %= G_symbolsCapacity;
	}

	return NULL;
}

//the function get label and type and insert it to the symbols table
void f_insertLabel(char* label, E_typeLabel type, int address)
{
	S_symbol* newSymbol = (S_symbol*)malloc(sizeof(S_symbol));
	newSymbol->address = address;
	newSymbol->label = label;
	newSymbol->type = type;
	newSymbol->next = NULL;
	//get the hash 
	int hashIndex = f_hashCode(label);

 S_symbol* list = (s_symbol*)hashSymbols[hashIndex].head;
	//move with pointer
	S_symbol* pointer = ;
	//move in array until an empty cell
	while (pointer != NULL)
	{
		pointer = pointer->next;
	}

	pointer=newSy
}

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
//
//	//Calculating Load factor
//	n = (1.0 * size) / max;
//	if (n >= 0.75)
//	{
//		//rehashing
//
//		printf("going to rehash\n");
//		rehash();
//
//	}
//
//}

//struct DataItem* delete(struct DataItem* item) {
//	int key = item->key;
//
//	//get the hash 
//	int hashIndex = f_hashCode(key);
//
//	//move in array until an empty
//	while (hashArray[hashIndex] != NULL) {
//
//		if (hashArray[hashIndex]->key == key) {
//			struct DataItem* temp = hashArray[hashIndex];
//
//			//assign a dummy item at deleted position
//			hashArray[hashIndex] = dummyItem;
//			return temp;
//		}
//
//		//go to next cell
//		++hashIndex;
//
//		//wrap around the table
//		hashIndex %= SIZE;
//	}
//
//	return NULL;
//}

//get label and scope and modity the scope of the label in the hash symbols table
void f_updateScopeLabel(char* label, E_scopeLabel scope)
{

}

void f_modifyLabel(char* row, E_scopeLabel scope)
{
	//the row point to the word:entry or:extern
	//note yoou souhuld find space and after him- the label to midify. cut it and
	//send to "updateScopeLabel(char * label,E_scopeLabel scope)"
}

//the function get label and type and insert it to the symbols table
void f_insertLabel(char* label, E_typeLabel labelType,int address)
{
	/*


	ליצור מבנה מתאים של תוית, להכניס בו ערכים: שם כתובת לפי הכתובת IC
	  labelTypeסוג לפי
	  הסקופ הוא לוקאלי
	להכניס לטבלת האש את התוית
	לצורך זה צריך טבלת האש, פונקצית גיבוב וכו'
	צריך להיות מוגדר מראש
	מספר השורות בקובץ
	כי
	*/
}
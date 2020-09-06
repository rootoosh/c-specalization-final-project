#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"
#include "helpers.h"
#include "symbolsHash.h"


//initialize DataNode for .data directive
void f_initializeDataNode(struct nodeD* node, int num)
{

	node->address = DC;
	node->label = NULL;
	node->binaryCode = 1;
	// 1&num -Put the number in binary representation
	node->binaryCode = (node->binaryCode & num);
	node->type = "data";

}
void f_initilzeFirstDataNode(struct nodeD* node, int num)
{
	node->binaryCode = 1;
	// 1&num -Put the number in binary representation
	node->binaryCode = (node->binaryCode & num);
	node->type = "data";
}



//get row which is directive- and manage the data of this row
//row point to 'd' letter of word 'data'
void f_manageData(char* row, S_nodeData* node)
{
	/*
	לקרא מספרים ממחרוזת שהתקבלה ולהכניס אותם ברשימה כל מספר בצומת ולקדם מונה נתונים
	כלומר לקדם dc
	*/
	//temp pointer to the row
	char* ptr;
	//hold the num from the string
	int num;
	struct nodeD* newNode;
	//to know if row shuold countioue or we in the last number
	size_t isLast = 0;
	//to know if we in the first number that shulnt put in the given node and not in newNode
	size_t isFirst = 1;
	//if it is not digit or '+' or '-' continue in the string
	while ((!isdigit(*row)) && (*row != '-') && (*row != '+'))
	{
		row++;
	}
	ptr = row;
	//for all the numbers (between ',')
	while (*row != '\0')
	{
		ptr = strchr(row, ',');
		//if not find ','
		if (ptr == NULL)
		{
			isLast = 1;
		}
		// when find number-convert it from string to integer
		//and place it in num variable 
		*ptr = '\0';
		num = atoi(row);
		//if it is the first number
		if (isFirst)
		{
			f_initilzeFirstDataNode(node, num);
			isFirst = 0;
		}
		else
		{
			newNode = (struct nodeD*)malloc(sizeof(struct nodeD));
			//connect the new node to the llist
			tailDataList->next = newNode;
			newNode->next = NULL;
			tailDataList = newNode;
			//initialize the new node in the S_nodeData struct
			f_initializeDataNode(newNode, num);
			//inc the data counter
			DC++;
		}
		if (!isLast)
		{
			//inc the ptr to point after the '/0'
			ptr++;
		}
		//row point after the '/0' to continue search another number
		row = ptr;
	}
}

//initialize DataNode for .string directive
void f_initializeStringNode(int ch, S_nodeData* node)
{
	node->address = DC;
	node->binaryCode = 1;
	//1&ch-Put the assci code of the sign in binary representation
	node->binaryCode = (node->binaryCode & ch);
	node->label = NULL;
	node->type = NULL;
}

//get row which is directive- and manage the data of this row
void f_manageString(char* row, S_nodeData* node)
{
	/*
	לקרא תוים ממחרוזת ולהכניס אותם ברשימה כל תו בצומת ולקדם מונה נתונים
	כלומר לקדם dc
		*/
		//new node decalartion
	struct nodeD* newNode;

	//look for the open quotation marks
	row = strchr(row, '"');
	row++;
	//ch- hold the assci code of the first sign in the string
	int ch = *row;
	//first char in the datastring
	node->binaryCode = 1;
	//1&ch-Put the assci code of the sign in binary representation
	node->binaryCode = (node->binaryCode & ch);
	//inc row to point to the next sign if there is each one
	row++;
	//until find the close quattion mark
	while (*row != '"')
	{
		//create new node
		newNode = (struct nodeD*)malloc(sizeof(struct nodeD));
		//connect the new node to the llist
		tailDataList->next = newNode;
		newNode->next = NULL;
		tailDataList = newNode;
		//ch- hold the assci code of the sign
		ch = *row;
		//initialize the new node in the S_nodeData struct
		f_initializeStringNode(ch, newNode);
		//inc the data counter
		DC++;
		row++;

	}
	//treat the node of the \0 char.
	// create new node
	newNode = (S_nodeData*)malloc(sizeof(S_nodeData));
	//connect the new node to the llist
	tailDataList->next = newNode;
	newNode->next = NULL;
	tailDataList = newNode;
	//initialize the new node in the S_nodeData struct
	f_initializeStringNode(0, newNode);
	//inc the data counter
	DC++;
}

void f_manageDirective(char* row, char* isLabel)
{
	struct nodeD* newNode;
	//first check if is label here
	// if has- send to function:insertlabel
	if (isLabel != NULL)
	{
		f_insertLabel(isLabel, data);
		//row point after ther label
		row += strlen(isLabel) + 1;
	}

	//ignore the spaces and go to letters- that must represent .data or .string .entry .extern
	row = strchr(row, '.');
	row++;

	//extern or entry
	if (*(row) == 'e')
	{
		if ((*(row + 1) == 'x'))
		{
			f_modifyLabel(row, external);
		}
		// entry
		else if (*(row + 1) == 'n')
		{
			f_modifyLabel(row, entry);
		}
	}
	else
	{
		//the new node struct
		newNode = (struct nodeD*)malloc(sizeof(struct nodeD));
		//connect the new node to the llist
		newNode->next = NULL;
		tailDataList->next = newNode;
		tailDataList = newNode;
		//copy the address to the node data struct from DC
		newNode->address = DC;
		//inc the Data counter
		DC++;
		//put the label in the node data struct
		newNode->label = isLabel;
		newNode->binaryCode = 0;
		//data
		if (*(row) == 'd')
		{
			newNode->type = "data";
			//note row point to data without '.'
			f_manageData(row, newNode);
		}
		//string 
		else
		{
			newNode->type = "string";
			//note row point to data without '.'
			f_manageString(row, newNode);
		}

	}


}
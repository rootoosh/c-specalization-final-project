#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "structures.h"
#include "commandsData.h"
#include "helpers.h"
#include "symbolsHash.h"

//get string and check is it register or label operand. in the nameOp put the name nice with \n
int f_checkRegistOrLabel(char* row, char** nameOp)
{
	//register =0. laebl =1
	int resultType = 0;
	char c;
	*nameOp = row;
	//register must start with r + number + white space or ','
	if (*row == 'r')
	{
		c = *(row + 1);
		//check is num between 0 to 7
		if (isdigit(c) )
		{
			//after the register operand shuold be: one of:", \t\n\0"
			switch (*(row + 2))
			{
			case ',':
			case ' ':
			case '\t':
			case '\0':
			case '\n':
			{
				//hold only the num of register
				(*nameOp) = &c;
				return resultType;
			}
			break;

			default:resultType = 1;
				break;
			}
		}
	}
	//find the end of the operand by using temp pointer
	char* temp = row;
	//look for a char that repersnt end of label
	while ((*temp) && (*temp != ',') && (*temp != ' ') && (*temp != '\t') && (*temp != '\n'))
	{
		temp++;
	}
	*temp = '\0';
	return resultType;
}

//row point on the char just after the command
void f_instrct2operand(char* row, S_nodeInstruction* newNode)
{
	/*

	פונקציה זו אמורה למלא בצומת החדש את שדות שני האופרנדים ,
	וכן את השדה קוד בינרי- בביטים הקשורים לשני האופרנדים

	צריך להפריד את האופרנדים למחרוזות
	לשלוח לפונקציות המתיאמות לשיטות המיעון
	להפוך מספרים ממחרוזות לאינטים ולכתוב קוד אסקי שלהם
	כוו'
	*/
}
void f_putBinaryCode(int numCommand, S_nodeInstruction* node, int lastIndex)
{
	//the mask is type of node because i need int with 16 bits only
	struct nodeI* mask = (struct nodeI*)malloc(sizeof(struct nodeI));
	mask->binaryCode = numCommand;
	mask->binaryCode << (lastIndex - 2);
	node->binaryCode |= mask->binaryCode;
}

//find # mean Instant residence method
void f_manageInstandResidence(char* row, S_nodeInstruction* newNode)
{
	/*
	1. לכתוב שיטת מעון בבינראי קוד של הצומת החדש - צריך להשתמש במסכה כדי לכתוב את זה בסיביות המתאימות
	כלומר בסיביו ת של שיטת מעון האופרנד הראשון
	2. לכתוב בסיביות של רגיטסטר אופרנד ראשון אפסים
	3. להוסיף צומת חדש שבבינרי קוד שלו יהיה כתוב את המספר שבמחרוזת שהפונקציה מקבלת.
	את הצומת הזו לחבר לצומת שקבלנו
	ובכתובת שלו יהיה IC מקוםד
	4. לקדם את מונה הכתובות של ההוראות IC
	//but note not to put anything in the firstOperand and Second operand parameters
	*/
}

void f_manageRelativeResidence(char * row, S_nodeInstruction* newNode)
{}

//row point on the char just after the command
void f_instrct1operand(char* row, S_nodeInstruction* newNode)
{

	//it is register(0) or label(1).return by pointer the name of label/ num of register
	char* nameOp;
	
	size_t typeOperand;

	/*
	פונקציה זו אמורה למלא בצומת החדש את השדה אופרנד שני,
	וכן את השדה קוד בינרי- בביטים הקשורים לאופרנד שני
	לא לעשות דברים מיותרים רק לפי מה שהגיוני  שיהיה
	לדוגמא אופרנד אחד לא יכול להיות מעון ישיר אין לבדוק זאת
	*/
	//ignore the spaces and go to letters- that must represent command
	row = f_ingnoreSpaces(row);
	//if it is relative residence - shuld manage with the binary code to put it,
	//and read the label after the "*" to the next node in the listInstruction. also inc IC
	if (*row == '*')
	{
		//the row+1 point after the '*'. 
		f_manageRelativeResidence(row + 1, newNode);
	}
	//indirect residence
	else if (*row == '@')
	{
		//the row+1 mean point just after the 'a'
		typeOperand = f_checkRegistOrLabel(row + 1, &nameOp);
		//if is regsiter
		if (!typeOperand)
		{
			//put the residence method code(indiercet register=5) in the 3-5 bit palce
			f_putBinaryCode(5, newNode, 5);
			//put the register num in the 0-2 bit place
			f_putBinaryCode(atoi(nameOp), newNode, 2);
		}
		//if is label
		else
		{
			//put the residence method code(indiercet =2) in the 3-5 bit palce
			f_putBinaryCode(2, newNode, 5);
			newNode->secondOperand = nameOp;
		}
	}
	else
	{
		typeOperand= f_checkRegistOrLabel(row + 1, &nameOp);
		//if is register
		if (!typeOperand)
		{
			//put the residence method code(direcct=4) in the 3-5 bit palce
			f_putBinaryCode(4, newNode, 5);
			//put the register num in the 0-2 bit place
			f_putBinaryCode(atoi(nameOp),newNode, 2);
		}
		else
		{

		}
	}


}




//deal with the instruction list,
void f_manamgeInstruction(char* row, char* isLabel)
{
	//the new node struct
	struct nodeI* newNode = (struct nodeI*)malloc(sizeof(struct nodeI));
	//connect the new node to the llist
	newNode->next = NULL;
	tailInstrucionList->next = newNode;
	tailInstrucionList = newNode;
	newNode->binaryCode = 0;
	//copy the address to the node istruction struct from IC
	newNode->address = IC;
	//inc the instrucion counter
	IC++;
	//first check if is label here
	// if has- send to function:insertlabel
	if (isLabel != NULL)
	{
		f_insertLabel(isLabel, instruction);
		//put the label in the node instruction struct
		newNode->label = isLabel;
		//row point after ther label
		row += strlen(isLabel) + 1;
	}
	//ignore the spaces and go to letters- that must represent command
	row = f_ingnoreSpaces(row);
	//copy the command name to the node instruction struct
	strncpy(newNode->command, row, 3);
	//put the command code in the binary code
	int numCommand = f_getNumCommand(newNode->command);
	f_putBinaryCode(numCommand, newNode, 15);
	//row point after the command
	row += 3;
	//initilize first and second operand
	newNode->firstOperand = NULL;
	newNode->secondOperand = NULL;

	//send to suitable function -denpend on the number of operands
	int numOperands = f_getNumOperandsByCommandName(newNode->command);
	if (numOperands == 1)
	{
		f_instrct1operand(row, newNode);
	}
	else if (numOperands == 2)
	{
		f_instrct2operand(row, newNode);
	}
	/*
	VVV int adress;
	VVV char* label;
	VVV char* command;
	char* firstOperand;
	char* secondOperand;
	 binaryCode:
	destRegister : 3;
	destResident : 3;
	sourceRegister : 3;
	sourecResident : 3;
	command : 4;
	VVVVVV nodeI* next;*/
}
#include <string.h>
#include <stdio.h>
#include "structures.h"
#include "validation.h"
#include "commandsData.h"


//row point on the char just after the command
void f_instrct2operand(char* row, S_nodeInstruction* newNode)
{
	/*
	צריך להפריד את האופרנדים למחרוזות
	לשלוח לפונקציות המתיאמות לשיטות המיעון
	להפוך מספרים ממחרוזות לאינטים ולכתוב קוד אסקי שלהם
	כוו'
	*/
}
//row point on the char just after the command
void f_instrct1operand(char* row, S_nodeInstruction* newNode)
{
	/*
	לא לעשות דברים מיותרים רק לפי מה שהגיוני  שיהיה
	לדוגמא אופרנד אחד לא יכול להיות מעון ישיר אין לבדוק זאת
	*/
}


//find # mean Instant residence method
f_manageInstandResidence(char* row, S_nodeInstruction* newNode)
{
	/*
	1. לכתוב שיטת מעון בבינראי קוד של הצומת החדש - צריך להשתמש במסכה כדי לכתוב את זה בסיביות המתאימות
	כלומר בסיביו ת של שיטת מעון האופרנד הראשון
	2. לכתוב בסיביות של רגיטסטר אופרנד ראשון אפסים
	3. להוסיף צומת חדש שבבינרי קוד שלו יהיה כתוב את המספר שבמחרוזת שהפונקציה מקבלת.
	את הצומת הזו לחבר לצומת שקבלנו
	ובכתובת שלו יהיה IC מקוםד
	4. לקדם את מונה הכתובות של ההוראות IC
	*/
}

//the function get label and type and insert it to the symbols table
void f_insertLabel(char* label, E_typeLabel labelType)
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

//deal with the instruction list,
void f_manamgeInstruction(char* row, char* isLabel)
{
	//the new node struct
	S_nodeInstruction* newNode = (S_nodeInstruction*)malloc(sizeof(S_nodeInstruction));
	//connect the new node to the llist
	newNode->next = NULL;
	tailInstrucionList->next = newNode;
	tailInstrucionList = newNode;

	//copy the address to the node istruction struct from IC
	newNode->adress = IC;

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
	while ((*row == ' ') || (*row == '\t'))
	{
		row++;
	}
	//copy the command name to the node instruction struct
	strncpy(newNode->command, row, 3);
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

void f_manageData(char* row, char* isLabel)
{
	if (isLabel != NULL)
	{
		f_insertLabel(isLabel, data);
	}


}

//function to read row, check is valid, 
//put in the suitable structure
void f_convertToStructure(FILE* inputFile)
{
	//has label in that row or not
	char* isLabelInRow = NULL;
	//number of row in the input file
	int rowNum = 0;
	int len = 0;
	size_t rowLength;
	char* row;
	//is had error(0) in the row or:
	 //indictae is it have label(1), is it insturction(2) or data(4).
	int status;
	//while there are rows in the file
	while (len = getline(&row, &rowLength, inputFile) != 0)
	{
		//print error of too many characters
		if (len > 80)
		{
			printf("in row %d too many charcters in row", rowNum);
		}
		else
		{
			//if getline success to read from the file
			if (len != -1)
			{
				//chcek if the row is valid, and is it data or instructio
				status = f_checkIsValidRow(row, rowNum, &isLabelInRow);
				//status =1 mean is instrucion
				if (status == 1)
				{
					f_manamgeInstruction(row, isLabelInRow);
					//inc the instrucion counter
					IC++;
				}
				//status =2 mean is data instruction
				if (status == 2)
				{
					f_manageData(row, isLabelInRow);
					//inc the data counter
					DC++;
				}
			}
		}
		//inc the row number
		rowNum++;
	}
}





#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "structures.h"
#include "validation.h"
#include "commandsData.h"

//get string and check is it register or label operand. in the nameOp put the name nice with \n
int f_checkRegistOrLabel(char* row, char** nameOp)
{
	int resultType=0;
	char c;
	size_t num;
	*nameOp = row;
	//register must start with r + number + white space or ','
	if (*row == 'r')
	{
		c = *(row + 1);
		num = atoi(c);
		//check is num between 0 to 7
		if (num <= 7)
		{
			//after the register operand shuold be: one of:", \t\n"
			switch (*(row + 2))
			{
				case ',':
				case ' ':
				case '\t':
				case '\n':
				{
					//for register need to put /n in the end after r_num
					*((*nameOp) + 2) = '\0';
					//hold only the num of register
					(*nameOp)++;
					return resultType;
				}
					break;

				default:resultType = 1;
				break;
			}
		}
	}
	//find the end of the operand by using temp pointer
	char* temp=row;
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

//row point on the char just after the command
void f_instrct1operand(char* row, S_nodeInstruction* newNode)
{

	/*
	פונקציה זו אמורה למלא בצומת החדש את השדה אופרנד שני,
	וכן את השדה קוד בינרי- בביטים הקשורים לאופרנד שני
	לא לעשות דברים מיותרים רק לפי מה שהגיוני  שיהיה
	לדוגמא אופרנד אחד לא יכול להיות מעון ישיר אין לבדוק זאת
	*/
	//ignore the spaces and go to letters- that must represent command
	while ((*row == ' ') || (*row == '\t'))
	{
		row++;
	}
	//if it is relative residence - shuld manage with the binary code to put it,
	//and read the label after the "*" to the next node in the listInstruction. also inc IC
	if (*row == '*')
	{
		//the row+1 point after the '*'. 
		f_manageRelativeResidence(row + 1, newNode);
	}
	//indirect residence
	if (*row == '@')
	{
		//it is register(0) or label(1).return by pointer the name of label/ num of register
		char* nameOp;
		//the row+1 mean point just after the 'a'
		size_t typeOperand=f_checkRegistOrLabel(row + 1, &nameOp);
		//if is regsiter
		if (!typeOperand)
		{
			f_putBinaryCode(5, newNode, 5);
			f_putBinaryCode(atoi(nameOp), newNode, 2);
		}
		//if is label
		else
		{

		}
	}
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
	*/
}

//get label and scope and modity the scope of the label in the hash symbols table
void f_updateScopeLabel(char* label, E_scopeLabel scope)
{

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

void f_putBinaryCode(int numCommand, S_nodeInstruction* node, size_t lastIndex)
{
	//the mask is type of node because i need int with 16 bits only
	S_nodeInstruction* mask = (S_nodeInstruction*)malloc(sizeof(S_nodeInstruction*));
	mask->binaryCode = numCommand;
	mask->binaryCode << (lastIndex - 2);
	node->binaryCode += mask->binaryCode;
}
//deal with the instruction list,
void f_manamgeInstruction(char* row, char* isLabel)
{
	//the new node struct
	S_nodeInstruction* newNode = (S_nodeInstruction*)malloc(sizeof(S_nodeInstruction*));
	//connect the new node to the llist
	newNode->next = NULL;
	tailInstrucionList->next = newNode;
	tailInstrucionList = newNode;
	newNode->binaryCode = 0;
	//copy the address to the node istruction struct from IC
	newNode->adress = IC;
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
	while ((*row == ' ') || (*row == '\t'))
	{
		row++;
	}
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

void f_modifyLabel(char* row, E_scopeLabel scope)
{
	//the row point to the word:entry or:extern
	//note yoou souhuld find space and after him- the label to midify. cut it and
	//send to "updateScopeLabel(char * label,E_scopeLabel scope)"
}

<<<<<<< HEAD
void f_manageData(char* row, S_nodeData* newNode)
=======
//initialize DataNode for .data directive
void f_initializeDataNode(S_nodeData* node, int num)
{

	node->adress = DC;
	node->label = NULL;
	node->binaryCode = 1;
	// 1&num -Put the number in binary representation
	node->binaryCode = (node->binaryCode & num);
	node->type = NULL;

}

//get row which is directive- and manage the data of this row
void f_manageData(char* row, S_nodeData* node)
>>>>>>> 50d123b439a9860abe33c4776e8f9dadeab74bd4
{
	/*
	לקרא מספרים ממחרוזת שהתקבלה ולהכניס אותם ברשימה כל מספר בצומת ולקדם מונה נתונים
	כלומר לקדם dc
		*/
		//temp pointer to the row
	char* ptr;
	//hold the num from the string
	int num;
	//while different from '/0' -this while search number in string
	while (*row)
	{
		//if it is not digit or '+' or '-' continue in the string
		if ((!isdigit(*row)) && (*row != '-') && (*row != '+'))
		{
			row++;
		}
		else
		{ // when find number-convert it from string to integer
			//and place it in num variable 
			ptr = row;
			ptr = strchr(row, ',');
			//if  find ','
			if (ptr != NULL)
			{
				*ptr = '/0';
				num = atoi(row);
				//the new node struct
				S_nodeData* newNode = (S_nodeData*)malloc(sizeof(S_nodeData));
				//connect the new node to the llist
				node->next = newNode;
				newNode->next = NULL;
				tailDataList = newNode;
				//initialize the new node in the S_nodeData struct
				f_initializeDataNode(newNode, num);
				//inc the data counter
				DC++;
				//inc the ptr to point after the '/0'
				ptr++;
				//row point after the '/0' to continue search another number
				row = ptr;
			}
			else
			{
				break;
			}
		}
	}

	//for the last number in the data
	num = atoi(row);
	//the new node struct
	S_nodeData* newNode = (S_nodeData*)malloc(sizeof(S_nodeData));
	//connect the new node to the llist
	node->next = newNode;
	newNode->next = NULL;
	tailDataList = newNode;
	//initialize the new node in the S_nodeData struct
	f_initializeDataNode(newNode, num);
	//inc the data counter
	DC++;
}

//initialize DataNode for .string directive
void f_initializeStringNode(int ch, S_nodeData* node)
{
	node->adress = DC;
	node->binaryCode = 1;
	//1&ch-Put the assci code of the sign in binary representation
	node->binaryCode = (node->binaryCode & 1);
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
		//row pointer after the word "string" in the directive sentense
	row += 6;
	//while there is no sign inc the row pointer until find sign
	while ((*row) == ' ' || (*row) == '\t')
	{
		row++;
	}
	//ch- hold the assci code of the first sign in the string
	int ch = *row;
	node->binaryCode = 1;
	//1&ch-Put the assci code of the sign in binary representation
	node->binaryCode = (node->binaryCode & ch);
	//inc row to point to the next sign if there is each one
	row++;
	//while different from '/0' -this while search sign in string
	while (*row)
	{
		//create new node
		S_nodeData* newNode = (S_nodeData*)malloc(sizeof(S_nodeData));
		//connect the new node to the llist
		node->next = newNode;
		newNode->next = NULL;
		tailDataList = newNode;
		//if after the sign there is no other sign put '\0' and finish
		if ((*row) == ' ' || (*row) == '\t')
		{
			//initialize the new node in the S_nodeData struct
			f_initializeStringNode(0, newNode);
			//inc the data counter
			DC++;
			break;
		}
		else {
			//ch- hold the assci code of the sign
			ch = *row;
			//initialize the new node in the S_nodeData struct
			f_initializeStringNode(ch, newNode);
			//inc the data counter
			DC++;
			row++;
		}

	}

}

void f_manageDirective(char* row, char* isLabel)
{
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
		S_nodeData* newNode = (S_nodeData*)malloc(sizeof(S_nodeData*));
		//connect the new node to the llist
		newNode->next = NULL;
		tailDataList->next = newNode;
		tailDataList = newNode;

		//copy the address to the node data struct from DC
		newNode->adress = DC;
		//inc the Data counter
		DC++;
		//put the label in the node data struct
		newNode->label = isLabel;

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


	/*
	VV   int adress;
	VV  char* label;
	//.data or .string
	char* type;
	//represent the content data in binary
	//should be node for every piece of data
	unsigned int binaryCode : 16;
	nodeD* next
	*/



}

//function to read row, check is valid, 
//put in the suitable structure
void f_assembleFirstPass(FILE* inputFile)
{
	//has label in that row or not
	char* isLabelInRow = NULL;
	//number of row in the input file
	int rowNum = 0;
	int len = 0;
	size_t rowLength;
	char* row;
	//is had error(0) in the row or:
	 // is it insturction(1) or data(2).
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
				}
				//status =2 mean is data instruction
				if (status == 2)
				{
					f_manageDirective(row, isLabelInRow);
				}
			}
		}
		//inc the row number
		rowNum++;
	}
}

//count rows in input file to know allocate the hash as need
//should fix it not to count rows without label
int CountRowsInFile(FILE* inputFile)
{
	char c;
	int count = 0;
	// Extract characters from file and store in character c
	for (c = getc(inputFile); c != EOF; c = getc(inputFile))
	{
		if (c == '\n') // Increment count if this character is newline
		{
			count++;
		}
	}
	return count - 1;
}





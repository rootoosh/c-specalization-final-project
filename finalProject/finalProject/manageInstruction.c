#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "commandsData.h"
#include "symbolsHash.h"

extern int IC;
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
		if (isdigit(c) && (c-'0') <= 7)
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
	//it is register(0) or label(1).return by pointer the name of label/ num of register
	char* nameOp;

	size_t typeOperand;

	row = f_ingnoreSpaces(row);
	//treat first operand:
	{
		if (*row == '#')
		{
			row++;
			//note: can add node and change the newNode pointer
			f_manageInstandResidence(row, newNode, 1);
		}
		//indirect
		else if (*row == '@')
		{
			//the row+1 mean point just after the '@'
			typeOperand = f_checkRegistOrLabel(row + 1, &nameOp);
			//if is regsiter
			if (!typeOperand)
			{
				//put the residence method code(indiercet register=5) in the 9-11 bit palce
				f_putBinaryCode(5, newNode, 11);
				//put the register num in the 8-6 bit place
				f_putBinaryCode(atoi(nameOp), newNode, 8);
			}
			//if is label
			else
			{
				//put the residence method code(indiercet =1) in the 9-11 bit palce
				f_putBinaryCode(2, newNode, 11);
				f_putLabelInNode(nameOp, newNode, 1);
			}
		}
		//direct
		else
		{
			typeOperand = f_checkRegistOrLabel(row + 1, &nameOp);
			//if is register
			if (!typeOperand)
			{
				//put the residence method code(direcct=4) in the 9-11 bit palce
				f_putBinaryCode(4, newNode, 11);
				//put the register num in the 0-2 bit place
				f_putBinaryCode(atoi(nameOp), newNode, 8);
			}
			else
			{
				//put the residence method code(direcct label=1) in the 9-11 bit palce
				f_putLabelInNode(row, newNode, 1);
				f_putBinaryCode(1, newNode, 11);
			}
		}
	}
	//treat second operand
	{
		//find ',' and send what after to the function that will deal with it

		row = strchr(row, ',');
		row++;
		row = f_ingnoreSpaces(row);
		//for cmp it can be instant residence in the second operand!
		if (*row == '#')
		{
			row++;
			//note: can add node and change the newNode pointer
			f_manageInstandResidence(row, newNode, 2);
		}
		else
		{
			f_instrct1operand(row, newNode);
		}
	}
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
void f_manageInstandResidence(char* row, S_nodeInstruction* node, int serialOperand)
{
	//should get the num from the char and put the ascii kod in the next node
	char* endNumber;
	int number;
	endNumber = strchr(row, ',');
	*endNumber = '\0';
	number = atoi(row);
	if (serialOperand == 1)
	{
		//הדלק סיביות אופרנד ראשון 9-11בשיטת מעון 0
		f_putBinaryCode(0, node, 11);
	}
	else
	{
		//הדלק סיביות אופרנד שני 3-5בשיטת מעון 0
		f_putBinaryCode(0, node, 5);
	}

	//new node for the number
	struct nodeI* newNode = f_insertInstruction();
	newNode->state = 'a';
	node->next = newNode;
	newNode->binaryCode = 1;
	// 1&num -Put the number in binary representation
	newNode->binaryCode = (newNode->binaryCode & number);
	//inc the instrucion count
	IC++;

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

void f_putLabelInNode(char* label, S_nodeInstruction* node, int serialOperand)
{
	char* endLabel = label;
	int numChars;
	while ((*endLabel != ' ') && (*endLabel != '\t') &&
		(*endLabel != '\0') && (*endLabel != '\n') && (*endLabel != ','))
	{
		endLabel++;
	}
	numChars = endLabel - label;
	if (serialOperand == 2)
	{
		node->secondOperand = (char*)malloc(sizeof(char) * numChars + 1);
		node->secondOperand[numChars] = '\n';
		strncpy(node->secondOperand, label, numChars);
	}
	else if (serialOperand == 1)
	{
		node->firstOperand = (char*)malloc(sizeof(char) * numChars + 1);
		node->firstOperand[numChars] = '\n';
		strncpy(node->firstOperand, label, numChars);
	}
	////prepare node for the next passion to fill with the address of the label
	//struct nodeI* newNode = (struct nodeI*)malloc(sizeof(struct nodeI));
	////connect the new node to the llist
	//newNode->next = NULL;
	//node->next = newNode;
	//tailInstrucionList = newNode;
	//newNode->binaryCode = 0;
	////copy the address to the node istruction struct from IC
	//newNode->address = IC;

	//inc the instrucion count
	IC++;

}
//את הפונקציה הזו כתבתי כשתכננתי לעשות נורא מסודר אבל בסוף לא. לא נורא...
//void f_manageLabelDirectiveResidence(char* label, S_nodeInstruction* newNode,int serialOperand)
//{
// f_putLabelInNode(label, newNode,serialOperand);
// //put the residence method code(diercet label=) in the 3-5 bit palce
// f_putBinaryCode(1, newNode, 5);
//
//}
//*
void f_manageRelativeResidence(char* row, S_nodeInstruction* newNode)
{
	f_putLabelInNode(row, newNode, 2);
	//put the residence method code(relative=) in the 3-5 bit palce
	f_putBinaryCode(3, newNode, 5);
}

//row point on the char just after the command
//or just after the , of the first operand
void f_instrct1operand(char* row, S_nodeInstruction* newNode)
{
	//it is register(0) or label(1).return by pointer the name of label/ num of register
	char* nameOp;

	size_t typeOperand;

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
		//the row+1 mean point just after the '@'
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
			f_putLabelInNode(row, newNode, 2);
		}
	}
	//direct
	else
	{
		typeOperand = f_checkRegistOrLabel(row + 1, &nameOp);
		//if is register
		if (!typeOperand)
		{
			//put the residence method code(direcct=4) in the 3-5 bit palce
			f_putBinaryCode(4, newNode, 5);
			//put the register num in the 0-2 bit place
			f_putBinaryCode(atoi(nameOp), newNode, 2);
		}
		else
		{
			//put the residence method code(direcct label=2) in the 3-5 bit palce
			f_putLabelInNode(row, newNode, 2);
			f_putBinaryCode(1, newNode, 5);
		}
	}
}

//deal with the instruction list,
void f_manamgeInstruction(char* row, char* isLabel)
{
	//the new node struct
	struct nodeI* newNode = f_insertInstruction();
	//inc the instrucion counter
	IC++;
	//first check if is label here
	// if has- send to function:insertlabel
	if (isLabel != NULL)
	{
		f_insertLabel(isLabel, instruction, newNode->address);
		//put the label in the node instruction struct
		newNode->label = isLabel;
		//row point after ther label
		row += strlen(isLabel) + 1;
	}
	//ignore the spaces and go to letters- that must represent command
	row = f_ingnoreSpaces(row);
	//copy the command name to the node instruction struct
	strncpy(newNode->command, row, 3);
	//row point after the command
	row += 3;
	//the state of the node is a- absulute. because it is command
	newNode->state = 'a';
	//put the command code in the binary code
	int numCommand = f_getNumCommand(newNode->command);
	f_putBinaryCode(numCommand, newNode, 15);
	//send to suitable function -denpend on the number of operands
	int numOperands = f_getNumOperandsByCommandIndex(numCommand);
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



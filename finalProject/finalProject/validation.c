
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "commandsData.h"
#include "structures.h"


int  hasError = 0;
int f_checkIsValidCommand(char* row, int numRow)
{
	int isValidComand;
	// hold the command-size 4 (also for the null)
	char command[4];
	strncpy(command, row, 3);
	command[3] = '\0';
	//check if the command is valid
	isValidComand = f_getNumCommand(command);
	//if the command not valid = -1
	if (isValidComand == -1)
	{
		printf("Error, in row %d, not valid statment this command not exists");
	}
	//return the num of the command or -1 if not valid
	return isValidComand;
}
//if the number valid and has "," return 1 if not have "," return 2
//else if not valid return 0
int f_checkIsValidNum(char* row, int numRow)
{
	//while is valid continue in row
	while (isdigit(*row))
	{
		row++;
	}
	//if has '.' not valid
	if (*row == '.')
	{
		printf("Error!, in row %d not valid statment,must be integer number", numRow);
		return 0;
	}
	if (*row == ' ' || *row == '\t')
	{
		row = f_ingnoreSpaces(row);
		//if after the number has only white space is valid 
		if (*row == ',')
			return 1;
		if (*row == '\n')
			return 2;
	}
	else {

		printf("Error!, in row %d not valid statment", numRow);
		return 0;
	}
}
//if the data number valid return 1
//else return 0
int f_checkIsValidDataNumbers(char* row, int numRow)
{
	int isValidnum;
	if (*row == '-' || *row == '+')
	{
		row++;
	}

	while (isValidnum = f_checkIsValidNum(row, numRow) == 1)
	{
		row = strchr(row, ',');
		row++;
		row = f_ingnoreSpaces(row);
	}
	if (isValidnum == 2)
	{
		return 1;
	}
	if (!isValidnum)
	{
		return 0;
	}
	else {

		printf("Error!, in row %d, not valid data of directive statment", numRow);
		return   0;
	}
}

//if the label is valid return the name of the lable (or row)
//else return null
char* f_checkIsValidLabel(char* row, int numRow)
{
	row = f_ingnoreSpaces(row);
	//help pointer in row string
	char* ptr = row;
	int count = 1;

	if (!isalpha(*ptr))
	{
		return NULL;
	}
	while ((isalpha(*ptr) || isdigit(*ptr)) && (*ptr))
	{
		if (count > 30)
		{
			printf("Error!, in row %d the lable name length more then 30, not valid!", numRow);
			return NULL;
		}
		count++;
		ptr++;
	}
	if (*ptr == '\0')
	{
		return row;
	}
	ptr = f_ingnoreSpaces(ptr);
	if (*ptr == '\n')
	{
		return row;
	}
	else
	{
		printf("Error!, in row %d the lable  not valid!", numRow);
	}
	return NULL;
}

int f_checkIsValidString(char* row, int numRow)
{
	if (*row == '"')
	{
		row++;
		row = strchr(row, '"');
		if (row != NULL)
		{
			row = f_ingnoreSpaces(row);
			if (*row == '\n')
			{
				return 1;
			}
			else {
				printf("Error,in row %d, not valid string characters after the close  quotation marks ", numRow);
			}
		}
		else
		{
			printf("Error,in row %d, no close quotation marks", numRow);
		}
	}
	else
	{
		printf("Error,in row %d, no open quotation marks", numRow);
	}
	return 0;
}

//check if the directive ststment is valid return 1 else return 0
//row point after the  .
int f_checkIsValidDirective(char* row, int numRow)
{
	int isValid = 0;
	//help pointer in row
	char* ptr;
	//hold the result of compare between 2 string
	int cmp;

	//ptr point to the space after the .
	ptr = strchr(row, ' ');
	if (ptr == NULL)
	{
		printf("Error!, in row %d , not valid statment there is no spaces between the data", numRow);
	}
	else
	{
		if (*row == 'd')
		{
			*ptr = '\0';
			cmp = strcmp("data", row);
			*ptr = ' ';
			//if the string is not equal
			if (cmp)
			{
				printf("Error!, in row %d , not valid directive statment", numRow);
			}
			//if the string is data
			else if (!cmp)
			{
				row = ptr + 1;
				//row point after the white spaces
				row = f_ingnoreSpaces(row);
				isValid = f_checkIsValidDataNumbers(row, numRow);
			}

		}
		if (*row == 's')
		{
			*ptr = '\0';
			cmp = strcmp("string", row);
			*ptr = ' ';
			//if the string is not equal
			if (cmp)
			{
				printf("Error!, in row %d , not valid directive statment", numRow);
			}
			//if the string is data
			else if (!cmp)
			{
				row = ptr + 1;
				//row point after the white spaces
				row = f_ingnoreSpaces(row);
				isValid = f_checkIsValidString(row, numRow);
			}

		}
		if (*row == 'e')
		{
			*ptr = '\0';
			cmp = strcmp("entry", row);
			*ptr = ' ';
			if (!cmp)
			{
				row = ptr + 1;
				//row point after the white spaces
				row = f_ingnoreSpaces(row);
				if (f_checkIsValidLabel != NULL)
					isValid = 1;
			}
			else
			{
				*ptr = '\0';
				cmp = strcmp("extern", row);
				*ptr = ' ';
				if (!cmp)
				{
					row = ptr + 1;
					//row point after the white spaces
					row = f_ingnoreSpaces(row);
					if (f_checkIsValidLabel != NULL)
						isValid = 1;
				}
			}
			//if the string is not equal
			if (cmp)
			{
				printf("Error!, in row %d , not valid directive statment", numRow);
			}


		}
	}
	return isValid;
}
//note here is have row++
//check is valid instrand resident method (#)=0
int f_checkIsValidInstantR(char** pointoRow, int numRow, int numOperand)
{
	int isValidNum;
	char* row = *pointoRow;
	row++;
	//if after the # there is valid sign
	if (*row == '-' || *row == '+' || isdigit(*row))
	{
		// check if the number is valid
		isValidNum = f_checkIsValidNum(row + 1, numRow);
		if (isValidNum == 0)
		{
			return 0;
		}
		else if (isValidNum == numOperand == 1)
		{
			row = strchr(row, ',');
			row++;
			*pointoRow = row;
			return 1;
		}
		else if (isValidNum == numOperand == 2)
		{
			return 1;
		}
	}
	return 0;
}//check direct and indirect residence for register or label(4 methods)
int f_checkIsValidDirectInDirectR(char* row, int numOperand, int numRow)
{
	char* label;
	if (*row == '@')
	{
		row++;
	}
	char c;
	//can be register or label
	if (*row == 'r')
	{
		c = *(row + 1);
		//check is num between 0 to 7
		if (isdigit(c) && (c - '0') <= 7)
		{
			if (numOperand == 2)
			{
				//after the register operand shuold be: one of:", \t\n\0"
				switch (*(row + 2))
				{
				case ' ':
				case '\t':
				case '\0':
				case '\n':
				{
					return 1;
				}
				break;
				default:break;
				}
			}
			else
			{
				//after the register operand shuold be: one of:", \t\n\0"
				switch (*(row + 2))
				{
				case ' ':
				case '\t':
				case ',':
				{
					return 1;
				}
				break;
				default:break;
				}
			}

		}
	}
	if (numOperand == 1)
	{
		label = strchr(row, ',');
		if (label == NULL)
		{
			printf("problem is the statemnt in line %d no comma between the operand", numRow);
		}
		else
		{
			*label = '/0';
			if (f_checkIsValidLabel(row, numRow) != NULL)
			{
				*label = ',';
				return 1;
			}
		}
	}
	//two operand
	else if (f_checkIsValidLabel(row, numRow) != NULL)
	{
		return 1;
	}
	return 0;
}

//check if instruction valid return 1 if valid else 0
int f_checkIsValidInstruction(char* row, int numRow)
{
	int numOfOperands;
	int numCommand;
	numCommand = f_checkIsValidCommand(row, numRow);
	if (numCommand == -1)
		return 0;
	//row point just after the command
	row += 3;
	//command with no operands are: 14, 15
	if (numCommand >= 14)
	{
		return 1;
	}
	if (*row != ' ' || *row != '\t')
	{
		printf("Error!, in row %d, must have spasce near the command", numRow);
	}
	row = f_ingnoreSpaces(row);
	//for the command "lea" can be only label in the first opernad
	if (numCommand == 6)
	{
		if (f_checkIsValidLabel(row, numRow) != NULL)
		{
			return (f_checkIsValidDirectInDirectR(row, 2, numRow));
		}
	}

	//num resident method=0   
	if (*row == '#')
	{
		if (f_matchCommandResidence(numCommand, 0, 1))
		{
			//check the first operand and put row to point after the ','
			if (f_checkIsValidInstantR(&row, numCommand, 1))
			{
				row = f_ingnoreSpaces(row);
				//now check the second operand
				if (numCommand == 1 && *row == '#' && f_checkIsValidInstantR(&(row), numCommand, 2))
				{
					return 1;
				}
				else { return f_checkIsValidDirectInDirectR(row, 2, numRow); }
			}
			//if there is not valid sign error
			else {
				printf("Error!,in row %d not valid statment. shuould be number right after the #", numRow);
				return 0;
			}
		}
		else
		{
			printf("Error!,in row %d not valid statment. cannot do instant residence with that command", numRow);
			return 0;
		}
	}
	//relative redisent method =3
	else if (*row == '*')
	{
		if (f_matchCommandResidence(numCommand, 3, 1))
		{
			row++;
			if (f_checkIsValidLabel(row, numRow) != NULL)
			{
				return 1;
			}
		}
		else
		{
			printf("Error!,in row %d not valid statment. cannot do instant residence with that command", numRow);
			return 0;
		}

	}
	//the command that can contarins @ can also coation: 1,2,4,5
	else if (isalpha(*row) || *row == '@')
	{
		if (f_matchCommandResidence(numCommand, 1, 1))
		{
			numOfOperands = f_getNumOperandsByCommandIndex(numCommand);
			//check the first operand 
			if (numOfOperands == 1)
			{
				return f_checkIsValidDirectInDirectR(row, 2, numRow);
			}
			else
			{
				if (f_checkIsValidDirectInDirectR(row, 1, numRow))
				{
					row = strchr(row, ',');
					row++;
					if (f_checkIsValidDirectInDirectR(row, 2, numRow))
					{
						return 1;
					}
				}
				//if there is not valid sign error
				else
				{
					printf("Error!,in row %d not valid statment. something wroing with the operand and the resident method", numRow);
					return 0;
				}
			}
		}
		else
		{
			printf("Error!,in row %d not valid statment. cannot do that residence with that command", numRow);
			return 0;
		}
	}
	return 0;
}





//check the statment if it is valid and which statment is it
//row point to the first letter in the row
int f_checkStatment(char* row, int numRow, char** isLabelInRow)
{
	//hold the num of the command
	int numCommand;
	int status;
	//null -if the label not valid
	char* isValidLabel = NULL;
	//help pointer in row
	char* ptr = row;
	//check if there is a lable 
	ptr = strchr(row, ':');
	//if there is a lable
	if (ptr != NULL)
	{   //check if it is valid lable
		*ptr = '\0';
		isValidLabel = f_checkIsValidLabel(row, numRow);
		if (isValidLabel == NULL)
		{
			status = 0;
			return status;
		}
		else {
			*isLabelInRow = isValidLabel;
		}
		*ptr = ':';
		ptr++;
		row = ptr;
	}
	//row point after the spaces
	row = f_ingnoreSpaces(row);
	if (isalpha(*row))
	{
		status = f_checkIsValidInstruction(row, numRow);
		return status;
	}
	if (*row == '.')
	{
		row++;
		status = f_checkIsValidDirective(row, numRow);
		if (status)
			return status + 1;
	}
	return status;
}

//fucntion to check the validion of the row, get row, num row for print error with the num
//and get pointer to string for returning the label
//must return label without ':'- put /0 in place of :
//status =0 mean error. =1 mean is insturcion. =2 mean is directivve 3-mean itis comment or empty row
//שורה ריקה היא לא ולידית כלומר לא חוקית וגם שורת הערה
int f_checkIsValidRow(char* row, int numRow, char** isLabelInRow)
{
	//hold the status of the row
	int status;
	//ignor spaces in the beginnings
	row = f_ingnoreSpaces(row);

	//if it is empty row
	if (*row == '\n')
	{
		status = 3;
		return status;
	}
	//if the row is note
	if (*row == ';')
	{
		status = 3;
		return status;
	}
	//if the first char is a letter- check which statment is it 
	//and if its valid statment
	if (isalpha(*row))
	{
		f_checkStatment(row, numRow, isLabelInRow);
	}
	//if it has a sign in the begining of the row
	else
	{
		status = 0;
		printf("Error!, not valid statment in row %d , cannot begin with %c", numRow, *row);
		return status;
	}

	//int status=0;
////hold the place of the ':'
//char* index;
//char* label=NULL;
//int command;
//index = strchr(row, ':');
////if the first word is label
//if (index !=NULL)
//{
//	label=f_checkIsValidLabel(row, index);
//	command = f_checkIsValidCommand(index+1);
//}
////else if the first word is command
//else
//{
//	command = f_checkIsValidCommand(row);
//}


//else is error!
}
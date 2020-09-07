
#include <stdio.h>
#include <string.h>

//if the label is valid return the name of the lable
//else return null
char* f_checkIsValidLabel(char* row, int numRow)
{
	//help pointer in row string
	char* ptr;
	if (strlen(row) > 30)
	{
		printf("Error!, in row %d the lable name length more then 30, not valid!", numRow);
		return NULL;
	}
	ptr = row;
	while (*ptr)
	{
		if (*ptr == ' ' || *ptr == '\t')
		{
			printf("Error!, in row %d the lable name not valid ", numRow);
			return NULL;
		}
	}
	return row;
}

int f_checkIsValidCommand(char* row)
{

}
//check the statment if it is valid and which statment is it
//row point to the first letter in the row
int f_checkStatment(char* row, int numRow, char** isLabelInRow)
{
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
		if(isValidLabel)
		ptr++;
		row = ptr;
	}

}

//fucntion to check the validion of the row, get row, num row for print error with the num
//and get pointer to string for returning the label
//must return label without ':'- put /0 in place of :
//status =0 mean error. =1 mean is insturcion. =2 mean is directivve
//שורה ריקה היא לא ולידית כלומר לא חוקית וגם שורת הערה
int f_checkIsValidRow(char* row, int numRow, char** isLabelInRow)
{
	//hold the status of the row
	int status;
	//ignor spaces in the beginnings
	row = f_ingnoreSpaces(row);

	//if it is empty row
	if (*row == '\0')
	{
		status = 0;
		return status;
	}
	//if the row is note
	if (*row == ';')
	{
		status = 0;
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
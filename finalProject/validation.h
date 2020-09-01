#include <string.h>
int G_flagError=0;

char * f_checkIsValidLabel(char * row, char * index)
{
	return NULL;
}

int f_checkIsValidCommand(char * row)
{

}
//fucntion to check the validion of the row
int f_checkIsValidRow(char* row)
{
	//hold the place of the ':'
	char* index;
	char* label=NULL;
	int command;
	index = strchr(row, ':');
	//if the first word is label
	if (index !=NULL)
	{
		label=f_checkIsValidLabel(row, index);
		command = f_checkIsValidCommand(index+1);
	}
	//else if the first word is command
	else
	{
		command = f_checkIsValidCommand(row);
	}


	//else is error!
}
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "structures.h"
#include "validation.h"
#include "manageInstruction.h"
#include "manageDirective.h"

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
	char* row=(char*)malloc(sizeof(char));
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
//the order of assembelr:
//pre passion - count rows in file
//init hash table for symbols
//first pass
//second pass
//in the second pass we shuold check all the nodes: if the field "first operand" or "secondOperand "
//not null- we shuld do something
//we should indicate also somthing improtant:
//is the second pass shuld put adress of second operand (usually) or put the far of adress of second operand (for *)
//if error flag is true:
//free alocation memory in list
//and return file with errors
//if error flag is false:
//write output files


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





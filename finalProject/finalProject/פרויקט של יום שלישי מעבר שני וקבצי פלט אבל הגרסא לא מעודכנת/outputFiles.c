#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "symbolsHash.h"
extern int IC;
extern int DC;
extern S_nodeInstruction* headInstructionList;
extern S_nodeData* headDataList;


void f_writeObFile(char* nameFile)
{
	FILE* obFile;
	S_nodeInstruction* instructionPtr = headInstructionList;
	S_nodeData* dataPtr = headDataList;
	obFile = fopen("file.ob", "w");
	if (obFile == NULL)
	{
		perror("canot write fo .ob file");
	}
	else
	{
		fprintf(obFile, "%o %o\n", IC, DC);
		while (instructionPtr != NULL)
		{
			fprintf(obFile, "%o %o %c \n", instructionPtr->address, instructionPtr->binaryCode, instructionPtr->state);
			instructionPtr = instructionPtr->next;
		}
		while (dataPtr != NULL)
		{
			fprintf(obFile, "%o %o\n", dataPtr->address + IC, dataPtr->binaryCode);
			dataPtr = dataPtr->next;
		}

	}
}

void f_writeENTFile()
{
	FILE* entFile;
	struct symbol* entrySymbol = NULL;

	entrySymbol = f_getNextEntry(entrySymbol);
	if (entrySymbol)
	{
		entFile = fopen("file.ent", "w");
		if (entFile == NULL)
		{
			perror("canot write to .ent file");
		}
		else
		{
			fprintf(entFile, "%s %o\n", entrySymbol->label, entrySymbol->address);
			while (entrySymbol = f_getNextEntry(entrySymbol) != NULL)
			{
				fprintf(entFile, "%s %o\n", entrySymbol->label, entrySymbol->address);
			}
		}
	}
}

void f_writeEXTFile()
{
	FILE* extFile;
	struct symbol* externSymbol = NULL;

	externSymbol = f_getNextExtern(externSymbol);
	if (externSymbol)
	{
		extFile = fopen("file.ext", "w");
		if (extFile == NULL)
		{
			perror("canot open the input file");
		}
		else
		{
			fprintf(extFile, "%s %o\n", externSymbol->label, externSymbol->address);
			while (externSymbol = f_getNextEextern(externSymbol) != NULL)
			{
				fprintf(extFile, "%s %o\n", externSymbol->label, externSymbol->address);
			}
		}
	}
}

void writeRelFile()
{
	FILE* relFile;
	S_nodeInstruction* instructionPtr = headInstructionList;
	
	relFile = fopen("file.ob", "w");
	if (relFile == NULL)
	{
		perror("canot crete the oupter .rel file");
	}
	else
	{
		while (instructionPtr != NULL)
		{
			if (instructionPtr->state == 'r')
				fprintf(relFile, "%o\n", instructionPtr->address);
			instructionPtr = instructionPtr->next;
		}
	}
}

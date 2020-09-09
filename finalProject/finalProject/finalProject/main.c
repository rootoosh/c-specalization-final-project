
#include <stdio.h>
#include "assembler.h"

//here i just open the input file and send to the assembelr program
int main(int argc,char **argv)
{
	if (argc < 2)
	{
		perror("the program didnt get file to manipulate");  
	}
	else
	{
		FILE* inputFile;
		inputFile = fopen((char*)(argv[1]), "r");
		if (inputFile == NULL)
		{
			perror("canot open the input file");
		}
	

		//f_assembleFirstPass(inputFile,listData,listInstrucion);
		//allocate hashForSymbol(n)
		//f_assenmbleSecondPass(inputFile,listDAta,listInstruction)
		//f_assemble
		if (fclose(inputFile) != 0)
		{
			perror("could not close the file");
		}
	}
	return 0;
}


﻿


// finalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <stdlib.h>

//here i just open the input file and send to the assembelr program
int main()
{
	if (__argc < 2)
	{ 
		perror("the program didnt get file to manipulate");
	}
	FILE * inputFile;
	inputFile=fopen((char*)(__argv[1]), "r");
	if (inputFile == NULL)
	{	
		perror("canot open the input file");
	}
	//int n=countrows(inputFile)
	//allocate hashForSymbol(n)
	//f_assembleFirstPass(inputFile);
	//f_assenmbleSecondPass(inputFile,listDAta,listInstruction)
	//f_
	if (fclose(inputFile) != 0)
	{
		perror("could not close the file");
	}
}


#include "structures.h"
#include "commandsData.h"
//make array that represent all the commands that valid in assembly
S_command cammoandTable[16]=
{

{{1,1,1,0,1,1}, {0,1,1,0,1,1}, "mov", 2},
{{1,1,1,0,1,1}, {1,1,1,0,1,1}, "cmp", 2},
{{1,1,1,0,1,1}, {0,1,1,0,1,1}, "add", 2},
{{1,1,1,0,1,1}, {0,1,1,0,1,1}, "sub", 2},
{{1,1,1,0,1,1}, {0,1,1,0,1,1}, "mul", 2},
{{1,1,1,0,1,1}, {0,1,1,0,1,1}, "div", 2},
{{0,1,0,0,0,0}, {0,1,1,0,1,1}, "lea", 2},
{{0,0,0,0,0,0,}, {0,1,1,0,1,1}, "inc", 1},
{{0,0,0,0,0,0,}, {0,1,1,0,1,1}, "dec", 1},
{{0,0,0,0,0,0,}, {0,1,1,1,1,1}, "brz", 1},
{{0,0,0,0,0,0,}, {0,1,1,1,1,1}, "jmp", 1},
{{0,0,0,0,0,0,}, {0,1,1,0,1,1}, "red", 1},
{{0,0,0,0,0,0,}, {0,1,1,0,1,1}, "prn", 1},
{{0,0,0,0,0,0,}, {0,1,1,1,1,1}, "jsr", 1},
{{0,0,0,0,0,0,}, {0,0,0,0,0,0,}, "rts", 0},
{{0,0,0,0,0,0,}, {0,0,0,0,0,0,}, "hlt", 0},

};

//the num that represent the command is the index of that command in the commandTable
int f_getNumCommand(char commandStr[3])
{
	// cammoandTable פשוט מחזירה מס' פקודה בין 0 ל15 צריך לעשות חיפוש  במערך
	return 0;
}

//get num of operand to that command by command name

int f_getNumOperandsByCommandIndex(int command)
{
	return cammoandTable[command].numOperands;
}
int f_matchCommandResidence(int command, int residenceMethod, int operandSerial)
{
	if (operandSerial == 1)
	{
		return cammoandTable[command].sourceResident[residenceMethod];
	}
	if (operandSerial == 2)
	{
		return cammoandTable[command].destResident[residenceMethod];
	}
}

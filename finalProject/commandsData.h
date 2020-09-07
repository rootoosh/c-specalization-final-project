

typedef struct
{
	//type of resident method can be the source operands
	int sourceResident[6];
	//type of resident method can be the dest operands
	int destResident[6];
	char name[4];
	//num of operators should be in that command
	int numOperands;
}S_command;

//make array that represent all the commands that valid in assembly
S_command cammoandTable[16]
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
	// cammoandTable ���� ������ ��' ����� ��� 0 �15 ���� ����� �����  �����
	return 0;
}
//����� ���������� ���� ����� �� ������
int f_check()
{
	return 0;
}
//get num of operand to that command by command name
int f_getNumOperandsByCommandName(char commandName[3])
{
	int indexCommand = f_getNumCommand(commandName);
	return cammoandTable[indexCommand].numOperands;
}
int f_getNumOperandsByCommandIndex(int command)
{
	return cammoandTable[command].numOperands;
}
int f_matchCommandResidence(int command, int residenceMethod, int operandSerial)
{
	//return commandTa
}

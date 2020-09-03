
//struct of assembly command for validation on commands
typedef struct
{
	char* name;
	//type of resident method can be the source operands
	int sourceResident[3];
	//type of resident method can be the dest operands
	int destResident[3];
	//num of operators should be in that command
	int numOperands;
}S_command;

//make array that represent all the commands that valid in assembly
S_command cammoandTable[16];

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

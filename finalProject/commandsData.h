
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
int f_getNumCommand(char* commandStr)
{
	// cammoandTable פשוט מחזירה מס' פקודה בין 0 ל15 צריך לעשות חיפוש  במערך
}
//בקובץ הולידצדיות צריך לעשות פה בדיקות
int f_check()
{

}
//get num of operand to that command by command name
int f_getNumOperandsByCommandName(char* commandName)
{
	int indexCommand = f_getNumCommand(commandName);
	return cammoandTable[indexCommand].numOperands;
}

#ifndef Validation
#define Validation

int f_checkIsValidCommand(char* row, int numRow);

int f_checkIsValidNum(char* row, int numRow);
int f_checkIsValidDataNumbers(char* row, int numRow);

char* f_checkIsValidLabel(char* row, int numRow);

int f_checkIsValidString(char* row, int numRow);

int f_checkIsValidDirective(char* row, int numRow);

int f_checkIsValidInstantR(char** pointoRow, int numRow, int numOperand);

int f_checkIsValidDirectInDirectR(char* row, int numOperand, int numRow);

int f_checkIsValidInstruction(char* row, int numRow);

int f_checkStatment(char* row, int numRow, char** isLabelInRow);

int f_checkIsValidRow(char* row, int numRow, char** isLabelInRow);

#endif
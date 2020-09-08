

int f_checkIsValidCommand(char* row, int numRow);

//if the number valid and has "," return 1 if not have "," return 2
//else if not valid return 0
int f_checkIsValidNum(char* row, int numRow);
//if the data number valid return 1
//else return 0
int f_checkIsValidDataNumbers(char* row, int numRow);

//if the label is valid return the name of the lable (or row)
//else return null
char* f_checkIsValidLabel(char* row, int numRow);
int f_checkIsValidString(char* row, int numRow);
//check if the directive ststment is valid return 1 else return 0
//row point after the  .
int f_checkIsValidDirective(char* row, int numRow);
//note here is have row++
//check is valid instrand resident method (#)=0
int f_checkIsValidInstantR(char** pointoRow, int numRow, int numOperand);
//check direct and indirect residence for register or label(4 methods)
int f_checkIsValidDirectInDirectR(char* row, int numOperand, int numRow);
//check if instruction valid return 1 if valid else 0
int f_checkIsValidInstruction(char* row, int numRow);

//check the statment if it is valid and which statment is it
//row point to the first letter in the row
int f_checkStatment(char* row, int numRow, char** isLabelInRow);
//fucntion to check the validion of the row, get row, num row for print error with the num
//and get pointer to string for returning the label
//must return label without ':'- put /0 in place of :
//status =0 mean error. =1 mean is insturcion. =2 mean is directivve
//שורה ריקה היא לא ולידית כלומר לא חוקית וגם שורת הערה
int f_checkIsValidRow(char* row, int numRow, char** isLabelInRow);
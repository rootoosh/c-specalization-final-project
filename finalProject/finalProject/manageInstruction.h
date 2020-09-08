#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "structures.h"
#include "commandsData.h"
#include "symbolsHash.h"

//get string and check is it register or label operand. in the nameOp put the name nice with \n
int f_checkRegistOrLabel(char* row, char** nameOp);

//row point on the char just after the command
void f_instrct2operand(char* row, S_nodeInstruction* newNode);
void f_putBinaryCode(int numCommand, S_nodeInstruction* node, int lastIndex);

//find # mean Instant residence method
void f_manageInstandResidence(char* row, S_nodeInstruction* node, int serialOperand);

void f_putLabelInNode(char* label, S_nodeInstruction* node, int serialOperand);
void f_manageRelativeResidence(char* row, S_nodeInstruction* newNode);

//row point on the char just after the command
//or just after the , of the first operand
void f_instrct1operand(char* row, S_nodeInstruction* newNode);

//deal with the instruction list,
void f_manamgeInstruction(char* row, char* isLabel);
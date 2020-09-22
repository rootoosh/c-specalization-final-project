
#include "structures.h"
#ifndef assembler
#define assembler


#include <stdio.h>

void f_assembleFirstPass(FILE* inputFile);
void f_assembleSecondPass();
S_nodeInstruction* f_OperandNewNode(int address, int labelAddress, E_scopeLabel scope);

#endif // !assembler
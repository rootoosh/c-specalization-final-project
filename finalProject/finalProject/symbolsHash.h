
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

//get label and scope and modity the scope of the label in the hash symbols table
void f_updateScopeLabel(char* label, E_scopeLabel scope);

void f_modifyLabel(char* row, E_scopeLabel scope);

//the function get label and type and insert it to the symbols table
void f_insertLabel(char* label, E_typeLabel labelType);

 S_symbol* headSymbolList=NULL;
 S_symbol* tailSymbolList;



#ifndef symbolH
#define symbolH


#include "structures.h"

//this functioin get detalis of label and insert into S_symbol struct
void f_insertLabel(char* label, E_typeLabel type,E_scopeLabel scope, int address);

void f_initHash(int capacity);

//this function Take each node from the list S_symbol
//and puts it in the hash table and disconnects it from the list 
void f_convertFromListToHash();

struct symbol* search(char* key);
// hash code function for a label name
int f_hashCode(char* label);

////get label and scope and modity the scope of the label in the hash symbols table
void f_updateScopeLabel(char* label, E_scopeLabel scope);

void f_modifyLabel(char* row, E_typeLabel type, E_scopeLabel scope);



#endif // !symbolH
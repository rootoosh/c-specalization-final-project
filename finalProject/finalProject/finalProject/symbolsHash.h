#ifndef symbolH
#define symbolH


#include "structures.h"

//this functioin get detalis of label and insert into S_symbol struct
void f_insertLabel(char* label, E_typeLabel type, E_scopeLabel scope, int address);

void f_initHash(int capacity);

//hash code function for a label name
int f_hashCode(char* label);

//this function Take each node from the list S_symbol
//and puts it in the hash table and disconnects it from the list 
int f_convertFromListToHash();

struct  symbol* search(char* key);

void f_modifyLabel(char* row, E_typeLabel type, E_scopeLabel scope);
#endif // !symbolH
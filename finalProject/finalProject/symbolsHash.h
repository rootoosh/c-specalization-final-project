
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

//this functioin get detalis of label and insert into S_symbol struct
void f_insertLabel(char* label, E_typeLabel type, int address);

void f_initHash(int capacity);

// hash code function for a label name
int f_hashCode(char* label);

//this function Take each node from the list S_symbol
//and puts it in the hash table and disconnects it from the list 
void f_convertFromListToHash();

struct  symbol* search(char* key);

////get label and scope and modity the scope of the label in the hash symbols table
void f_updateScopeLabel(char* label, E_scopeLabel scope);

void f_modifyLabel(char* row, E_scopeLabel scope);

struct symbol* headSymbolList=NULL;
struct symbol* tailSymbolList;



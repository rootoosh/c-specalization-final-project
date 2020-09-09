#ifndef manageD
#define manageD


#include "structures.h"

//initialize DataNode for .data directive
void f_initializeDataNode(struct nodeD* node, int num);

void f_initilzeFirstDataNode(struct nodeD* node, int num);

void f_manageData(char* row, S_nodeData* node);

void f_initializeStringNode(int ch, S_nodeData* node);

void f_manageString(char* row, S_nodeData* node);

void f_manageDirective(char* row, char* isLabel);
#endif // !manageD
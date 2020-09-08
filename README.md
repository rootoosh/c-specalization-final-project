# c-specalization-final-project
western digital bootcamp final project

assembler program: get assembly input file with extension .as
return 3 output file:
1. the binary machine code -with extension .ob
2.the external machine code -with extension .ext
3.the entry machine code- with extension .ent
4. file with extension .rel

note: when there is a problem- one row in the input file is not valid- 
  the program will not return result output, only error file that explain all the errors in the input file
  
/*
the order of assembelr:

1.first pass
2.if error flag is true:
free alocation memory in list
and return file with errors
3.if error flag is false:
init hash table for symbols.convert form list to hash
second pass
in the second pass we shuold check all the nodes:
if the field "first operand" or "secondOperand "
not null- we shuld do something
for lebels should manage address 
4.write output files
5.  free alocation memory
*/


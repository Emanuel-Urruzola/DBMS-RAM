#ifndef _PRINT_H
#define _PRINT_H
#include "variables.h"

string getRowString( Tuple, int, typeOfData &, int &, string & );

void LoopInRows( Tuples, TreeInt &, TreeStr &, int, typeOfData & );

typeRet PrintDataTable( string, string );

#endif
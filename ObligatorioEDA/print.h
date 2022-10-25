#pragma once
#include "variables.h"

string getRowString( Tuple, int, typeOfData&, int&, string& );

void loopInRows( Tuples, TreeInt&, TreeStr&, int, typeOfData& );

typeRet printDataTable( string, string );
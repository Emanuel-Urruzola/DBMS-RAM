#pragma once
#include "variables.h"

int maxlenght( Tuple );

ListInt getFirstLength( Tuple );

void getLength( Tuples rows, ListInt list );

string getRowString( Tuple, int, typeOfData&, int&, string&, ListInt );

void loopInRows( Tuples, TreeInt&, TreeStr&, int, typeOfData& );

void separator( );

typeRet printDataTable( string, string );

typeRet printMetadata( string );
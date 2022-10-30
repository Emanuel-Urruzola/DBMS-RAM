#pragma once
#include "variables.h"

void releaseTree( TreeStr& tree );

typeRet insertAndCreate( TreeStr&, string, string, string, string );

typeRet insertIntoTableIntersection( Tables, string, TreeStr&, string );

TreeStr deleteNodeTree( TreeStr&, string );

typeRet insertIntoSet( Tables, string, string, TreeStr );

typeRet createTableUnion( Tables, Tables, string );

typeRet checkSchema( Tables, Tables, string );

int insertSetTreeInTable( TreeStr, string );

typeRet unionDB( string, string, string, string );
#pragma once
#include "variables.h"

union tree {
  TreeInt treeInt;
  TreeStr treeStr;
};

void deleteListInt( ListInt& );

void insBack( List&, string );

void insBackInt( ListInt&, int );

TreeInt newNode( int, string );

TreeStr newNodeStr( string, string );

typeRet insert( TreeInt&, int, string );

typeRet insertText( TreeStr&, string, string );

bool boolInsertText( TreeStr& , string , string  );

void showTreeStr( TreeStr );

void showTree( TreeInt );

TreeStr findMinimum( TreeStr );

Tuples insFrontTuples( Tuples, Tuple );

#ifndef _OPERATIONS_H
#define _OPERATIONS_H
#include "../include/variables.h"

union tree {
  TreeInt treeInt;
  TreeStr treeStr;
};

void InsBack( List &, string );

void InsBackInt( ListInt &, int );

TreeInt NewNode( int, string );

TreeStr NewNodeStr( string, string );

typeRet Insert( TreeInt &, int, string );

typeRet InsertText( TreeStr &, string, string );

void ShowTreeStr( TreeStr );

void ShowTree( TreeInt );

#endif
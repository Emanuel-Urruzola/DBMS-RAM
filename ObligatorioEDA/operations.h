#pragma once
#include "variables.h"

union tree {
	TreeInt treeInt;
	TreeStr treeStr;
};

void insBack(List&, string);

void insBackInt(ListInt&, int);

TreeInt newNode(int, string);

TreeStr newNodeStr(string, string);

typeRet insert(TreeInt&, int, string);

typeRet insertText(TreeStr&, string, string);

void showTreeStr(TreeStr);

void showTree(TreeInt);

#pragma once
#include <string>
using namespace std;

enum typeOfRestriction { NOT_EMPTY = 0, PRIMARY_KEY, ANY };
enum typeOfData { STRING = 0, INT };
enum typeRet { OK = 0, ERROR, NOT_IMPLEMENTED };

// template<typename values>  //It doesn't seem to work.
struct nodeElement {
	string name;
	string text;
	int number;
	typeOfData type;
	typeOfRestriction restriction;
	nodeElement* next;
};
typedef nodeElement* Tuple;

struct nodeTuple {
	Tuple row;
	nodeTuple* next;
};
typedef nodeTuple* Tuples;

struct nodeTable {
	string name;
	Tuple attributes;
	Tuples tuple;
	nodeTable* next;
};
typedef nodeTable* Tables;

struct nodeList {
	string value;
	nodeList* next;
};
typedef nodeList* List;

struct nodeListInt {
	int value;
	nodeListInt* next;
};
typedef nodeListInt* ListInt;

struct nodeTree {
	int value;
	string row;
	nodeTree* right;
	nodeTree* left;
};
typedef nodeTree* TreeInt;

struct nodeTreeStr {
	string value;
	string row;
	nodeTreeStr* right;
	nodeTreeStr* left;
};
typedef nodeTreeStr* TreeStr;

inline Tables tablesList = NULL;

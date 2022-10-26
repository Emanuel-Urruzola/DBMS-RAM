#pragma once
#include <string>
using namespace std;

enum class typeOfRestriction { NOT_EMPTY = 0, PRIMARY_KEY=1, ANY=2 };
enum class typeOfData { STRING = 0, INT=1 };
enum class typeRet { OK = 0, ERROR=1, NOT_IMPLEMENTED=2 };

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

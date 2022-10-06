#ifndef variables
#define variables
#include <string>
using std::string;

enum typeOfRestriction {NOT_EMPTY, PRIMARY_KEY, ANY};
enum typeOfData {STRING, INT};
enum typeRet {OK, ERROR, NOT_IMPLEMENTED};

// template<typename values>  //It doesn't seem to work.
struct nodeElement{
  string text;
  int number;
  typeOfData type;
  typeOfRestriction restriction;
  unsigned int index; // to get the position for a simple find
  nodeElement *next;
};
typedef nodeElement* Tuple;

struct nodeTuple{
  Tuple *row;
  nodeTuple *next;
};
typedef nodeTuple* Tuples;

struct nodeTable{
  string name;
  unsigned int index;
  Tuple attributes;
  Tuples tuple;
  nodeTable *next;
};
typedef nodeTable* Tables;

struct nodeList{
  string value;
  nodeList *next;
};
typedef nodeTable* List;

#endif // !variables
#ifndef operations,
#define operations
#include "variables.hpp"
using namespace std;
void InsBack( List &initialList, string value ) {
  List newNode   = new nodeList;
  newNode->value = value;
  newNode->next  = NULL;
  if( initialList == NULL ) {
    initialList = newNode;
  } else {
    List copyList = initialList;
    while( copyList->next != NULL ) {
      copyList = copyList->next;
    }
    copyList->next = newNode;
  }
}

#endif
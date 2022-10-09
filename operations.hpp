#ifndef operations
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

void InsBackInt( ListInt &initialList, int value ) {
  ListInt newNode = new nodeListInt;
  newNode->value  = value;
  newNode->next   = NULL;
  if( initialList == NULL ) {
    initialList = newNode;
  } else {
    ListInt copyList = initialList;
    while( copyList->next != NULL ) {
      copyList = copyList->next;
    }
    copyList->next = newNode;
  }
}

typeRet printDataTable( string tableName, string ordeyBy ) {
  Tables table = findTable( tableName );
  if( table == NULL ) return ERROR;
  if( table->attributes == NULL ) {
    cout << "No hay tuplas en " << tableName << endl;
    return OK;
  }
}

TreeInt NewNode( int value, string row ) {
  TreeInt newNode = new nodeTree;
  newNode->value  = value;
  newNode->row    = row;
  newNode->right  = NULL;
  newNode->left   = NULL;
  return newNode;
}

void insert( TreeInt &tree, int value ) {
  if( tree == NULL ) {
    TreeInt newTree = NewNode( value, "" );
    tree            = newTree;
  } else {
    if( value < tree->value ) {
      insert( tree->left, value );
    } else {
      insert( tree->right, value );
    }
  }
}

void showTree( TreeInt tree ) {
  if( tree == NULL ) return;
  showTree( tree->left );
  cout << tree->row << endl;
  showTree( tree->right );
}

#endif
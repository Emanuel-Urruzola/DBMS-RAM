#ifndef operations
#define operations
#include "variables.hpp"
#include "operations.hpp"
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

TreeInt NewNode( int value, string row ) {
  TreeInt newNode = new nodeTree;
  newNode->value  = value;
  newNode->row    = row;
  newNode->right  = NULL;
  newNode->left   = NULL;
  return newNode;
}

TreeStr NewNodeStr( string value, string row ) {
  TreeStr newNode = new nodeTreeStr;
  newNode->value  = value;
  newNode->row    = row;
  newNode->right  = NULL;
  newNode->left   = NULL;
  return newNode;
}

// TODO: review returns when testable
typeRet Insert( TreeInt &tree, int value, string row ) {
  if( tree == NULL ) {
    TreeInt newTree = NewNode( value, row );
    tree            = newTree;
  } else {
    if( value < tree->value ) {
      Insert( tree->left, value, row );
    } else if( value == tree->value ) {
      Insert( tree->right, value, row );
      return ERROR;
    } else {
      Insert( tree->right, value, row );
    }
  }
}

typeRet InsertText( TreeStr &tree, string value, string row ) {
  if( tree == NULL ) {
    TreeStr newTree = NewNodeStr( value, row );
    tree            = newTree;
  } else {
    if( value.compare( tree->value ) < 0 ) {
      InsertText( tree->left, value, row );
    } else if( value.compare( tree->value ) == 0 ) {
      InsertText( tree->right, value, row );
      return ERROR;
    } else {
      InsertText( tree->right, value, row );
    }
  }
}

void ShowTreeStr( TreeStr tree ) {
  if( tree == NULL ) return;
  ShowTreeStr( tree->left );
  cout << tree->row << endl;
  ShowTreeStr( tree->right );
}

void ShowTree( TreeInt tree ) {
  if( tree == NULL ) return;
  ShowTree( tree->left );
  cout << tree->row << endl;
  ShowTree( tree->right );
}
#endif
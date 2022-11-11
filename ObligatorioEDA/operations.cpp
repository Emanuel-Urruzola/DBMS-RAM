#include <iostream>
#include "operations.h"
#include "variables.h"
using namespace std;

void insBack( List& initialList, string value ) {
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

void insBackInt( ListInt& initialList, int value ) {
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

void deleteListInt( ListInt& list ) {
  if( list->next != NULL ) deleteListInt( list->next );
  delete list;
}

TreeInt newNode( int value, string row ) {
  TreeInt newNode = new nodeTree;
  newNode->value  = value;
  newNode->row    = row;
  newNode->right  = NULL;
  newNode->left   = NULL;
  return newNode;
}

TreeStr newNodeStr( string value, string row ) {
  TreeStr newNode = new nodeTreeStr;
  newNode->value  = value;
  newNode->row    = row;
  newNode->right  = NULL;
  newNode->left   = NULL;
  return newNode;
}

typeRet insert( TreeInt& tree, int value, string row ) {
  if( tree == NULL ) {
    TreeInt newTree = newNode( value, row );
    tree            = newTree;
    return typeRet::OK;
  } else {
    if( value < tree->value ) {
      insert( tree->left, value, row );
      return typeRet::OK;
    } else if( value == tree->value ) {
      insert( tree->right, value, row );
      return typeRet::ERROR;
    } else {
      insert( tree->right, value, row );
      return typeRet::OK;
    }
  }
}

typeRet insertText( TreeStr& tree, string value, string row ) {
  if( tree == NULL ) {
    TreeStr newTree = newNodeStr( value, row );
    tree            = newTree;
    return typeRet::OK;
  } else {
    if( value.compare( tree->value ) < 0 ) {
      insertText( tree->left, value, row );
      return typeRet::OK;
    } else if( value.compare( tree->value ) == 0 ) {
      insertText( tree->right, value, row );
      return typeRet::ERROR;
    } else {
      insertText( tree->right, value, row );
      return typeRet::OK;
    }
  }
}

bool boolInsertText( TreeStr& tree, string value, string row ) {
  if( tree == NULL ) {
    TreeStr newTree = newNodeStr( value, row );
    tree            = newTree;
    cout << tree->value << " y  " << value << endl << endl;
    return true;
  } else {
    cout << tree->value << " ";
    if( value.compare( tree->value ) < 0 )
      return boolInsertText( tree->left, value, row );
    else if( value.compare( tree->value ) == 0 )
      return false;
    else
      return boolInsertText( tree->right, value, row );
  }
}

void showTreeStr( TreeStr tree ) {
  if( tree == NULL ) return;
  showTreeStr( tree->left );
  cout << tree->row << endl;
  showTreeStr( tree->right );
}

void showTree( TreeInt tree ) {
  if( tree == NULL ) return;
  showTree( tree->left );
  cout << tree->row << endl;
  showTree( tree->right );
}

TreeStr findMinimum( TreeStr tree ) {
  if( tree->left == NULL ) return tree;
  return findMinimum( tree->left );
}

Tuples insFrontTuples( Tuples tuplesList, Tuple row ) {
  if( tuplesList == NULL ) {
    tuplesList       = new nodeTuple;
    tuplesList->row  = row;
    tuplesList->next = NULL;
  } else {
    Tuples copy = new nodeTuple;
    copy->row   = row;
    copy->next  = tuplesList;
    tuplesList  = copy;
  }
  return tuplesList;
}
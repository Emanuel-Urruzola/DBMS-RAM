#ifndef print
#define print
using namespace std;
#include <iostream>
#include "operations.hpp"
#include "tuples.hpp"
using namespace std;
typeRet PrintDataTable( string tableName, string ordeyBy ) {
  Tables table = findTable( tableName );
  if( table == NULL ) return ERROR;
  if( table->tuple->row == NULL ) {
    cout << "No hay tuplas en " << tableName << endl;
    return OK;
  }
  Tuples rows           = table->tuple;
  TreeInt treeQuerie    = NULL;  // To save the int column in a tree
  TreeStr treeQuerieStr = NULL;  // To save the string column in a tree
  string rowString;              // To store the entire row with tabs
  int number;                    // To sort by number
  string text;                   // To sort by text
  typeOfData type;               // To select type of sort
  int n = findIndexColumn( table, ordeyBy );  // Save the index of column ordeby
  while( rows != NULL ) {
    int index = n;  // In this way I avoid calling the function several times
    rowString = "";
    Tuple row = rows->row;
    while( row != NULL ) {
      if( row->type == STRING ) {
        rowString += row->text + "\t";
      } else {
        rowString += row->number + "\t";
      }
      index--;
      if( index == 0 ) type = row->type;
      if( row->type == INT && index == 0 ) number = row->number;
      if( row->type == STRING && index == 0 ) text = row->text;
      row = row->next;
    }
    if( type == STRING ) {
      InsertText( treeQuerieStr, text, rowString );
    } else {
      Insert( treeQuerie, number, rowString );
    }
    rows = rows->next;
  }
  // system( "clear" );
  cout << table->name << endl;
  Tuple attributes = table->attributes;
  while( attributes != NULL ) {
    cout << attributes->name << "\t";
    attributes = attributes->next;
  }
  cout << endl;
  ShowTreeStr( treeQuerieStr );
  cout << endl << endl;
  return OK;
}
#endif
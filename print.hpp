#ifndef print
#define print
using namespace std;
#include <iostream>
#include <string>
#include "operations.hpp"
#include "tuples.hpp"
using namespace std;

string getRowString( Tuple row, int index, typeOfData &type, int &number,
                     string &text ) {
  string rowString = "";
  while( row != NULL ) {
    if( row->type == STRING ) {
      string element = row->text;
      element.resize( 20, ' ' );
      rowString += element + "\t";
    } else {
      cout << row->number;
      string element = to_string( row->number ) + "";
      element.resize( 20, ' ' );
      rowString += element + "\t";
    }
    index--;
    if( index == 0 ) {
      type = row->type;
      if( row->type == INT ) number = row->number;
      else
        text = row->text;
    }
    row = row->next;
  }
  return rowString;
}

void LoopInRows( Tuples rows, TreeInt &treeQuerie, TreeStr &treeQuerieStr,
                 int indexInParameter, typeOfData &type ) {
  int number;   // To sort by number
  string text;  // To sort by text
  while( rows != NULL ) {
    int index        = indexInParameter;
    string rowString = getRowString( rows->row, index, type, number, text );
    if( type == STRING ) {
      InsertText( treeQuerieStr, text, rowString );
    } else {
      Insert( treeQuerie, number, rowString );
    }
    rows = rows->next;
  }
}

typeRet PrintDataTable( string tableName, string ordeyBy ) {
  // TODO: column maximum size and "..." to string more large
  Tables table = findTable( tableName );
  typeOfData type;  // To select type of sort
  if( table == NULL ) return ERROR;
  if( table->tuple == NULL ) {
    cout << "No hay tuplas en " << tableName << endl;
    return OK;
  }
  TreeInt treeQuerie    = NULL;  // To save the int column in a tree
  TreeStr treeQuerieStr = NULL;  // To save the string column in a tree
  int n = findIndexColumn( table, ordeyBy );  // Save the index of column ordeby
  LoopInRows( table->tuple, treeQuerie, treeQuerieStr, n, type );
  // system( "clear" );
  cout << endl << "Tabla " << table->name << ":" << endl;
  Tuple attributes = table->attributes;
  while( attributes != NULL ) {
    string attribute = attributes->name;
    attribute.resize( 20, ' ' );
    cout << attribute << "\t";
    attributes = attributes->next;
  }
  cout << endl;
  if( type == STRING ) ShowTreeStr( treeQuerieStr );
  else
    ShowTree( treeQuerie );

  cout << endl << endl;
  return OK;
}
#endif
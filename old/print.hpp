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
  string rowString = "|";
  bool noExist     = index == 0;
  while( row != NULL ) {
    if( row->type == STRING ) {
      if( row->text.length( ) == 0 ) {
        string element = "EMPTY";
        element.resize( 20, ' ' );
        rowString += element + "\t" + "|";
      } else {
        string element = row->text;
        element.resize( 20, ' ' );
        rowString += element + "\t" + "|";
      }
    } else {
      if( row->number == -1 ) {  // nc
        string element = "EMPTY";
        element.resize( 20, ' ' );
        rowString += element + "\t" + "|";
      } else {
        string element = to_string( row->number ) + "";
        element.resize( 20, ' ' );
        rowString += element + "\t" + "|";
      }
    }
    index--;
    if( index == 0 ) {
      type = row->type;
      if( row->type == INT ) number = row->number;
      else
        text = row->text;
    } else if( row->next == NULL && noExist ) {
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
  // TODO: union?
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
  typeOfData type;  // To select type of sort
  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return ERROR;
  }
  if( table->tuple == NULL ) {
    cout << "No hay tuplas en " << tableName << endl;
    return OK;
  }
  TreeInt treeQuerie    = NULL;  // To save the int column in a tree
  TreeStr treeQuerieStr = NULL;  // To save the string column in a tree
  int n = findIndexColumn( table, ordeyBy );  // Save the index of column ordeby
  if( ! n > 0 && ordeyBy.compare( "\"\"" ) ) {
    cout << "ERROR: No existe la columna" << endl;
    return ERROR;
  }

  LoopInRows( table->tuple, treeQuerie, treeQuerieStr, n, type );
  // system( "clear" );
  cout << endl << "Tabla " << table->name << ":" << endl;
  Tuple attributes = table->attributes;
  cout << "|";
  while( attributes != NULL ) {
    string attribute = attributes->name;
    attribute.resize( 20, ' ' );
    cout << attribute << "\t"
         << "|";
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
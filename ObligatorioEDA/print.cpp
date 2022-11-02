using namespace std;
#include <iostream>
#include <string>
#include "print.h"
#include "operations.h"
#include "tuples.h"
#include "tables.h"
using namespace std;

ListInt lengths = NULL;
string getRowString( Tuple row, int index, typeOfData& type, int& number,
                     string& text, ListInt length ) {
  string rowString = "|";
  while( row != NULL ) {
    string element = "";
    if( row->type == typeOfData::STRING ) {
      if( row->text.length( ) == 0 ) element = "EMPTY";
      else
        element = row->text;
    } else {
      if( row->number == -1 ) element = "EMPTY";  // nc
      else
        element = to_string( row->number ) + "";
    }
    element.resize( length->value, ' ' );
    rowString += " " + element + " |";
    index--;
    if( index == 0 || row->next == NULL ) {
      type = row->type;
      if( type == typeOfData::INT ) number = row->number;
      else
        text = row->text;
    }
    row    = row->next;
    length = length->next;
  }
  return rowString;
}

int maxlenght( Tuple row ) {
  int lengthRow = 2;
  if( row->name.length( ) > lengthRow ) lengthRow = row->name.length( );
  if( row->type == typeOfData::INT &&
      to_string( row->number ).length( ) > lengthRow )
    lengthRow = to_string( row->number ).length( );
  if( row->type == typeOfData::STRING && row->text.length( ) > lengthRow )
    lengthRow = row->text.length( );
  if( row->type == typeOfData::INT && row->number == -1 ||
      row->type == typeOfData::STRING && row->text == "" ) {
    if( lengthRow < 5 ) lengthRow = 5;
  }
  return lengthRow;
}

ListInt getFirstLength( Tuple row ) {
  while( row != NULL ) {
    int lengthRow = maxlenght( row );
    insBackInt( lengths, lengthRow );
    row = row->next;
  }
  return lengths;
}

void getLength( Tuples rows, ListInt list ) {
  while( rows != NULL ) {
    Tuple row     = rows->row;
    ListInt list_ = list;
    while( row != NULL ) {
      int maximum = maxlenght( row );
      if( maximum > list_->value ) list_->value = maximum;
      list_        = list_->next;
      row          = row->next;
    }
    rows = rows->next;
  }
}

void loopInRows( Tuples rows, TreeInt& treeQuerie, TreeStr& treeQuerieStr,
                 int indexInParameter, typeOfData& type ) {
  int number;   // To sort by number
  string text;  // To sort by text
  ListInt lengths = getFirstLength( rows->row );
  getLength( rows, lengths );
  while( rows != NULL ) {
    int index = indexInParameter;
    string rowString =
        getRowString( rows->row, index, type, number, text, lengths );
    if( type == typeOfData::STRING ) {
      insertText( treeQuerieStr, text, rowString );
    } else {
      insert( treeQuerie, number, rowString );
    }
    rows = rows->next;
  }
}

typeRet printDataTable( string tableName, string ordeyBy ) {
  // TODO: column maximum size and "..." to string more large
  typeOfData type;  // To select type of sort
  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }
  if( table->tuple == NULL ) {
    cout << "No hay tuplas en " << tableName << endl;
    return typeRet::OK;
  }
  TreeInt treeQuerie    = NULL;  // To save the int column in a tree
  TreeStr treeQuerieStr = NULL;  // To save the string column in a tree
  int n = findIndexColumn( table, ordeyBy );  // Save the index of column ordeby
  if( n <= 0 && ordeyBy.compare( "\"\"" ) ) {
    cout << "ERROR: No existe la columna" << endl;
    return typeRet::ERROR;
  }

  loopInRows( table->tuple, treeQuerie, treeQuerieStr, n, type );
  // system( "clear" );
  cout << endl << "Tabla " << table->name << ":" << endl;
  separator( );
  Tuple attributes    = table->attributes;
  ListInt copyLengths = lengths;
  cout << "|";
  while( attributes != NULL ) {
    string attribute = attributes->name;
    attribute.resize( copyLengths->value, ' ' );
    cout << " " << attribute << " "
         << "|";
    attributes  = attributes->next;
    copyLengths = copyLengths->next;
  }
  cout << endl;
  separator( );
  if( type == typeOfData::STRING ) showTreeStr( treeQuerieStr );
  else
    showTree( treeQuerie );
  separator( );
  deleteListInt( lengths );
  lengths = NULL;
  return typeRet::OK;
}

void separator( ) {
  ListInt copyLengths = lengths;
  copyLengths         = lengths;
  while( copyLengths != NULL ) {
    string minus = "";
    minus.resize( copyLengths->value + 2, '-' );
    cout << "+" << minus;
    copyLengths = copyLengths->next;
  }
  cout << "+";
  cout << endl;
}
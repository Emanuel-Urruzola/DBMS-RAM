#ifndef tuples
#define tuples
#include <iostream>
#include "variables.hpp"
#include "tables.hpp"
using namespace std;
bool validColumns( string columnsOrder, Tables table ) {
  size_t position;
  int userAttributesCounter = 0;
  //  TODO: Check possible double name in columns
  //  TODO: Validate types and restrictions
  while( ( position = columnsOrder.find( ":" ) ) != string::npos ) {
    userAttributesCounter++;
    int counter               = 0;
    Tuple tableAttributesCopy = table->attributes;
    while( tableAttributesCopy != NULL ) {
      if( columnsOrder.substr( 0, position ) == tableAttributesCopy->name )
        counter++;
      tableAttributesCopy = tableAttributesCopy->next;
    }
    if( counter != 1 ) return false;
    columnsOrder.erase( 0, position + 1 );
  }
  if( userAttributesCounter == table->attributes->index ) return true;
  return false;
}

void InsertInto( Tables &tablesList, string tableName, string columnsOrder,
                 string columnValues ) {
  Tables table = findTable( tablesList, tableName );
  if( table == NULL ) {
    cout << "Doesn't exist";
  } else {
    if( validColumns( columnsOrder, table ) ) {
      Tuples newRow = new nodeTuple;
      newRow->next  = NULL;
      newRow->row   = NULL;
      if( table->tuple != NULL ) {
        Tuples tableRows = table->tuple;
        while( tableRows->next != NULL ) {
          tableRows = tableRows->next;
        }
        tableRows->next = newRow;
      } else {
        table->tuple = newRow;
      }
      Tuple tableAttributesCopy = table->attributes;
      while( tableAttributesCopy != NULL ) {
        size_t position;
        string columnsOrderCopy = columnsOrder;
        bool finded             = false;
        int columnIndex         = 0;
        while( ( position = columnsOrderCopy.find( ":" ) ) != string::npos &&
               ! finded ) {
          if( ( tableAttributesCopy->name ==
                columnsOrderCopy.substr(
                    0, columnsOrderCopy.length( ) -
                           ( columnsOrderCopy.length( ) -
                             columnsOrderCopy.find( ":" ) ) ) ) ) {
            finded = true;
          } else {
            columnIndex++;
            columnsOrderCopy.erase( 0, position + 1 );
          }
        }
        string columnValuesCopy = columnValues;
        // TODO: Fix column values indexes
        for( int i = 0; i < columnIndex; i++ ) {
          position = columnValuesCopy.find( ":" );
          columnValuesCopy.erase( 0, position + 1 );
        }
        columnValuesCopy = columnValuesCopy.substr(
            0, columnValuesCopy.length( ) - ( columnValuesCopy.length( ) -
                                              columnValuesCopy.find( ":" ) ) );
        Tuple newTuple        = new nodeElement;
        newTuple->next        = NULL;
        newTuple->text        = columnValuesCopy;
        newTuple->type        = tableAttributesCopy->type;
        newTuple->restriction = tableAttributesCopy->restriction;
        if( newRow->row == NULL ) {
          newRow->row = newTuple;
        } else {
          Tuple rowCopy = newRow->row;
          while( rowCopy->next != NULL ) {
            rowCopy = rowCopy->next;
          }
          rowCopy->next = newTuple;
        }
        tableAttributesCopy = tableAttributesCopy->next;
      }
    }
  }
  cout << "";
}
#endif  // !tuples test
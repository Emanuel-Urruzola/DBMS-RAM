#ifndef tuples
#define tuples
#include <iostream>
#include <regex>
#include "variables.hpp"
#include "tables.hpp"
#include "operations.hpp"
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

void InsertInto( string tableName, string columnsOrder, string columnValues ) {
  Tables table = findTable( tableName );
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
}

int WhereConditionColumn( Tables table, string columnName ) {
  if( table == NULL ) return -1;
  int index = 0;
  while( table->attributes != NULL ) {
    index++;
    if( table->attributes->name == columnName ) {
      return index;
    }
    table->attributes = table->attributes->next;
  }
  return -1;
}

typeRet findColumn( Tables table, string columnName ) {
  if( table == NULL ) return ERROR;
  Tuple attributes = table->attributes;
  while( attributes != NULL ) {
    if( attributes->name == columnName ) return OK;
    attributes = attributes->next;
  }
  return ERROR;
}

int findIndexColumn( Tables table, string columnName ) {
  if( table == NULL ) return 0;
  int index        = 0;
  Tuple attributes = table->attributes;
  while( attributes != NULL ) {
    index++;
    if( attributes->name == columnName ) return index;
    attributes = attributes->next;
  }
  return 0;
}

ListInt findMatches( Tables table, int index, string value,
                     string columnToModify, string newValueInColumn ) {
  ListInt indexes = NULL;
  Tuples tuple    = table->tuple;
  while( tuple != NULL ) {
    Tuple row = tuple->row;
    for( int i = 1; i < index; i++ ) {
      row = row->next;
    }
    if( row->text == value ) {
      Tuple rowAgain = tuple->row;
      // TODO: Insert directly new value
    }
    tuple = tuple->next;
  }
  return indexes;
}

// update (Personas,Nombre=”Pepe”,CI,1555000);
typeRet update( string tableName, string whereCondition, string columnToModify,
                string newValue ) {
  Tables table = findTable( tableName );
  if( table == NULL ) return ERROR;  // if table no exist
  if( findColumn( table, columnToModify ) == ERROR )
    return ERROR;  // if column to modify no exist
  int index = WhereConditionColumn(
      table,
      whereCondition.substr(
          0, whereCondition.find( "=" ) ) );  // Get the position of attribute
  if( index == -1 ) return ERROR;             // If the position doesn't found
  const regex regExp( "[\"'”][A-Za-z\\d]+[\"'”]" );
  cout << whereCondition.substr(
      whereCondition.find( "=" ) + 1,
      whereCondition.length( ) - whereCondition.find( "=" ) + 1 );
  ListInt indexes = NULL;
  if( regex_match( whereCondition.substr( whereCondition.find( "=" ) + 1,
                                          whereCondition.length( ) -
                                              whereCondition.find( "=" ) + 1 ),
                   regExp ) ) {
    indexes = findMatches(
        table, index,
        whereCondition.substr(
            whereCondition.find( "=" ) + 2,
            whereCondition.length( ) - ( whereCondition.find( "=" ) + 3 ) ),
        columnToModify, newValue );
  }
  return OK;
}
#endif  // !tuples test
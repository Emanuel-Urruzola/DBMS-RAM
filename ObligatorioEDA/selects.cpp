#include <iostream>
#include "selects.h"
#include "variables.h"
#include "tables.h"
#include "tuples.h"
using namespace std;

void insertRow( Tuples tableTuple, string newTableName ) {
  string columns      = "";
  string values       = "";
  Tuple tupleRowsCopy = tableTuple->row;
  while( tupleRowsCopy->next != NULL ) {
    columns = columns + tupleRowsCopy->name + ":";
    if( tupleRowsCopy->type == typeOfData::STRING )
      values = values + tupleRowsCopy->text + ":";
    else
      values = values + to_string( tupleRowsCopy->number ) + ":";

    tupleRowsCopy = tupleRowsCopy->next;
  }
  columns = columns + tupleRowsCopy->name;
  if( tupleRowsCopy->type == typeOfData::STRING )
    values = values + tupleRowsCopy->text;
  else
    values = values + to_string( tupleRowsCopy->number );
  insertInto( newTableName, columns, values );
}

typeRet selectWhere( string tableName, string condition, string newTableName ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  Tables table = findTable( newTableName );
  if( table != NULL ) {
    cout << "ERROR: La tabla '" << newTableName << "' ya existe." << endl;
    return typeRet::ERROR;
  }

  table = findTable( tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }
  // selectWhere(Persona,"",Pepes)

  createTable( newTableName );
  Tables newTable = findTable( newTableName );

  Tuple tableAttribuesCopy = table->attributes;
  while( tableAttribuesCopy != NULL ) {
    Tuple newAttribute        = new nodeElement;
    newAttribute->name        = tableAttribuesCopy->name;
    newAttribute->type        = tableAttribuesCopy->type;
    newAttribute->restriction = tableAttribuesCopy->restriction;
    newAttribute->next        = NULL;

    if( newTable->attributes == NULL ) newTable->attributes = newAttribute;
    else {
      Tuple newTableAttributesCopy = newTable->attributes;
      while( newTableAttributesCopy->next != NULL )
        newTableAttributesCopy = newTableAttributesCopy->next;
      newTableAttributesCopy->next = newAttribute;
    }
    tableAttribuesCopy = tableAttribuesCopy->next;
  }

  // TODO copy tuples
  if( condition.length( ) == 0 ) {
    Tuples tableTuplesCopy = table->tuple;
    while( tableTuplesCopy != NULL ) {
      insertRow( tableTuplesCopy, newTableName );
      tableTuplesCopy = tableTuplesCopy->next;
    }
  }

  cout << "";

  string conditionColumn, conditionValue;
  int option;
  if( condition.find( '=' ) != string::npos ) {
    splitCondition( condition, conditionColumn, conditionValue, "=", 1 );
    option = 0;
  } else if( condition.find( '<' ) != string::npos &&
             condition.find( '>' ) != string::npos ) {
    splitCondition( condition, conditionColumn, conditionValue, "<", 2 );
    option = 1;
  } else if( condition.find( '<' ) != string::npos ) {
    splitCondition( condition, conditionColumn, conditionValue, "<", 1 );
    option = 2;
  } else if( condition.find( '>' ) != string::npos ) {
    splitCondition( condition, conditionColumn, conditionValue, ">", 1 );
    option = 3;
  } else {
    cout << "ERROR: Debe ingresar un operador valido ('=', '<', '>' o '<>')."
         << endl;
    return typeRet::ERROR;
  }

  Tuples tableTuplesCopy = table->tuple;
  while( tableTuplesCopy != NULL ) {
    if( validCondition( newTable, tableTuplesCopy, option, conditionColumn,
                        conditionValue ) == 0 )
      insertRow( tableTuplesCopy, newTableName );
    tableTuplesCopy = tableTuplesCopy->next;
  }
  return typeRet::OK;
}
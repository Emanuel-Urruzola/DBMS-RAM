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

  if( newTableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la nueva tabla debe ser especificado." << endl;
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

  createTable( newTableName );
  Tables newTable = findTable( newTableName );

  Tuple tableAttributesCopy = table->attributes;
  while( tableAttributesCopy != NULL ) {
    Tuple newAttribute        = new nodeElement;
    newAttribute->name        = tableAttributesCopy->name;
    newAttribute->type        = tableAttributesCopy->type;
    newAttribute->restriction = tableAttributesCopy->restriction;
    newAttribute->next        = NULL;

    if( newTable->attributes == NULL ) newTable->attributes = newAttribute;
    else {
      Tuple newTableAttributesCopy = newTable->attributes;
      while( newTableAttributesCopy->next != NULL )
        newTableAttributesCopy = newTableAttributesCopy->next;
      newTableAttributesCopy->next = newAttribute;
    }
    tableAttributesCopy = tableAttributesCopy->next;
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

void addNewTableColumns( Tables oldTable, Tables &newTable, string columns ) {
  Tuple tableAttributesCopy = oldTable->attributes;
  while( tableAttributesCopy != NULL ) {
    size_t position;
    string columnsOrderCopy = columns;
    bool attributeFinded    = false;
    while( ( position = columnsOrderCopy.find( ":" ) ) != string::npos &&
           ! attributeFinded ) {
      string columnName = columnsOrderCopy.substr(
          0, columnsOrderCopy.length( ) - ( columnsOrderCopy.length( ) -
                                            columnsOrderCopy.find( ":" ) ) );

      if( tableAttributesCopy->name == columnName ) {
        Tuple newAttribute        = new nodeElement;
        newAttribute->name        = tableAttributesCopy->name;
        newAttribute->type        = tableAttributesCopy->type;
        newAttribute->restriction = tableAttributesCopy->restriction;
        newAttribute->next        = NULL;

        if( newTable->attributes == NULL ) newTable->attributes = newAttribute;
        else {
          Tuple newTableAttributesCopy = newTable->attributes;
          while( newTableAttributesCopy->next != NULL )
            newTableAttributesCopy = newTableAttributesCopy->next;
          newTableAttributesCopy->next = newAttribute;
        }
        attributeFinded = true;
      }
      columnsOrderCopy.erase( 0, position + 1 );
    }
    if( ! attributeFinded ) {
      string columnName = columnsOrderCopy.substr(
          0, columnsOrderCopy.length( ) - ( columnsOrderCopy.length( ) -
                                            columnsOrderCopy.find( ":" ) ) );
      if( tableAttributesCopy->name == columnName ) {
        Tuple newAttribute        = new nodeElement;
        newAttribute->name        = tableAttributesCopy->name;
        newAttribute->type        = tableAttributesCopy->type;
        newAttribute->restriction = tableAttributesCopy->restriction;
        newAttribute->next        = NULL;

        if( newTable->attributes == NULL ) newTable->attributes = newAttribute;
        else {
          Tuple newTableAttributesCopy = newTable->attributes;
          while( newTableAttributesCopy->next != NULL )
            newTableAttributesCopy = newTableAttributesCopy->next;
          newTableAttributesCopy->next = newAttribute;
        }
      }
    }
    tableAttributesCopy = tableAttributesCopy->next;
  }
}

typeRet select( string tableName, string columns, string newTableName ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  if( newTableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la nueva tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  if( columns.length( ) == 0 ) {
    cout << "ERROR: Debe especificar las columnas a proyectar." << endl;
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

  size_t position;
  string columnsOrderCopy = columns;
  bool columnNotFinded    = false;
  while( ( position = columnsOrderCopy.find( ":" ) ) != string::npos &&
         ! columnNotFinded ) {
    Tuple tableAttributesCopy = table->attributes;
    bool attributeFinded      = false;
    while( tableAttributesCopy != NULL && ! attributeFinded ) {
      if( tableAttributesCopy->name ==
          columnsOrderCopy.substr( 0, columnsOrderCopy.length( ) -
                                          ( columnsOrderCopy.length( ) -
                                            columnsOrderCopy.find( ":" ) ) ) )
        attributeFinded = true;
      else {
        tableAttributesCopy = tableAttributesCopy->next;
      }
    }
    if( tableAttributesCopy == NULL ) {
      cout << "ERROR: La columna '"
           << columnsOrderCopy.substr( 0, columnsOrderCopy.length( ) -
                                              ( columnsOrderCopy.length( ) -
                                                columnsOrderCopy.find( ":" ) ) )
           << "' no existe." << endl;
      return typeRet::ERROR;
    }

    columnsOrderCopy.erase( 0, position + 1 );
  }

  Tuple tableAttributesCopy = table->attributes;
  bool attributeFinded      = false;
  while( tableAttributesCopy != NULL && ! attributeFinded ) {
    if( tableAttributesCopy->name ==
        columnsOrderCopy.substr(
            0, columnsOrderCopy.length( ) - ( columnsOrderCopy.length( ) -
                                              columnsOrderCopy.find( ":" ) ) ) )
      attributeFinded = true;
    else {
      tableAttributesCopy = tableAttributesCopy->next;
    }
  }
  if( tableAttributesCopy == NULL ) {
    cout << "ERROR: La columna '"
         << columnsOrderCopy.substr( 0, columnsOrderCopy.length( ) -
                                            ( columnsOrderCopy.length( ) -
                                              columnsOrderCopy.find( ":" ) ) )
         << "' no existe." << endl;
    return typeRet::ERROR;
  }

  createTable( newTableName );
  Tables newTable = findTable( newTableName );
  addNewTableColumns( table, newTable, columns );

  Tuples tableTuplesCopy = table->tuple;
  while( tableTuplesCopy != NULL ) {
    string values      = "";
    Tuple tupleRowCopy = tableTuplesCopy->row;
    while( tupleRowCopy != NULL ) {
      Tuple newTableAttributes = newTable->attributes;
      while( newTableAttributes != NULL ) {
        if( newTableAttributes->name == tupleRowCopy->name ) {
          if( tupleRowCopy->type == typeOfData::STRING )
            values = values + tupleRowCopy->text + ":";
          else
            values = values + to_string( tupleRowCopy->number ) + ":";
        }
        newTableAttributes = newTableAttributes->next;
      }

      tupleRowCopy = tupleRowCopy->next;
    }

    insertInto( newTable->name, columns,
                values.substr( 0, values.length( ) - 1 ) );
    tableTuplesCopy = tableTuplesCopy->next;
  }

  return typeRet::OK;
}
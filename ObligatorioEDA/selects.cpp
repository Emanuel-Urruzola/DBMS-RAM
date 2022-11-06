#include <iostream>
#include "selects.h"
#include "variables.h"
#include "tables.h"
#include "tuples.h"

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

  Tables table = findTable( tablesList, newTableName );
  if( table != NULL ) {
    cout << "ERROR: La tabla '" << newTableName << "' ya existe." << endl;
    return typeRet::ERROR;
  }

  table = findTable( tablesList, tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }

  createTable( newTableName );
  Tables newTable = findTable( tablesList, newTableName );

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

  Tables table = findTable( tablesList, newTableName );
  if( table != NULL ) {
    cout << "ERROR: La tabla '" << newTableName << "' ya existe." << endl;
    return typeRet::ERROR;
  }

  table = findTable( tablesList, tableName );
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
          columnsOrderCopy.substr( 0, columnsOrderCopy.find( ":" ) ) )
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
        columnsOrderCopy.substr( 0, columnsOrderCopy.find( ":" ) ) )
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
  Tables newTable = findTable( tablesList, newTableName );
  addNewTableColumns( table, newTable, columns );

  Tuples tableTuplesCopy = table->tuple;
  while( tableTuplesCopy != NULL ) {
    string values      = "";
    string columnsCopy = columns;
    while( ( position = columnsCopy.find( ":" ) ) != string::npos ) {
      Tuple tupleRowCopy = tableTuplesCopy->row;
      while( tupleRowCopy != NULL ) {
        if( columnsCopy.substr( 0, columnsCopy.find( ":" ) ) ==
            tupleRowCopy->name ) {
          if( tupleRowCopy->type == typeOfData::STRING )
            values = values + tupleRowCopy->text + ":";
          else
            values = values + to_string( tupleRowCopy->number ) + ":";
        }
        tupleRowCopy = tupleRowCopy->next;
      }
      columnsCopy.erase( 0, position + 1 );
    }

    Tuple tupleRowCopy = tableTuplesCopy->row;
    while( tupleRowCopy != NULL ) {
      if( columnsCopy.substr( 0, columnsCopy.find( ":" ) ) ==
          tupleRowCopy->name ) {
        if( tupleRowCopy->type == typeOfData::STRING )
          values = values + tupleRowCopy->text + ":";
        else
          values = values + to_string( tupleRowCopy->number ) + ":";
      }
      tupleRowCopy = tupleRowCopy->next;
    }

    insertInto( newTable->name, columns,
                values.substr( 0, values.length( ) - 1 ) );
    tableTuplesCopy = tableTuplesCopy->next;
  }

  return typeRet::OK;
}

int matchColumnIndex( Tables table1, Tables table2 ) {
  int index, matchCounter = 0, counter = 0;

  Tuple table1AttributesCopy = table1->attributes;
  while( table1AttributesCopy != NULL ) {
    Tuple table2AttributesCopy = table2->attributes;
    bool attributeFinded       = false;
    while( table2AttributesCopy != NULL && ! attributeFinded ) {
      if( table1AttributesCopy->name == table2AttributesCopy->name &&
          table1AttributesCopy->restriction == typeOfRestriction::PRIMARY_KEY &&
          table2AttributesCopy->restriction == typeOfRestriction::PRIMARY_KEY &&
          table1AttributesCopy->type == table2AttributesCopy->type ) {
        index = counter;
        matchCounter++;
      }
      table2AttributesCopy = table2AttributesCopy->next;
    }
    counter++;
    table1AttributesCopy = table1AttributesCopy->next;
  }

  if( matchCounter == 0 ) return -1;
  if( matchCounter > 1 ) return -2;
  return index;
}

void addJoinColumns( Tables table1, Tables table2, Tables &newTable,
                     int matchIndex ) {
  // Add table 1 attributes
  int counter                = 0;
  Tuple table1AttributesCopy = table1->attributes;
  while( table1AttributesCopy != NULL ) {
    if( counter != matchIndex ) {
      Tuple newAttribute        = new nodeElement;
      newAttribute->name        = table1AttributesCopy->name;
      newAttribute->type        = table1AttributesCopy->type;
      newAttribute->restriction = table1AttributesCopy->restriction;
      newAttribute->next        = NULL;

      if( newTable->attributes == NULL ) newTable->attributes = newAttribute;
      else {
        Tuple newTableAttributesCopy = newTable->attributes;
        while( newTableAttributesCopy->next != NULL )
          newTableAttributesCopy = newTableAttributesCopy->next;
        newTableAttributesCopy->next = newAttribute;
      }
    }
    counter++;
    table1AttributesCopy = table1AttributesCopy->next;
  }

  // Add table 2 attributes
  Tuple table2AttributesCopy = table2->attributes;
  while( table2AttributesCopy != NULL ) {
    Tuple newAttribute        = new nodeElement;
    newAttribute->name        = table2AttributesCopy->name;
    newAttribute->type        = table2AttributesCopy->type;
    newAttribute->restriction = table2AttributesCopy->restriction;
    newAttribute->next        = NULL;

    if( newTable->attributes == NULL ) newTable->attributes = newAttribute;
    else {
      Tuple newTableAttributesCopy = newTable->attributes;
      while( newTableAttributesCopy->next != NULL )
        newTableAttributesCopy = newTableAttributesCopy->next;
      newTableAttributesCopy->next = newAttribute;
    }
    table2AttributesCopy = table2AttributesCopy->next;
  }
}

void addJoinTuples( Tables table1, Tables table2, Tables &newTable,
                    int matchIndex ) {
  string matchingColumn;
  string columns     = "";
  int counter        = 0;
  int columnsCounter = 0;
  // set columns order
  Tuple table1AttributesCopy = table1->attributes;
  while( table1AttributesCopy != NULL ) {
    if( counter != matchIndex ) {
      columns = columns + table1AttributesCopy->name + ":";
      columnsCounter++;
    } else
      matchingColumn = table1AttributesCopy->name;
    counter++;
    table1AttributesCopy = table1AttributesCopy->next;
  }
  Tuple table2ttributesCopy = table2->attributes;
  while( table2ttributesCopy->next != NULL ) {
    columns = columns + table2ttributesCopy->name + ":";
    columnsCounter++;
    table2ttributesCopy = table2ttributesCopy->next;
  }
  columns = columns + table2ttributesCopy->name;
  columnsCounter++;

  // add tuples
  Tuples table1TuplesCopy = table1->tuple;
  while( table1TuplesCopy != NULL ) {
    Tuple matchingRow    = nullptr;
    string values        = "";
    Tuple table1RowsCopy = table1TuplesCopy->row;
    while( table1RowsCopy != NULL ) {
      if( table1RowsCopy->name != matchingColumn ) {
        if( table1RowsCopy->type == typeOfData::STRING )
          values = values + table1RowsCopy->text + ":";
        else
          values = values + to_string( table1RowsCopy->number ) + ":";
      } else
        matchingRow = table1RowsCopy;
      table1RowsCopy = table1RowsCopy->next;
    }

    Tuples table2TuplesCopy = table2->tuple;
    bool tupleFinded        = false;

    while( table2TuplesCopy != NULL && ! tupleFinded ) {
      string auxValues     = "";
      bool tupleMatches    = false;
      Tuple table2RowsCopy = table2TuplesCopy->row;
      while( table2RowsCopy != NULL ) {
        if( table2RowsCopy->type == typeOfData::STRING )
          auxValues = auxValues + table2RowsCopy->text + ":";
        else
          auxValues = auxValues + to_string( table2RowsCopy->number ) + ":";
        if( table2RowsCopy->restriction == typeOfRestriction::PRIMARY_KEY ) {
          if( ( table2RowsCopy->type == typeOfData::STRING &&
                table2RowsCopy->text == matchingRow->text ) ||
              ( table2RowsCopy->type == typeOfData::INT &&
                table2RowsCopy->number == matchingRow->number ) )
            tupleMatches = true;
        }
        table2RowsCopy = table2RowsCopy->next;
      }
      if( tupleMatches ) values = values + auxValues;
      table2TuplesCopy = table2TuplesCopy->next;
    }
    int columnsCounterCopy = columnsCounter;
    string valuesCopy       = values;
    while( valuesCopy.substr( 0, valuesCopy.find( ":" ) ).length( ) > 0 ) {
      columnsCounterCopy--;
      valuesCopy.erase( 0, valuesCopy.find( ":" ) + 1 );
    }

    if( columnsCounterCopy == 0 ) 
      insertInto( newTable->name, columns,
                  values.substr( 0, values.length( ) - 1 ) );


    table1TuplesCopy = table1TuplesCopy->next;
  }
}

typeRet join( string table1Name, string table2Name, string newTableName ) {
  if( table1Name.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  Tables table1 = findTable( tablesList, table1Name );
  if( table1 == NULL ) {
    cout << "ERROR: La tabla '" << table1Name << "' no existe." << endl;
    return typeRet::ERROR;
  }

  if( table2Name.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  Tables table2 = findTable( tablesList, table2Name );
  if( table1 == NULL ) {
    cout << "ERROR: La tabla '" << table2Name << "' no existe." << endl;
    return typeRet::ERROR;
  }

  if( findTable( tablesList, newTableName ) != NULL ) {
    cout << "ERROR: La tabla '" << newTableName << "' ya existe." << endl;
    return typeRet::ERROR;
  }

  int matchIndex = matchColumnIndex( table1, table2 );

  if( matchIndex == -1 ) {
    cout << "ERROR: Las tablas '" << table1Name << "' y '" << table2Name
         << "' no tienen columnas en comun" << endl;
    return typeRet::ERROR;
  }

  if( matchIndex == -2 ) {
    cout << "ERROR: Las tablas '" << table1Name << "' y '" << table2Name
         << "' tienen mas de una columna en comun" << endl;
    return typeRet::ERROR;
  }

  createTable( newTableName );
  Tables newTable = findTable( tablesList, newTableName );
  addJoinColumns( table1, table2, newTable, matchIndex );
  addJoinTuples( table1, table2, newTable, matchIndex );

  return typeRet::OK;
}

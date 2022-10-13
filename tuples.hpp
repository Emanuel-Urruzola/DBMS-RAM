#ifndef tuples
#define tuples
#include <iostream>
#include <regex>
#include "variables.hpp"
#include "tables.hpp"
#include "operations.hpp"
#include "deleteHelpers.hpp"
using namespace std;

void splitCondition( string condition, string &column, string &value,
                     string splitter, int add ) {
  column = condition.substr( 0, condition.find( splitter ) );
  value  = condition.substr( condition.find( splitter ) + add,
                            condition.length( ) - condition.find( splitter ) );
}

bool validColumns( string columnsOrder, Tables table ) {
  size_t position;
  int userAttributesCounter = 0;
  //  TODO: Check possible double name in columns
  //  TODO: Validate types and restrictions
  // TODO: Last column from columnsOrder is not entering
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
  Tuple tableAttributesCopy = table->attributes;
  while( tableAttributesCopy->next != NULL )
    tableAttributesCopy = tableAttributesCopy->next;

  if( userAttributesCounter == tableAttributesCopy->index ) return true;
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
        newTuple->name        = tableAttributesCopy->name;
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
  int index        = 0;
  Tuple attributes = table->attributes;
  while( attributes != NULL ) {
    index++;
    if( attributes->name == columnName ) return index;
    attributes = attributes->next;
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

typeRet replaceInRow( Tuple rowCopy, string columnToModify,
                      string valueModified, typeOfData type ) {
  bool modified = false;
  const regex regExpNumber( "^[\\d]+$" );
  while( rowCopy != NULL && ! modified ) {
    if( rowCopy->name == columnToModify ) {
      if( rowCopy->type == STRING ) {
        rowCopy->text = valueModified;
        modified      = true;
      } else {
        if( regex_match( valueModified, regExpNumber ) ) {
          rowCopy->number = stoi( valueModified );
          modified        = true;
        } else {
          return ERROR;
        }
      }
    }
    rowCopy = rowCopy->next;
  }
  return OK;
}

typeRet findMatches( Tables table, int index, string value, typeOfData type,
                     string columnToModify, string valueModified,
                     int condition ) {
  Tuples tuple = table->tuple;
  bool finded;
  if( type == STRING ) value = value.substr( 1, value.length( ) - 2 );
  while( tuple != NULL ) {
    Tuple row     = tuple->row;
    Tuple rowCopy = tuple->row;
    for( int i = 1; i < index; i++ ) row = row->next;
    switch( condition ) {
      case 0:
        if( row->text == value ) {
          if( replaceInRow( rowCopy, columnToModify, valueModified, type ) ==
              ERROR )
            return ERROR;
        }
        break;
      case 1:
        if( row->text != value )
          if( replaceInRow( rowCopy, columnToModify, valueModified, type ) ==
              ERROR )
            return ERROR;
        break;
      case 2:
        if( row->text < value )
          if( replaceInRow( rowCopy, columnToModify, valueModified, type ) ==
              ERROR )
            return ERROR;
        break;
      case 3:
        if( row->text < value )
          if( replaceInRow( rowCopy, columnToModify, valueModified, type ) ==
              ERROR )
            return ERROR;
        break;
      default:
        break;
    }
    tuple = tuple->next;
  }
  return OK;
}

typeOfData findTypeColumn( Tables table, int index ) {
  Tuple attributes = table->attributes;
  for( int i = 1; i < index; i++ ) attributes = attributes->next;
  return attributes->type;
}

// update (Personas,Nombre=”Pepe”,CI,1555000);
typeRet update( string tableName, string whereCondition, string columnToModify,
                string newValue ) {
  Tables table = findTable( tableName );
  if( table == NULL ) return ERROR;  // if table no exist
  if( findColumn( table, columnToModify ) == ERROR )
    return ERROR;  // if column to modify no exist
  const regex regExpString( "[\"'”].+[\"'”]" );
  const regex regExpNumber( "^[\\d]+$" );
  string column, value;
  int option;
  if( whereCondition.find( '=' ) != string::npos ) {
    splitCondition( whereCondition, column, value, "=", 1 );
    option = 0;
  } else if( whereCondition.find( '<' ) != string::npos &&
             whereCondition.find( '>' ) != string::npos ) {
    splitCondition( whereCondition, column, value, "<", 2 );
    option = 1;
  } else if( whereCondition.find( '<' ) != string::npos ) {
    splitCondition( whereCondition, column, value, "<", 1 );
    option = 2;
  } else if( whereCondition.find( '>' ) != string::npos ) {
    splitCondition( whereCondition, column, value, ">", 1 );
    option = 3;
  } else {
    cout << "Debe ingresar un operador valido ('=', '<', '>' o '<>')." << endl;
    return ERROR;
  }
  int index = WhereConditionColumn( table,
                                    column );  // Get the position of attribute
  if( index == -1 ) return ERROR;              // If the position doesn't found
  typeOfData type = findTypeColumn( table, index );
  if( ( type == INT && regex_match( value, regExpNumber ) ) ||
      ( type == STRING && regex_match( value, regExpString ) ) ) {
    if( findMatches( table, index, value, type, columnToModify, newValue,
                     option ) == ERROR )
      return ERROR;
  } else {
    cout << "Recuerde poner comillas para columnas de tipo STRING y no "
            "poner "
            "comillas para tipo INT"
         << endl;
    return ERROR;
  }
  return OK;
}

// DELETE QUERY

int validCondition( Tables table, Tuples tuple, int option, string column,
                    string value ) {
  bool columnExists         = false;
  Tuple tableAttributesCopy = table->attributes;
  while( tableAttributesCopy != NULL && ! columnExists ) {
    if( tableAttributesCopy->name == column ) columnExists = true;
    else
      tableAttributesCopy = tableAttributesCopy->next;
  }
  if( columnExists ) {
    Tuple tupleRowCopy = tuple->row;
    for( int i = 0; i < tableAttributesCopy->index; i++ )
      tupleRowCopy = tupleRowCopy->next;

    switch( option ) {
      case 0:
        if( tupleRowCopy->text == value.substr( 1, value.length( ) - 2 ) )
          return 0;
        break;
      case 1:
        if( tupleRowCopy->text < value.substr( 1, value.length( ) - 2 ) )
          return 0;
        break;
      case 2:
        if( tupleRowCopy->text != value.substr( 1, value.length( ) - 2 ) )
          return 0;
        break;
      case 3:
        if( tupleRowCopy->text > value.substr( 1, value.length( ) - 2 ) )
          return 0;
        break;
    }
  } else {
    return 2;
  }
  return 1;
}

typeRet deleteQuery( string tableName, string condition ) {
  if( tableName.length( ) == 0 ) {
    cout << "La columna debe ser especificada." << endl;
    return ERROR;
  }

  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "La tabla '" << tableName << "' no existe." << endl;
    return ERROR;
  }

  if( condition.length( ) == 0 ) {
    deleteAllTuples( table->tuple );
    return OK;
  }

  string column, value;
  int option;
  if( condition.find( '=' ) != string::npos ) {
    splitCondition( condition, column, value, "=", 1 );
    option = 0;
  } else if( condition.find( '<' ) != string::npos &&
             condition.find( '>' ) != string::npos ) {
    splitCondition( condition, column, value, "<", 2 );
    option = 1;
  } else if( condition.find( '<' ) != string::npos ) {
    splitCondition( condition, column, value, "<", 1 );
    option = 2;
  } else if( condition.find( '>' ) != string::npos ) {
    splitCondition( condition, column, value, ">", 1 );
    option = 3;
  } else {
    cout << "Debe ingresar un operador valido ('=', '<', '>' o '<>')." << endl;
    return ERROR;
  }

  bool first = true;
  while( first ) {
    int conditionStatus =
        validCondition( table, table->tuple, option, column, value );
    if( conditionStatus == 0 ) {
      deleteAllRows( table->tuple->row );
      Tuples aux   = table->tuple;
      table->tuple = table->tuple->next;
      delete aux;
    } else if( conditionStatus == 1 )
      first = false;
    else if( conditionStatus == 2 ) {
      cout << "La columna '" << column << "' no existe." << endl;
      return ERROR;
    }
  }

  Tuples tableTuplesCopy = table->tuple;
  while( tableTuplesCopy->next != NULL ) {
    int conditionStatus =
        validCondition( table, tableTuplesCopy->next, option, column, value );
    if( conditionStatus == 0 ) {
      deleteNextTuple( tableTuplesCopy );
    } else if( conditionStatus == 1 ) {
      tableTuplesCopy = tableTuplesCopy->next;
    } else if( conditionStatus == 2 ) {
      cout << "La columna '" << column << "' no existe." << endl;
      return ERROR;
    }
  }

  int conditionStatus =
      validCondition( table, table->tuple, option, column, value );
  if( conditionStatus == 0 ) {
    deleteAllRows( table->tuple->row );
    Tuples aux   = table->tuple;
    table->tuple = table->tuple->next;
    delete aux;
  } else if( conditionStatus == 2 ) {
    cout << "La columna '" << column << "' no existe." << endl;
    return ERROR;
  }

  return OK;
}

#endif  // !tuples
#include <iostream>
#include <regex>
#include "tuples.h"
#include "variables.h"
#include "tables.h"
#include "operations.h"
#include "deleteHelpers.h"

using namespace std;

void splitCondition( string condition, string& column, string& value,
                     string splitter, int add ) {
  column = condition.substr( 0, condition.find( splitter ) );
  value  = condition.substr( condition.find( splitter ) + add,
                             condition.length( ) - condition.find( splitter ) );
}

bool validColumns( string columnsOrder, Tables table ) {
  size_t position;
  int userAttributesCounter = 0;
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
  int attributesCounter     = 0;
  if( tableAttributesCopy->next == NULL ) attributesCounter++;

  while( tableAttributesCopy->next != NULL ) {
    attributesCounter++;
    tableAttributesCopy = tableAttributesCopy->next;
  }
  if( userAttributesCounter == attributesCounter ) return true;
  return false;
}

typeRet insertInto( string tableName, string columnsOrder,
                    string columnValues ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  Tables table = findTable( tablesList, tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }

  if( ! ( validColumns( columnsOrder, table ) ) ) {
    cout << "ERROR: Columna no existente." << endl;
    return typeRet::ERROR;
  }
  if( table->attributes == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no tiene columnas." << endl;
    return typeRet::ERROR;
  }

  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }

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
    } else
      // caso de que sea la primer tupla a ingresar.
      table->tuple = newRow;

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
                           columnsOrderCopy.find( ":" ) ) ) ) )
          finded = true;
        else {
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
      Tuple newTuple = new nodeElement;
      newTuple->next = NULL;
      newTuple->type = tableAttributesCopy->type;
      if( tableAttributesCopy->type == typeOfData::INT ) {
        newTuple->number = stoi( columnValuesCopy );
      } else {
        newTuple->text = columnValuesCopy;
      }
      newTuple->restriction = tableAttributesCopy->restriction;
      // Chequea si la PRIMARY KEY ya existe.
      if( tableAttributesCopy->restriction == typeOfRestriction::PRIMARY_KEY ) {
        Tuples tupleCopy = table->tuple;
        while( tupleCopy != NULL ) {
          Tuple rowCopy = table->tuple->row;
          while( rowCopy != NULL ) {
            if( rowCopy->restriction == typeOfRestriction::PRIMARY_KEY ) {
              if( ( rowCopy->type == typeOfData::INT &&
                    rowCopy->number == newTuple->number ) ||
                  ( rowCopy->type == typeOfData::STRING &&
                    rowCopy->text == newTuple->text ) ) {
                cout << "ERROR: Primary key existente." << endl;
                return typeRet::ERROR;
              } else {
                rowCopy = rowCopy->next;
              }
            } else {
              rowCopy = rowCopy->next;
            }
          }
          tupleCopy = tupleCopy->next;
        }
      }
      newTuple->name = tableAttributesCopy->name;
      if( newRow->row == NULL ) newRow->row = newTuple;
      else {
        Tuple rowCopy = newRow->row;
        while( rowCopy->next != NULL ) rowCopy = rowCopy->next;

        rowCopy->next = newTuple;
      }
      tableAttributesCopy = tableAttributesCopy->next;
    }
  }

  return typeRet::OK;
}

int whereConditionColumn( Tables table, string columnName ) {
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
  if( table == NULL ) return typeRet::ERROR;
  Tuple attributes = table->attributes;
  while( attributes != NULL ) {
    if( attributes->name == columnName ) return typeRet::OK;
    attributes = attributes->next;
  }
  return typeRet::ERROR;
}

int findIndexColumn( Tables table, string columnName ) {
  if( table == NULL ) return 0;
  int index        = 0;
  Tuple attributes = table->attributes;
  if( columnName.compare( "\"\"" ) ) {
    while( attributes != NULL ) {
      index++;
      if( attributes->name == columnName ) return index;
      attributes = attributes->next;
    }
  } else {
    while( attributes->next != NULL ) {
      index++;
      if( attributes->restriction == typeOfRestriction::PRIMARY_KEY )
        return index;
      attributes = attributes->next;
    }
    index++;
    return index;
  }
  return 0;
}

typeRet getRows( Tuple& row, string columnToModify,
                 typeOfRestriction& restriction, Tuples& rowsToModified ) {
  rowsToModified = insFrontTuples( rowsToModified, row );
  Tuple rowCopy  = row;
  while( rowCopy->name != columnToModify ) rowCopy = rowCopy->next;
  restriction = rowCopy->restriction;
  return typeRet::OK;
}

typeRet findMatches( Tables table, int index, string value, typeOfData type,
                     string columnToModify, string valueModified,
                     int condition ) {
  Tuples tuple = table->tuple;
  bool isEmpty = ! value.compare( "\"\"" );
  if( type == typeOfData::STRING && ! isEmpty )
    value = value.substr( 1, value.length( ) - 2 );
  Tuples rowsToModify = NULL;
  typeOfRestriction restriction;
  while( tuple != NULL ) {
    Tuple row     = tuple->row;
    Tuple rowCopy = tuple->row;
    for( int i = 1; i < index; i++ ) row = row->next;
    switch( condition ) {
      case 0:
        if( ( type == typeOfData::STRING && ! row->text.compare( value ) ) ||
            isEmpty ||
            ( type == typeOfData::INT && row->number == stoi( value ) ) ) {
          if( getRows( rowCopy, columnToModify, restriction, rowsToModify ) ==
              typeRet::ERROR )
            return typeRet::ERROR;
        }
        break;
      case 1:
        if( ( type == typeOfData::STRING && row->text.compare( value ) ) ||
            isEmpty ||
            ( type == typeOfData::INT && row->number != stoi( value ) ) )
          if( getRows( rowCopy, columnToModify, restriction, rowsToModify ) ==
              typeRet::ERROR )
            return typeRet::ERROR;
        break;
      case 2:
        if( ( type == typeOfData::STRING &&
              row->text.compare( value ) == -1 ) ||
            isEmpty ||
            ( type == typeOfData::INT && row->number < stoi( value ) ) )
          if( getRows( rowCopy, columnToModify, restriction, rowsToModify ) ==
              typeRet::ERROR )
            return typeRet::ERROR;
        break;
      case 3:
        if( ( type == typeOfData::STRING && row->text.compare( value ) == 1 ) ||
            isEmpty ||
            ( type == typeOfData::INT && row->number > stoi( value ) ) )
          if( getRows( rowCopy, columnToModify, restriction, rowsToModify ) ==
              typeRet::ERROR )
            return typeRet::ERROR;
        break;
      default:
        break;
    }
    tuple = tuple->next;
  }
  const regex regExpNumber( "^[\\d]+$" );
  tuple       = table->tuple;
  int counter = 0;
  if( rowsToModify == NULL )
    return typeRet::OK;  // If the table doesn't have tuples, is not a ERROR
  else if( rowsToModify->next != NULL ) {
    if( restriction == typeOfRestriction::PRIMARY_KEY ) return typeRet::ERROR;
    else {
      while( rowsToModify != NULL ) {
        Tuple rowToModify = rowsToModify->row;
        while( rowToModify->name != columnToModify )
          rowToModify = rowToModify->next;
        if( rowToModify->type == typeOfData::STRING )
          rowToModify->text = valueModified;
        else
          rowToModify->number = stoi( valueModified );
        rowsToModify = rowsToModify->next;
      }
    }
  } else {
    while( tuple != NULL ) {
      Tuple row = tuple->row;
      while( row->name != columnToModify ) row = row->next;
      while( rowsToModify->row->name != columnToModify )
        rowsToModify->row = rowsToModify->row->next;
      if( row->type == typeOfData::STRING ) {
        if( row->text == valueModified ) {
          if( row != rowsToModify->row &&
              restriction == typeOfRestriction::PRIMARY_KEY )
            return typeRet::ERROR;
        }
      } else {
        if( regex_match( valueModified, regExpNumber ) &&
            row->number == stoi( valueModified ) ) {
          if( row != rowsToModify->row &&
              restriction == typeOfRestriction::PRIMARY_KEY )
            return typeRet::ERROR;
        }
      }
      tuple = tuple->next;
    }
    if( rowsToModify->row->type == typeOfData::STRING )
      rowsToModify->row->text = valueModified;
    else {
      if( regex_match( valueModified, regExpNumber ) ) {
        rowsToModify->row->number = stoi( valueModified );
      } else {
        cout << "ERROR: Solo se pueden asignar numeros enteros a columna de "
                "tipo integer";
        return typeRet::ERROR;
      }
    }
    tuple = table->tuple;
  }
  return typeRet::OK;
}

typeOfData findTypeColumn( Tables table, int index ) {
  Tuple attributes = table->attributes;
  for( int i = 1; i < index; i++ ) attributes = attributes->next;
  return attributes->type;
}

int divideCondition( string condition, string& column, string& value,
                     int& option ) {
  if( condition.find( '=' ) != string::npos ) {
    splitCondition( condition, column, value, "=", 1 );
    option = 0;
  }
  if( condition.find( '<' ) != string::npos &&
      condition.find( '>' ) != string::npos ) {
    splitCondition( condition, column, value, "<", 2 );
    option = 1;
  }
  if( condition.find( '<' ) != string::npos ) {
    splitCondition( condition, column, value, "<", 1 );
    option = 2;
  }
  if( condition.find( '>' ) != string::npos ) {
    splitCondition( condition, column, value, ">", 1 );
    option = 3;
  }
  cout << "ERROR: Debe ingresar un operador valido ('=', '<', '>' o '<>')."
       << endl;
  return option;
}

typeRet update( string tableName, string whereCondition, string columnToModify,
                string newValue ) {
  if( ! tableName.length( ) ) {
    cout << "ERROR: Debe especificar nombre de tabla" << endl;
    return typeRet::ERROR;
  }
  if( ! columnToModify.length( ) ) {
    cout << "ERROR: Debe especificar nombre de la columna a modificar" << endl;
    return typeRet::ERROR;
  }
  if( ! newValue.length( ) ) {
    cout << "ERROR: Debe especificar el valor nuevo de la columna a modificar"
         << endl;
    return typeRet::ERROR;
  }
  Tables table = findTable( tablesList, tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla a modificar no existe" << endl;
    return typeRet::ERROR;
  }
  if( findColumn( table, columnToModify ) == typeRet::ERROR ) {
    cout << "ERROR: La columna a modificar no existe" << endl;
    return typeRet::ERROR;
  }
  const regex regExpString(
      "[\"'�].+[\"'�]" );  // Checking that string is between different types
  // of quotes
  const regex regExpNumber( "^[\\d]+$" );  // Start and end with number
  string column, value;
  int option = -1;
  if( divideCondition( whereCondition, column, value, option ) == -1 )
    return typeRet::ERROR;
  int index = whereConditionColumn( table,
                                    column );  // Get the position of attribute
  if( index == -1 ) {                          // If the position doesn't found
    cout << "ERROR: La columna '" << column << "' no existe." << endl;
    return typeRet::ERROR;
  }
  typeOfData type = findTypeColumn( table, index );
  if( ( type == typeOfData::INT && regex_match( value, regExpNumber ) ) ||
      ( type == typeOfData::STRING && regex_match( value, regExpString ) ) ||
      ! value.compare(
          "\"\"" ) ) {  // if is int it can only have number, if is string has
    // to have quotes, or if is "" it passes
    if( findMatches( table, index, value, type, columnToModify, newValue,
                     option ) == typeRet::ERROR ) {
      cout << "ERROR: Una columna del tipo PRIMARY KEY no puede tener "
              "elementos repetidos"
           << endl;
      return typeRet::ERROR;
    }
  } else {
    cout << "ERROR: Recuerde poner comillas para columnas de tipo STRING y no "
            "poner "
            "comillas para tipo INT"
         << endl;
    return typeRet::ERROR;
  }
  return typeRet::OK;
}

int columnExists( Tables table, string columnName ) {
  Tuple tableAttributesCopy = table->attributes;
  int index                 = 0;
  while( tableAttributesCopy != NULL ) {
    if( tableAttributesCopy->name == columnName ) return index;
    else
      tableAttributesCopy = tableAttributesCopy->next;
    index++;
  }
  return -1;
}

int validCondition( Tables table, Tuples tuple, int option, string column,
                    string value ) {
  int columnIndex = columnExists( table, column );
  if( columnIndex != -1 ) {
    Tuple tupleRowCopy = tuple->row;
    for( int i = 0; i < columnIndex; i++ ) tupleRowCopy = tupleRowCopy->next;

    if( value != "EMPTY" ) {
      switch( option ) {
        case 0:
          if( tupleRowCopy->type == typeOfData::STRING ) {
            if( tupleRowCopy->text.compare(
                    value.substr( 1, value.length( ) - 2 ) ) == 0 )
              return 0;
          } else if( tupleRowCopy->number == stoi( value ) )
            return 0;
          break;
        case 1:
          if( tupleRowCopy->type == typeOfData::STRING ) {
            if( tupleRowCopy->text.compare(
                    value.substr( 1, value.length( ) - 2 ) ) != 0 )
              return 0;
          } else if( tupleRowCopy->number != stoi( value ) )
            return 0;
          break;
        case 2:
          if( tupleRowCopy->type == typeOfData::STRING ) {
            if( tupleRowCopy->text.compare(
                    value.substr( 1, value.length( ) - 2 ) ) < 0 )
              return 0;
          } else if( tupleRowCopy->number < stoi( value ) )
            return 0;
          break;
        case 3:
          if( tupleRowCopy->type == typeOfData::STRING ) {
            if( tupleRowCopy->text.compare(
                    value.substr( 1, value.length( ) - 2 ) ) > 0 )
              return 0;
          } else if( tupleRowCopy->number > stoi( value ) )
            return 0;
          break;
      }
    } else {
      if( tupleRowCopy->restriction != typeOfRestriction::NOT_EMPTY ) {
        switch( option ) {
          case 0:
            if( tupleRowCopy->type == typeOfData::STRING ) {
              if( tupleRowCopy->text.length( ) == 0 ) return 0;
            } else if( tupleRowCopy->number == -1 )
              return 0;
            break;
          case 2:
            if( tupleRowCopy->type == typeOfData::STRING ) {
              if( tupleRowCopy->text.length( ) != 0 ) return 0;
            } else if( tupleRowCopy->number != -1 )
              return 0;
            break;
        }
      }
    }
  } else
    return 2;
  return 1;
}

typeRet deleteQuery( string tableName, string condition ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  Tables table = findTable( tablesList, tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }

  if( condition.length( ) == 0 ) {
    deleteAllTuples( table->tuple );
    return typeRet::OK;
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
    cout << "ERROR: Debe ingresar un operador valido ('=', '<', '>' o '<>')."
         << endl;
    return typeRet::ERROR;
  }

  bool first = true;
  while( first && table->tuple != NULL ) {
    int conditionStatus =
        validCondition( table, table->tuple, option, column, value );
    if( conditionStatus == 0 ) deleteTuple( table->tuple );
    else if( conditionStatus == 1 )
      first = false;
    else if( conditionStatus == 2 ) {
      cout << "ERROR: La columna '" << column << "' no existe." << endl;
      return typeRet::ERROR;
    }
  }
  if( table->tuple != NULL ) {
    Tuples tableTuplesCopy = table->tuple;
    Tuples previousTuple   = tableTuplesCopy;
    while( tableTuplesCopy != NULL && tableTuplesCopy->next != NULL ) {
      int conditionStatus =
          validCondition( table, tableTuplesCopy->next, option, column, value );
      if( conditionStatus == 0 ) deleteNextTuple( tableTuplesCopy );
      else if( conditionStatus == 1 ) {
        if( previousTuple != tableTuplesCopy )
          previousTuple = previousTuple->next;
        tableTuplesCopy = tableTuplesCopy->next;
      } else if( conditionStatus == 2 ) {
        cout << "ERROR: La columna '" << column << "' no existe." << endl;
        return typeRet::ERROR;
      }
    }
    if( tableTuplesCopy != NULL ) {
      int conditionStatus =
          validCondition( table, tableTuplesCopy, option, column, value );
      if( conditionStatus == 0 ) {
        deleteNextTuple( previousTuple );
      } else if( conditionStatus == 2 ) {
        cout << "ERROR: La columna '" << column << "' no existe." << endl;
        return typeRet::ERROR;
      }
    }
  }

  return typeRet::OK;
}
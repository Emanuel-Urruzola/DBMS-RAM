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
  while( tableAttributesCopy->next != NULL ) {
    attributesCounter++;
    tableAttributesCopy = tableAttributesCopy->next;
  }
  if( userAttributesCounter == attributesCounter ) return true;
  return false;
}

typeRet InsertInto( string tableName, string columnsOrder,
                    string columnValues ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: Ingrese un nombre de tabla!." << endl;
    return ERROR;
  }
  Tables table = findTable( tableName );
  if(!(validColumns(columnsOrder, table))){
    cout<<"ERROR: Columna no existente, ingrese nuevamente!."<<endl;
    return ERROR;
  }
  if( table->attributes == NULL ) {
    cout << "ERROR: La tabla ingresada no tiene columnas!." << endl;
    return ERROR;
  }
  if( table == NULL ) {
    cout << "ERROR: La tabla ingresada no existe!." << endl;
    return ERROR;
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
        // caso de que sea la primer tupla a ingresar.
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
        Tuple newTuple = new nodeElement;
        newTuple->next = NULL;
        newTuple->type = tableAttributesCopy->type;
        if( tableAttributesCopy->type == INT ) {
          newTuple->number = stoi( columnValuesCopy );
        } else {
          newTuple->text = columnValuesCopy;
        }
        newTuple->restriction = tableAttributesCopy->restriction;
        // Chequea si la PRIMARY KEY ya existe.
        if( tableAttributesCopy->restriction == PRIMARY_KEY ) {
          Tuples tupleCopy = table->tuple;
          while( tupleCopy != NULL ) {
            Tuple rowCopy = table->tuple->row;
            while( rowCopy != NULL ) {
              if( rowCopy->restriction == PRIMARY_KEY ) {
                if( rowCopy->number == newTuple->number ) {
                  cout << "ERROR: Primary key existente!." << endl;
                  return ERROR;
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
  return OK;
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
  cout << columnName << " and "
       << "\"\"" << endl;
  if( columnName.compare( "\"\"" ) ) {
    while( attributes != NULL ) {
      index++;
      if( attributes->name == columnName ) return index;
      attributes = attributes->next;
    }
  } else {
    while( attributes->next != NULL ) {
      index++;
      if( attributes->restriction == PRIMARY_KEY ) return index;
      attributes = attributes->next;
    }
    index++;
    return index;
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
  bool isEmpty = ! value.compare( "\"\"" );
  if( type == STRING && ! isEmpty )
    value = value.substr( 1, value.length( ) - 2 );
  while( tuple != NULL ) {
    Tuple row     = tuple->row;
    Tuple rowCopy = tuple->row;
    for( int i = 1; i < index; i++ ) row = row->next;
    switch( condition ) {
      case 0:
        if( type == STRING && ! row->text.compare( value ) || isEmpty ||
            type == INT && row->number == stoi( value ) ) {
          if( replaceInRow( rowCopy, columnToModify, valueModified, type ) ==
              ERROR )
            return ERROR;
        }
        break;
      case 1:
        if( type == STRING && row->text.compare( value ) || isEmpty ||
            type == INT && row->number != stoi( value ) )
          if( replaceInRow( rowCopy, columnToModify, valueModified, type ) ==
              ERROR )
            return ERROR;
        break;
      case 2:
        if( type == STRING && row->text.compare( value ) == -1 || isEmpty ||
            type == INT && row->number < stoi( value ) )
          if( replaceInRow( rowCopy, columnToModify, valueModified, type ) ==
              ERROR )
            return ERROR;
        break;
      case 3:
        if( type == STRING && row->text.compare( value ) == 1 || isEmpty ||
            type == INT && row->number > stoi( value ) )
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

typeRet update( string tableName, string whereCondition, string columnToModify,
                string newValue ) {
  // TODO: PRIMARY KEY cannot be repeated
  Tables table = findTable( tableName );
  if( table == NULL ) return ERROR;  // if table no exist
  if( findColumn( table, columnToModify ) == ERROR )
    return ERROR;  // if column to modify no exist
  const regex regExpString(
      "[\"'”].+[\"'”]" );  // Checking that string is between different types of
                           // quotes
  const regex regExpNumber( "^[\\d]+$" );  // Start and end with number
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
  if( index == -1 ) {                          // If the position doesn't found
    cout << "La columna asociada a la condicion no se encontro" << endl;
    return ERROR;
  }
  typeOfData type = findTypeColumn( table, index );
  if( ( type == INT && regex_match( value, regExpNumber ) ) ||
      ( type == STRING && regex_match( value, regExpString ) ) ||
      ! value.compare(
          "\"\"" ) ) {  // if is int it can only have number, if is string has
                        // to have quotes, or if is "" it passes
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

int columnExists( Tables table, string columnName ) {
  Tuple tableAttributesCopy = table->attributes;
  while( tableAttributesCopy != NULL ) {
    if( tableAttributesCopy->name == columnName )
      return tableAttributesCopy->index;
    else
      tableAttributesCopy = tableAttributesCopy->next;
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
          if( tupleRowCopy->type == STRING ) {
            if( tupleRowCopy->text.compare(
                    value.substr( 1, value.length( ) - 2 ) ) == 0 )
              return 0;
          } else if( tupleRowCopy->number == stoi( value ) )
            return 0;
          break;
        case 1:
          if( tupleRowCopy->type == STRING ) {
            if( tupleRowCopy->text.compare(
                    value.substr( 1, value.length( ) - 2 ) ) != 0 )
              return 0;
          } else if( tupleRowCopy->number != stoi( value ) )
            return 0;
          break;
        case 2:
          if( tupleRowCopy->type == STRING ) {
            if( tupleRowCopy->text.compare(
                    value.substr( 1, value.length( ) - 2 ) ) < 0 )
              return 0;
          } else if( tupleRowCopy->number < stoi( value ) )
            return 0;
          break;
        case 3:
          if( tupleRowCopy->type == STRING ) {
            if( tupleRowCopy->text.compare(
                    value.substr( 1, value.length( ) - 2 ) ) > 0 )
              return 0;
          } else if( tupleRowCopy->number > stoi( value ) )
            return 0;
          break;
      }
    } else {
      if( tupleRowCopy->restriction != NOT_EMPTY ) {
        switch( option ) {
          case 0:
            if( tupleRowCopy->type == STRING ) {
              if( tupleRowCopy->text.length( ) == 0 ) return 0;
            } else if( tupleRowCopy->number == -1 )
              return 0;
            break;
          case 2:
            if( tupleRowCopy->type == STRING ) {
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
  while( first && table->tuple != NULL ) {
    int conditionStatus =
        validCondition( table, table->tuple, option, column, value );
    if( conditionStatus == 0 ) deleteTuple( table->tuple );
    else if( conditionStatus == 1 )
      first = false;
    else if( conditionStatus == 2 ) {
      cout << "La columna '" << column << "' no existe." << endl;
      return ERROR;
    }
  }
  if( table->tuple != NULL ) {
    Tuples tableTuplesCopy = table->tuple;
    Tuples previousTuple   = tableTuplesCopy;
    while( tableTuplesCopy != NULL && tableTuplesCopy->next != NULL ) {
      int conditionStatus =
          validCondition( table, tableTuplesCopy->next, option, column, value );
      if( conditionStatus == 0 ) {
        deleteNextTuple( tableTuplesCopy );
      } else if( conditionStatus == 1 ) {
        if( previousTuple != tableTuplesCopy )
          previousTuple = previousTuple->next;

        tableTuplesCopy = tableTuplesCopy->next;
      } else if( conditionStatus == 2 ) {
        cout << "La columna '" << column << "' no existe." << endl;
        return ERROR;
      }
    }
    if( tableTuplesCopy != NULL ) {
      int conditionStatus =
          validCondition( table, tableTuplesCopy, option, column, value );
      if( conditionStatus == 0 ) {
        deleteNextTuple( previousTuple );
      } else if( conditionStatus == 2 ) {
        cout << "La columna '" << column << "' no existe." << endl;
        return ERROR;
      }
    }
  }

  return OK;
}

#endif  // !tuples
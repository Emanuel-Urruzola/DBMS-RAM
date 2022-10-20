#ifndef columns
#define columns
#include <regex>
#include "tables.hpp"
#include "variables.hpp"
#include "tuples.hpp"

// TODO: Validar el caso de que
// exista almenos una tupla. Tambien validar que en el caso de que existan
// tuplas no pueden tener restriction != de ANY
typeRet AddCol( string tableName, string columnName, string columnType,
                string restriction ) {
  typeOfData colType;
  typeOfRestriction colRestriction;

  if( columnType == "string" ) {
    colType = STRING;
  } else if( columnType == "integer" ) {
    colType = INT;
  } else {
    cout << "El tipo de dato " << columnType << " no es valido." << endl;
    return ERROR;
  }
  if( restriction == "PRIMARY_KEY" ) {
    colRestriction = PRIMARY_KEY;
  } else if( restriction == "ANY" ) {
    colRestriction = ANY;
  } else if( restriction == "NOT_EMPTY" ) {
    colRestriction = NOT_EMPTY;
  } else {
    // TODO: Steven error
    return ERROR;
  }
  if( columnType != "string" && columnType != "integer" ) {
    cout << "ERROR: Ingrese tipo de dato válido." << endl;
    return ERROR;
  }
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: Ingrese un nombre de tabla." << endl;
    return ERROR;
  }
  // Si nombre de la columna no se especifica.
  if( columnName.length( ) == 0 ) {
    cout << "ERROR: Ingrese un nombre de columna." << endl;
    return ERROR;
  }

  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla no existe.";
    return ERROR;
  } else {
    Tuple column = new nodeElement;
    column->name = columnName;
    column->type = colType;
    if( table->tuple != NULL ) {
      if( colRestriction != ANY ) {
        cout << "ERROR: El calificador debe ser ANY!." << endl;
        return ERROR;
      } else {
        column->restriction   = colRestriction;
        Tuple newTuple        = new nodeElement;
        newTuple->next        = NULL;
        newTuple->name        = columnName;
        newTuple->type        = colType;
        newTuple->restriction = colRestriction;
        if( colType == INT ) {
          newTuple->number = -1;
        } else {
          newTuple->text = "";
        }
        Tuples aux = table->tuple;
        while( aux != NULL ) {
          Tuple tupleCopy = aux->row;
          while( tupleCopy->next != NULL ) {
            tupleCopy = tupleCopy->next;
          }
          if( tupleCopy->next == NULL ) {
            tupleCopy->next = newTuple;
          }
          aux = aux->next;
        }
      }
    } else {
      column->restriction = colRestriction;
    }
    column->next = NULL;
    if( table->attributes == NULL ) {
      table->attributes = column;
    } else {
      Tuple tableAttributesCopy = table->attributes;
      while( tableAttributesCopy->next != NULL ) {
        if( tableAttributesCopy->restriction == PRIMARY_KEY &&
            column->restriction == tableAttributesCopy->restriction ) {
          cout << "ERROR: Ya existe una PRIMARY_KEY." << endl;
          return ERROR;
        }
        if( tableAttributesCopy->name == columnName ) {
          cout << "ERROR: El nombre de columna ya existe." << endl;
          return ERROR;
        } else {
          tableAttributesCopy = tableAttributesCopy->next;
        }
      }
      // Si nombre de la columna ya existe.
      if( tableAttributesCopy->next == NULL &&
          tableAttributesCopy->name == columnName ) {
        cout << "ERROR: El nombre de columna ya existe." << endl;
        return ERROR;
      }
      if( tableAttributesCopy->next == NULL &&
          tableAttributesCopy->restriction == PRIMARY_KEY &&
          column->restriction == tableAttributesCopy->restriction ) {
        cout << "ERROR: Ya existe una PRIMARY_KEY." << endl;
        return ERROR;
      }
      if( tableAttributesCopy->next == NULL ) {
        tableAttributesCopy->next = column;
      }
    }
  }
  return OK;
}

typeRet PKCondition( typeOfData type, int index, Tuples tuple ) {
  tree treeUnion;
  if( type == STRING ) treeUnion.treeStr = NULL;
  else
    treeUnion.treeInt = NULL;
  while( tuple != NULL ) {
    typeRet result = OK;
    Tuple row      = tuple->row;
    for( int i = 1; i < index; i++ ) row = row->next;
    if( type == STRING )
      result = InsertText( treeUnion.treeStr, row->text, "" );
    else
      result = Insert( treeUnion.treeInt, row->number, "" );
    if( result == ERROR ) {
      cout << "Hay datos duplicados en " << row->name
           << " no se puede cambiar a PRIMARY KEY" << endl;
      return ERROR;
    }
    tuple = tuple->next;
  }
  return OK;
}

// alterCol (Personas,Name,string,NOT EMPTY, Nombre)
typeRet alterCol( string tableName, string columnName, string typeOfDataP,
                  string typeOfRestrictionP, string newColumnName ) {
  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "Tabla no encontrada" << endl;
    return ERROR;
  }
  int index = WhereConditionColumn( table, columnName );
  if( index == -1 ) {
    cout << "La columna no existe" << endl;
    return ERROR;
  }
  const regex regExpString( "^[sS][tT][rR][iI][nN][gG]$" );
  const regex regExpInteger( "^[iI][nN][tT][eE][gG][eE][rR]$" );
  const regex regExpInt( "^[iI][nN][tT]$" );
  const regex regExpAny( "^[Aa][Nn][Yy]$" );
  const regex regExpNEmpty( "^[Nn][Oo][Tt][-_ ][Ee][Mm][Pp][Tt][Yy]$" );
  Tuple row   = table->tuple->row;
  bool change = false;
  typeOfData newType;
  for( int i = 1; i < index; i++ ) row = row->next;
  if( regex_match( typeOfDataP, regExpInteger ) ||
      regex_match( typeOfDataP, regExpInt ) ) {
    newType = INT;
    if( row->type == STRING ) {
      cout << "No esta permitido cambiar de STRING a INT" << endl;
      return ERROR;
    }
  } else if( ! regex_match( typeOfDataP, regExpString ) ) {
    cout << "Tipo de dato incorrecto, debe ser INT o STRING" << endl;
    return ERROR;
  }
  if( regex_match( typeOfDataP, regExpString ) ) {
    newType = STRING;
    if( row->type == INT ) change = true;
  }
  // Check if columnName is Primary key and there is more than one column
  row                     = table->tuple->row;
  bool minimumTwoElements = ( row->next != NULL );
  for( int i = 1; i < index; i++ ) row = row->next;
  typeOfData type = row->type;  // for condition on primary key later
  if( ( row->restriction == PRIMARY_KEY ) && minimumTwoElements ) {
    cout << row->name << " es la PRIMARY KEY y la tabla tiene más columnas.";
    return ERROR;
  }
  // Check if newColumnName exist previously (I allow it if it is the same
  // column)
  row           = table->tuple->row;
  int indexCopy = index;
  while( row != NULL ) {
    indexCopy--;
    if( row->name == newColumnName && index != 0 ) {
      cout << newColumnName << " ya existe en la tabla" << endl;
      return ERROR;
    }
    row = row->next;
  }
  // Check if typeOfRestriction parameter is primary key that there are no
  // duplicates
  typeOfRestriction newRestriction;
  const regex regExpPrimary(
      "^[Pp][Rr][Ii][Mm][Aa][Rr][Yy][ _-][Kk][Ee][Yy]$" );
  if( regex_match( typeOfRestrictionP, regExpPrimary ) ) {
    newRestriction = PRIMARY_KEY;
    if( PKCondition( type, index, table->tuple ) == ERROR ) return ERROR;
  }
  // Store the other types of restrictions
  if( regex_match( typeOfRestrictionP, regExpAny ) ) newRestriction = ANY;
  if( regex_match( typeOfRestrictionP, regExpNEmpty ) )
    newRestriction = NOT_EMPTY;
  // If it don't throw an error still means I can set without errors.
  Tuples tuplesCopy = table->tuple;
  while( tuplesCopy != NULL ) {
    Tuple rowCopy = tuplesCopy->row;
    for( int i = 1; i < index; i++ ) rowCopy = rowCopy->next;
    if( rowCopy->type == INT && newType == STRING ) {
      rowCopy->text = to_string( rowCopy->number );
      rowCopy->type = newType;
    }
    rowCopy->restriction = newRestriction;
    rowCopy->name        = newColumnName;
    tuplesCopy           = tuplesCopy->next;
  }
  // TODO: Delete if we delete attributes list
  Tuple attributesCopy = table->attributes;
  for( int i = 1; i < index; i++ ) attributesCopy = attributesCopy->next;
  attributesCopy->type        = newType;
  attributesCopy->restriction = newRestriction;
  attributesCopy->name        = newColumnName;
  return OK;
}

typeRet dropCol( string tableName, string columnName ) {
  if( tableName.length( ) == 0 ) {
    cout << "El nombre de la tabla debe ser especificado." << endl;
    return ERROR;
  }

  if( columnName.length( ) == 0 ) {
    cout << "El nombre de la columna debe ser especificado." << endl;
    return ERROR;
  }

  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "La tabla '" << tableName << "' no existe." << endl;
    return ERROR;
  }

  Tuple tableAttributesCopy = table->attributes;
  int columnsCounter        = 0;
  Tuple findedColumn        = NULL;
  while( tableAttributesCopy != NULL ) {
    if( tableAttributesCopy->name == columnName ) {
      findedColumn = tableAttributesCopy;
    }
    tableAttributesCopy = tableAttributesCopy->next;
    columnsCounter++;
  }

  if( findedColumn == NULL ) {
    cout << "La columna '" << columnName << "' no pertenece a la tabla '"
         << tableName << "'." << endl;
    return ERROR;
  }

  if( findedColumn->restriction == PRIMARY_KEY && columnsCounter > 1 ) {
    cout << "La columna '" << columnName << "' es clave primaria de la tabla '"
         << tableName
         << "'. No puede ser eliminada al menos que sea el único atributo."
         << endl;
    return ERROR;
  }

  int findedColumnIndex = 0;
  bool finded           = false;
  tableAttributesCopy   = table->attributes;
  while( tableAttributesCopy != NULL && ! finded ) {
    if( tableAttributesCopy->name == columnName ) {
      finded = true;
    } else {
      findedColumnIndex++;
      tableAttributesCopy = tableAttributesCopy->next;
    }
  }

  if( findedColumnIndex == 0 ) {
    Tuple attributeCopy = table->attributes;
    table->attributes   = table->attributes->next;
    delete attributeCopy;
  } else {
    tableAttributesCopy = table->attributes;
    for( int i = 0; i < findedColumnIndex - 1; i++ ) {
      tableAttributesCopy = tableAttributesCopy->next;
    }
    Tuple attributeCopy       = tableAttributesCopy->next;
    tableAttributesCopy->next = tableAttributesCopy->next->next;
    delete attributeCopy;
  }

  Tuples tableTuplesCopy = table->tuple;
  bool firstChanged      = false;
  while( tableTuplesCopy != NULL ) {
    if( findedColumnIndex == 0 ) {
      if( ! firstChanged ) {
        Tuple tupleCopy   = table->tuple->row;
        table->tuple->row = table->tuple->row->next;
        delete tupleCopy;
        firstChanged = true;
      } else {
        Tuple tupleCopy      = tableTuplesCopy->row;
        tableTuplesCopy->row = tableTuplesCopy->row->next;
        delete tupleCopy;
      }
    } else {
      Tuple tupleRowCopy = tableTuplesCopy->row;
      for( int i = 0; i < findedColumnIndex - 1; i++ )
        tupleRowCopy = tupleRowCopy->next;

      Tuple rowCopy      = tupleRowCopy->next;
      tupleRowCopy->next = tupleRowCopy->next->next;
      delete rowCopy;
    }
    tableTuplesCopy = tableTuplesCopy->next;
  }
  return OK;
}

void showColumns( Tables tablesList ) {
  Tables aux = tablesList;
  while( aux->attributes != NULL ) {
    cout << aux->attributes->name << endl;
    aux->attributes = aux->attributes->next;
  }
}

#endif  // !columns
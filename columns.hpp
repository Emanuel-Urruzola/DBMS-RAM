#ifndef columns
#define columns
#include "tables.hpp"
#include "variables.hpp"
// TODO: Validar el caso de que ya exista una PRIMARY_KEY, el caso de que
// exista almenos una tupla. Tambien validar que en el caso de que existan
// tuplas no pueden tener restriction != de ANY
typeRet AddCol( string tableName, string columnName, string columnType,
                typeOfRestriction restriction ) {
  typeOfData colType;
  if( columnType == "STRING" ) {
    colType = STRING;
  } else if( columnType == "INT" ) {
    colType = INT;
  } else {
    cout << "Tipo de dato invalido." << endl;
    return ERROR;
  }
  if( columnType != "STRING" && columnType != "INT" ) {
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
    Tuple column        = new nodeElement;
    column->name        = columnName;
    column->type        = colType;
    column->restriction = restriction;
    column->next        = NULL;
    if( table->attributes == NULL ) {
      table->attributes = column;
      column->index     = 0;
    } else {
      // Si nombre de la columna ya existe.
      if( table->attributes->next == NULL &&
          table->attributes->name == columnName ) {
        cout << "ERROR: El nombre de columna ya existe." << endl;
        return ERROR;
      }
      Tuple tableAttributesCopy = table->attributes;
      bool finded               = false;
      while( tableAttributesCopy->next != NULL && ! finded ) {
        if( tableAttributesCopy->name == columnName ) {
          cout << "ERROR: El nombre de columna ya existe." << endl;
          return ERROR;
          finded = true;
        } else {
          tableAttributesCopy = tableAttributesCopy->next;
        }
      }
      if( tableAttributesCopy->next == NULL && ! finded ) {
        tableAttributesCopy->next        = column;
        tableAttributesCopy->next->index = tableAttributesCopy->index + 1;
      }
    }
  }
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
  // TODO: Set columns index after deleteing one
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

/** PARTE VIEJA DEL INSFRONT**/
//     if( table->attributes == NULL ) {
//       column->next  = NULL;
//       column->index = 0;
//     } else {
//       column->next  = table->attributes;
//       column->index = column->next->index + 1;  // descendent order
//     }
//     table->attributes = column;
//     cout << "";
//   }
// }
#endif  // !columns
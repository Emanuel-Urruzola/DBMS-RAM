#ifndef columns
#define columns
#include "tables.hpp"
#include "variables.hpp"

void AddCol( string tableName, string columnName, typeOfData columnType,
             typeOfRestriction restriction ) {
  Tables table = findTable( tableName );
  if( table == NULL ) cout << "What table?";
  else {
    Tuple column        = new nodeElement;
    column->name        = columnName;
    column->type        = columnType;
    column->restriction = restriction;
    column->next        = NULL;
    if( table->attributes == NULL ) {
      table->attributes = column;
      column->index     = 0;
    } else {
      Tuple tableAttributesCopy = table->attributes;
      bool finded               = false;
      while( tableAttributesCopy->next != NULL && ! finded ) {
        if( tableAttributesCopy->name == columnName ) {
          cout << "No se puede ingresar dos veces la misma columna"
               << endl;  // retornar tipoRet
          finded = true;
        } else {
          tableAttributesCopy = tableAttributesCopy->next;
        }
      }
      if( ! finded ) {
        tableAttributesCopy->next        = column;
        tableAttributesCopy->next->index = tableAttributesCopy->index + 1;
      }
    }
  }
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
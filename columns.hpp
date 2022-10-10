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
    if( table->attributes == NULL ) {
      column->next  = NULL;
      column->index = 0;
    } else {
      column->next  = table->attributes;
      column->index = column->next->index + 1;  // descendent order
    }
    table->attributes = column;
    cout << "";
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

  tableAttributesCopy = table->attributes;
  for( int i = 0; i < findedColumnIndex - 1; i++ ) {
    tableAttributesCopy = tableAttributesCopy->next;
  }
  Tuple attributeCopy       = tableAttributesCopy->next;
  tableAttributesCopy->next = tableAttributesCopy->next->next;
  delete attributeCopy;

  Tuples tableTuplesCopy = table->tuple;
  while( tableTuplesCopy != NULL ) {
    Tuple tupleRowCopy = tableTuplesCopy->row;
    for( int i = 0; i < findedColumnIndex - 1; i++ ) {
      tupleRowCopy = tupleRowCopy->next;
    }
    Tuple rowCopy      = tupleRowCopy->next;
    tupleRowCopy->next = tupleRowCopy->next->next;
    delete rowCopy;
    tableTuplesCopy = tableTuplesCopy->next;
  }

  return OK;
}

#endif  // !columns
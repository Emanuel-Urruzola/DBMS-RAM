#include <iostream>
#include <regex>
#include "columns.h"
#include "tables.h"
#include "variables.h"
#include "tuples.h"
#include "operations.h"

// TODO: Validar el caso de que
// exista almenos una tupla. Tambien validar que en el caso de que existan
// tuplas no pueden tener restriction != de ANY
typeRet addCol( string tableName, string columnName, string columnType,
                string restriction ) {
  typeOfData colType;
  typeOfRestriction colRestriction;

  if( columnType == "string" ) {
    colType = typeOfData::STRING;
  } else if( columnType == "integer" ) {
    colType = typeOfData::INT;
  } else {
    cout << "ERROR: El tipo de dato '" << columnType << "' no es valido."
         << endl;
    return typeRet::ERROR;
  }
  if( restriction == "PRIMARY_KEY" ) {
    colRestriction = typeOfRestriction::PRIMARY_KEY;
  } else if( restriction == "ANY" ) {
    colRestriction = typeOfRestriction::ANY;
  } else if( restriction == "NOT_EMPTY" ) {
    colRestriction = typeOfRestriction::NOT_EMPTY;
  } else {
    cout << "ERROR: El tipo de restriccion '" << restriction
         << "' no es valido." << endl;
    return typeRet::ERROR;
  }

  if( columnType != "string" && columnType != "integer" ) {
    cout << "ERROR: Ingrese tipo de dato válido." << endl;
    return typeRet::ERROR;
  }
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  if( columnName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la columna debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }

  Tuple column = new nodeElement;
  column->name = columnName;
  column->type = colType;
  if( table->tuple != NULL ) {
    if( colRestriction != typeOfRestriction::ANY ) {
      cout << "ERROR: El calificador de la columna debe ser ANY." << endl;
      return typeRet::ERROR;
    }
    column->restriction   = colRestriction;
    Tuple newTuple        = new nodeElement;
    newTuple->next        = NULL;
    newTuple->name        = columnName;
    newTuple->type        = colType;
    newTuple->restriction = colRestriction;
    if( colType == typeOfData::INT ) newTuple->number = -1;
    else
      newTuple->text = "";

    Tuples aux = table->tuple;
    while( aux != NULL ) {
      Tuple tupleCopy = aux->row;
      while( tupleCopy->next != NULL ) tupleCopy = tupleCopy->next;
      if( tupleCopy->next == NULL ) tupleCopy->next = newTuple;
      aux = aux->next;
    }

  } else
    column->restriction = colRestriction;

  column->next = NULL;
  if( table->attributes == NULL ) table->attributes = column;
  else {
    Tuple tableAttributesCopy = table->attributes;
    while( tableAttributesCopy->next != NULL ) {
      if( tableAttributesCopy->restriction == typeOfRestriction::PRIMARY_KEY &&
          column->restriction == tableAttributesCopy->restriction ) {
        cout << "ERROR: Ya existe una PRIMARY_KEY." << endl;
        return typeRet::ERROR;
      }

      if( tableAttributesCopy->name == columnName ) {
        cout << "ERROR: La columna '" << columnName
             << "' ya existe en la tabla '" << tableName << "'." << endl;
        return typeRet::ERROR;
      } else
        tableAttributesCopy = tableAttributesCopy->next;
    }

    // Si nombre de la columna ya existe.
    if( tableAttributesCopy->next == NULL &&
        tableAttributesCopy->name == columnName ) {
      cout << "ERROR: El nombre de columna ya existe." << endl;
      return typeRet::ERROR;
    }
    if( tableAttributesCopy->next == NULL &&
        tableAttributesCopy->restriction == typeOfRestriction::PRIMARY_KEY &&
        column->restriction == tableAttributesCopy->restriction ) {
      cout << "ERROR: Ya existe una PRIMARY_KEY." << endl;
      return typeRet::ERROR;
    }

    if( tableAttributesCopy->next == NULL ) tableAttributesCopy->next = column;
  }
  return typeRet::ERROR;
}

typeRet pkCondition( typeOfData type, int index, Tuples tuple ) {
  tree treeUnion{ };
  if( type == typeOfData::STRING ) treeUnion.treeStr = NULL;
  else
    treeUnion.treeInt = NULL;
  while( tuple != NULL ) {
    typeRet result = typeRet::ERROR;
    Tuple row      = tuple->row;
    for( int i = 1; i < index; i++ ) row = row->next;
    if( type == typeOfData::STRING )
      result = insertText( treeUnion.treeStr, row->text, "" );
    else
      result = insert( treeUnion.treeInt, row->number, "" );
    if( result == typeRet::ERROR ) return typeRet::ERROR;
    tuple = tuple->next;
  }
  return typeRet::ERROR;
}

// alterCol (Personas,Name,string,NOT EMPTY, Nombre)
typeRet alterCol( string tableName, string columnName, string typeOfDataP,
                  string typeOfRestrictionP, string newColumnName ) {
  Tables table = findTable( tableName );
  const regex regExpString( "^[sS][tT][rR][iI][nN][gG]$" );
  const regex regExpInteger( "^[iI][nN][tT][eE][gG][eE][rR]$" );
  const regex regExpInt( "^[iI][nN][tT]$" );
  const regex regExpAny( "^[Aa][Nn][Yy]$" );
  const regex regExpNEmpty( "^[Nn][Oo][Tt][-_ ][Ee][Mm][Pp][Tt][Yy]$" );
  const regex regExpPrimary(
      "^[Pp][Rr][Ii][Mm][Aa][Rr][Yy][ _-][Kk][Ee][Yy]$" );

  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }

  if( typeOfRestrictionP.length( ) == 0 ) {
    cout << "ERROR: El la restriccion de la columna debe ser especificada."
         << endl;
    return typeRet::ERROR;
  }
  if( typeOfDataP.length( ) == 0 ) {
    cout << "ERROR: El tipo de la columna debe ser especificada." << endl;
    return typeRet::ERROR;
  }

  if( ! regex_match( typeOfRestrictionP, regExpAny ) &&
      ! regex_match( typeOfRestrictionP, regExpPrimary ) &&
      ! regex_match( typeOfRestrictionP, regExpNEmpty ) ) {
    cout << "ERROR: El la restriccion de la columna debe PRIMARY_KEY, "
            "NOT_EMPTY o ANY."
         << endl;
    return typeRet::ERROR;
  }

  if( newColumnName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la columna debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  int index = whereConditionColumn( table, columnName );
  if( index == -1 ) {
    cout << "ERROR: La columna no existe" << endl;
    return typeRet::ERROR;
  }

  Tuple attributes = table->attributes;
  // TODO Emanuel: ver si change se usa. en linea 190 tambien borrar
  typeOfData newType{ };
  for( int i = 1; i < index; i++ ) attributes = attributes->next;
  if( regex_match( typeOfDataP, regExpInteger ) ||
      regex_match( typeOfDataP, regExpInt ) ) {
    newType = typeOfData::INT;
    if( attributes->type == typeOfData::STRING ) {
      cout << "ERROR: No esta permitido cambiar de STRING a INT" << endl;
      return typeRet::ERROR;
    }
  } else if( ! regex_match( typeOfDataP, regExpString ) ) {
    cout << "ERROR: Tipo de dato incorrecto, debe ser INT o STRING" << endl;
    return typeRet::ERROR;
  }
  if( regex_match( typeOfDataP, regExpString ) ) {
    newType = typeOfData::STRING;
  }
  // Check if columnName is Primary key and there is more than one column
  Tuple row               = table->tuple->row;
  bool minimumTwoElements = ( row->next != NULL );
  for( int i = 1; i < index; i++ ) row = row->next;
  typeOfData type = row->type;  // for condition on primary key later
  if( ( row->restriction == typeOfRestriction::PRIMARY_KEY ) &&
      minimumTwoElements ) {
    cout << "ERROR: La columna'" << row->name
         << "' es la PRIMARY KEY y la tabla tiene más columnas.";
    return typeRet::ERROR;
  }
  // Check if newColumnName exist previously (I allow it if it is the same
  // column)
  row           = table->tuple->row;
  int indexCopy = index;
  while( row != NULL ) {
    indexCopy--;
    if( row->name == newColumnName && index != 0 ) {
      cout << "ERROR: La columna '" << newColumnName
           << "' ya existe en la tabla '" << tableName << "'." << endl;
      return typeRet::ERROR;
    }
    row = row->next;
  }
  // Check if typeOfRestriction parameter is primary key that there are no
  // duplicates
  typeOfRestriction newRestriction{ };
  if( regex_match( typeOfRestrictionP, regExpPrimary ) ) {
    newRestriction = typeOfRestriction::PRIMARY_KEY;
    if( pkCondition( type, index, table->tuple ) == typeRet::ERROR ) {
      cout << "ERROR: Hay datos duplicados en '" << newColumnName
           << "' no se puede cambiar a PRIMARY KEY" << endl;
      return typeRet::ERROR;
    }
  }
  // Store the other types of restrictions
  if( regex_match( typeOfRestrictionP, regExpAny ) )
    newRestriction = typeOfRestriction::ANY;
  if( regex_match( typeOfRestrictionP, regExpNEmpty ) )
    newRestriction = typeOfRestriction::NOT_EMPTY;
  // If it don't throw an error still means I can set without errors.
  Tuples tuplesCopy = table->tuple;
  while( tuplesCopy != NULL ) {
    Tuple rowCopy = tuplesCopy->row;
    for( int i = 1; i < index; i++ ) rowCopy = rowCopy->next;
    if( rowCopy->type == typeOfData::INT && newType == typeOfData::STRING ) {
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
  return typeRet::ERROR;
}

typeRet dropCol( string tableName, string columnName ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  if( columnName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la columna debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
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
    cout << "ERROR: La columna '" << columnName << "' no pertenece a la tabla '"
         << tableName << "'." << endl;
    return typeRet::ERROR;
  }

  if( findedColumn->restriction == typeOfRestriction::PRIMARY_KEY &&
      columnsCounter > 1 ) {
    cout << "ERROR: La columna '" << columnName
         << "' es clave primaria de la tabla '" << tableName
         << "'. No puede ser eliminada al menos que sea el único atributo."
         << endl;
    return typeRet::ERROR;
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
    Tuple attributeCopy = tableAttributesCopy->next;
    if( tableAttributesCopy->next != NULL &&
        tableAttributesCopy->next->next != NULL ) //fix warning
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
  return typeRet::ERROR;
}
void showColumns( Tables tablesList ) {
  Tables aux = tablesList;
  while( aux->attributes != NULL ) {
    cout << aux->attributes->name << endl;
    aux->attributes = aux->attributes->next;
  }
}

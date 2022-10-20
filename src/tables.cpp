#include <iostream>
#include <string>
#include "../include/tables.h"
#include "../include/variables.h"
#include "../include/deleteHelpers.h"

using namespace std;

typeRet createTable( string tableName ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return ERROR;
  }
  if( tablesList != NULL ) {
    Tables aux = tablesList;
    while( aux != NULL ) {
      if( aux->name == tableName ) {
        cout << "ERROR: Ya existe la tabla '" << tableName << "'." << endl;
        return ERROR;
      } else {
        if( aux->next != NULL ) aux = aux->next;
        else {
          cout << "";
          Tables newTable      = new nodeTable;
          newTable->name       = tableName;
          newTable->attributes = NULL;
          newTable->tuple      = NULL;
          newTable->next       = tablesList;
          tablesList           = newTable;
          aux                  = aux->next;
        }
      }
    }
  } else {
    Tables newTable      = new nodeTable;
    newTable->name       = tableName;
    newTable->attributes = NULL;
    newTable->tuple      = NULL;
    newTable->next       = tablesList;
    tablesList           = newTable;
  }
  return OK;
}

void showTables( Tables tablesList ) {
  Tables aux = tablesList;
  while( aux != NULL ) {
    cout << aux->name << endl;
    aux = aux->next;
  }
}

Tables findTable( string tableName ) {
  Tables aux = tablesList;
  while( aux != NULL ) {
    if( aux->name == tableName ) return aux;
    aux = aux->next;
  }
  return NULL;
}

typeRet dropTable( string tableName ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return ERROR;
  }

  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return ERROR;
  }
  // Delete table tuples
  deleteAllTuples( table->tuple );

  // Delete table attributes
  deleteAllRows( table->attributes );

  // Delete table
  if( tablesList == table ) {
    Tables tableCopy = tablesList;
    tablesList       = tablesList->next;
    delete tableCopy;
  } else {
    Tables tablesListCopy = tablesList;
    while( tablesListCopy->next != table )
      tablesListCopy = tablesListCopy->next;
    Tables tableCopy     = tablesListCopy->next;
    tablesListCopy->next = tablesListCopy->next->next;
    delete tableCopy;
  }
  return OK;
}

typeRet modifyTable( string tableName, string newName ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return ERROR;
  }

  if( newName.length( ) == 0 ) {
    cout << "ERROR: El nuevo nombre de la tabla debe ser especificado." << endl;
    return ERROR;
  }

  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return ERROR;
  }

  table->name = newName;
  return OK;
}
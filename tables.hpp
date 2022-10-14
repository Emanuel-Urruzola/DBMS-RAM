#ifndef tables
#define tables

#include <iostream>
#include <string>

#include "variables.hpp"
#include "deleteHelpers.hpp"

using namespace std;

typeRet createTable( string tableName ) {
  if(tableName.length() == 0){
    cout << "ERROR: Nombre vacio!." << endl;
    return ERROR;
  }
  if( tablesList != NULL ) {
    Tables aux  = tablesList;
    bool finded = false;
    while( aux != NULL && ! finded ) {
      if( aux->name == tableName ) {
        cout << "ERROR: El nombre de tabla ya existe!." << endl;
        return ERROR;
        finded = true;
      } else {
        if( aux->next != NULL ) {
          aux = aux->next;
        } else {
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
    cout << "La tabla debe ser especificada." << endl;
    return ERROR;
  }

  Tables table = findTable( tableName );
  if( table == NULL ) {
    cout << "La tabla " << tableName << " no existe." << endl;
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
#endif  // !1
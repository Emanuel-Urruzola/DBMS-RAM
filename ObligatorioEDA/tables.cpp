#include <iostream>
#include <string>
#include "tables.h"
#include "variables.h"
#include "deleteHelpers.h"

using namespace std;

Tables newNodeTable( string tableName ) {
  Tables newTable      = new nodeTable;
  newTable->name       = tableName;
  newTable->attributes = NULL;
  newTable->tuple      = NULL;
  newTable->left       = NULL;
  newTable->right      = NULL;
  return newTable;
}

// Auxiliar para ver si la tabla ya existe (osea si se repite el nombre).
bool isIncluded( Tables tablesList, string tableName ) {
  if( tablesList == NULL ) 
      return false;
  if( tableName.compare( tablesList->name ) == 0 ) {
    cout << "La tabla ya existe." << endl;
    return true;
  }
  else if( tableName.compare( tablesList->name ) > 0 ) 
      return isIncluded(tablesList->right, tableName );
  else return isIncluded( tablesList->left, tableName );
}

void insertTable( Tables tablesList, string tableName ) {
  if( tableName.compare( tablesList->name ) > 0 ) {
    if( tablesList->right == NULL )
      tablesList->right = newNodeTable( tableName );
    else
      insertTable( tablesList->right, tableName );
  } else {
    if( tablesList->left == NULL ) 
      tablesList->left = newNodeTable( tableName );
    else
      insertTable( tablesList->left, tableName );
  }
}

typeRet createTable( string tableName ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }
  if( tablesList == NULL ) {
    Tables newTable = newNodeTable( tableName );
    tablesList      = newTable;
  } else {
    if( isIncluded( tablesList, tableName ) ) {
      cout << "ERROR: Ya existe la tabla " << tableName << endl;
      return typeRet::ERROR;
    } else {
      insertTable( tablesList, tableName );
    }
  }
  return typeRet::OK;
}

typeRet printTables( Tables tablesList ) {
  if( tablesList != NULL ){
    printTables( tablesList->left );
    cout << tablesList->name << endl;
    printTables( tablesList->right );
  }
  return typeRet::OK;
}

Tables findTable( Tables tablesList, string tableName ) {
  if( tablesList == NULL ) 
      return NULL;
  if( tableName.compare( tablesList->name ) == 0 ) 
    return tablesList;
  else if( tableName.compare( tablesList->name ) > 0 )
    return findTable( tablesList->right, tableName );
  else
    return findTable( tablesList->left, tableName );
}

typeRet dropTable( string tableName ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  Tables table = findTable(tablesList, tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }
  // Delete table tuples
  deleteAllTuples( table->tuple );

  // Delete table attributes
  deleteAllRows( table->attributes );

  // Delete table
  if( tablesList == table ) {
    Tables tableCopy = tablesList;
    tablesList       = tablesList->left;
    delete tableCopy;
  } else {
    Tables tablesListCopy = tablesList;
    while( tablesListCopy->left != table )
      tablesListCopy = tablesListCopy->left;
    Tables tableCopy     = tablesListCopy->left;
    tablesListCopy->left = tablesListCopy->left->left;
    delete tableCopy;
  }
  return typeRet::OK;
}

typeRet modifyTable( string tableName, string newName ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  if( newName.length( ) == 0 ) {
    cout << "ERROR: El nuevo nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  Tables table = findTable( tablesList, tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }

  table->name = newName;
  return typeRet::OK;
}

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

bool isIncluded( Tables tablesList, string tableName ) {
  if( tablesList == NULL ) return false;
  if( tableName.compare( tablesList->name ) == 0 ) {
    cout << "La tabla ya existe." << endl;
    return true;
  } else if( tableName.compare( tablesList->name ) > 0 )
    return isIncluded( tablesList->right, tableName );
  else
    return isIncluded( tablesList->left, tableName );
}

void insertTable( Tables tablesList, string tableName ) {
  if( tableName.compare( tablesList->name ) > 0 ) {
    if( tablesList->right == NULL )
      tablesList->right = newNodeTable( tableName );
    else
      insertTable( tablesList->right, tableName );
  } else {
    if( tablesList->left == NULL ) tablesList->left = newNodeTable( tableName );
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
  if( tablesList == NULL ) {
    cout << "ERROR: No hay tablas." << endl;
    return typeRet::ERROR;
  } else {
    if( tablesList->left != NULL )  // Si hay tablas a la izquierda llama a la
                                    // funcion para imprimir los hijos izq
      printTables( tablesList->left );
    cout << tablesList->name << endl;
    if( tablesList->right != NULL )  // Si hay tablas a la derecha llama a la
                                     // funcion para imprimir hijos der
      printTables( tablesList->right );
  }

  return typeRet::OK;
}

Tables findTable( Tables tablesList, string tableName ) {
  if( tablesList == NULL ) return NULL;
  if( tableName.compare( tablesList->name ) == 0 ) return tablesList;
  else if( tableName.compare( tablesList->name ) > 0 )
    return findTable( tablesList->right, tableName );
  else
    return findTable( tablesList->left, tableName );
}

Tables minTable( Tables tablesList ) {
  Tables current = tablesList;
  while( current && current->left != NULL ) current = current->left;
  return current;
}

Tables deleteTable( Tables &tablesList, string tableName ) {
  if( tablesList != NULL ) {
    if( tableName.compare( tablesList->name ) == 0 ) {
      // nodo hoja
      if( tablesList->left == NULL && tablesList->right == NULL ) {
        Tables aux = tablesList;
        tablesList = NULL;
        delete aux;
        // nodo con hijo a la izq
      } else if( tablesList->right == NULL ) {
        Tables aux = tablesList;
        tablesList = tablesList->left;
        delete aux;
        // nodo con hijo a la derecha
      } else if( tablesList->left == NULL ) {
        Tables aux = tablesList;
        tablesList = tablesList->right;
        delete aux;
        // tiene dos hijos.
      } else {
        // deleteMax( tablesList->left );
        Tables temp            = minTable( tablesList->right );
        tablesList->name       = temp->name;
        tablesList->attributes = temp->attributes;
        tablesList->tuple      = temp->tuple;
        tablesList->right      = deleteTable( tablesList->right, temp->name );
      }
    } else if( tableName.compare( tablesList->name ) < 0 )
      deleteTable( tablesList->left, tableName );
    else
      deleteTable( tablesList->right, tableName );
  }
  return tablesList;
}

typeRet dropTable( string tableName ) {
  if( tableName.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla debe ser especificado." << endl;
    return typeRet::ERROR;
  }

  Tables table = findTable( tablesList, tableName );
  if( table == NULL ) {
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
    return typeRet::ERROR;
  }
  // Delete table tuples
  deleteAllTuples( table->tuple );

  // Delete table attributes
  deleteAllRows( table->attributes );

  // Delete table
  deleteTable( tablesList, tableName );

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

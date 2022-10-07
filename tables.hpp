#ifndef tables
#define tables

#include <iostream>
#include <string>

#include "variables.hpp"

using namespace std;

void createTable( Tables &tablesList, string tableName ) {
  Tables newTable      = new nodeTable;
  newTable->name       = tableName;
  newTable->attributes = NULL;
  newTable->tuple      = NULL;
  newTable->next       = tablesList;
  tablesList           = newTable;
}

void showTables( Tables tablesList ) {
  Tables aux = tablesList;
  while( aux != NULL ) {
    cout << aux->name << endl;
    aux = aux->next;
  }
}

Tables findTable( Tables &tablesList, string tableName ) {
  Tables aux = tablesList;
  while( aux != NULL ) {
    if( aux->name == tableName ) return aux;
    aux = aux->next;
  }
  return NULL;
}
#endif  // !1

// Prueba branches
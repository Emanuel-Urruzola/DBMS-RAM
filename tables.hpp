#ifndef tables
#define tables

#include <iostream>
#include <string>

#include "variables.hpp"

using namespace std;
// Esta pasando que tira el error, pero sigue iterando y comparando, preciso que
// no lo haga, si no me va a crear la tabla de igual manera
void createTable( string tableName ) {
  if( tablesList != NULL ) {
    Tables aux  = tablesList;
    bool finded = false;
    cout<<"";
    while( aux != NULL && ! finded ) {
      if( aux->name == tableName ) {
        cout << "Error" << endl;
        finded = true;
      } else /**/ {
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
}

void showTables( Tables tablesList ) {
  Tables aux = tablesList;
  while( aux != NULL ) {
    cout << aux->name << endl;
    aux = aux->next;
  }
}

Tables findTable( Tables tablesList, string tableName ) {
  Tables aux = tablesList;
  while( aux != NULL ) {
    if( aux->name == tableName ) return aux;
    aux = aux->next;
  }
  return NULL;
}
#endif  // !1

// Prueba branches
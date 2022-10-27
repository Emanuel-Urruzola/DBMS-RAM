// Si nombreTabla1 no existe o no se especifica.
//  Si nombreTabla2 no existe o no se especifica.
//  Si nombreTabla3 existe.
//  Si los esquemas de nombreTabla1 es distinta a nombreTabla2.
#include <iostream>
#include <string>
#include "sets.h"
#include "variables.h"
#include "tables.h"
#include "columns.h"
#include "tuples.h"

typeRet unionDB( string tableName1, string tableName2,
                 string tableNameResult ) {
  if( tableName1.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla 1 debe ser especificado" << endl;
    return typeRet::ERROR;
  }
  if( tableName2.length( ) == 0 ) {
    cout << "ERROR: El nombre de la tabla 2 debe ser especificado" << endl;
    return typeRet::ERROR;
  }
  if( tableNameResult.length( ) == 0 ) {
    cout << "ERROR: El nombre de la nueva tabla debe ser especificado" << endl;
    return typeRet::ERROR;
  }
  Tables table1 = findTable( tableName1 );
  if( table1 == NULL ) {
    cout << "ERROR: La tabla '" << tableName1 << "' no existe." << endl;
    return typeRet::ERROR;
  }
  Tables table2 = findTable( tableName2 );
  if( table2 == NULL ) {
    cout << "ERROR: La tabla '" << tableName2 << "' no existe." << endl;
    return typeRet::ERROR;
  }
  Tables tableResult = findTable( tableNameResult );
  if( tableResult != NULL ) {
    cout << "ERROR: La tabla '" << tableName2 << "' ya existe." << endl;
    return typeRet::ERROR;
  }
  if( checkSchema( table1, table2, tableNameResult ) == typeRet::ERROR ) {
    return typeRet::ERROR;
  }
  return typeRet::OK;
}
typeRet checkSchema( Tables table1, Tables table2, string tableNameResult ) {
  // TODO Emanuel: Check if tables have no attributes previously  ?
  Tuple attributesTable1 = table1->attributes;
  Tuple attributesTable2 = table2->attributes;
  // To check that the new table does not repeat the primary key
  while( attributesTable1 != NULL && attributesTable2 != NULL ) {
    // I assign condition on boolean variables: more legible, less efficient
    bool names = attributesTable1->name == attributesTable2->name;
    bool types = attributesTable1->type == attributesTable2->type;
    bool restrictions =
        attributesTable1->restriction == attributesTable2->restriction;
    if( ! names || ! types || ! restrictions ) {
      cout << "ERROR: Los esquemas de las tablas no son iguales" << endl;
      return typeRet::ERROR;
    }
    attributesTable1 = attributesTable1->next;
    attributesTable2 = attributesTable2->next;
  }
  if( attributesTable1 != NULL || attributesTable2 != NULL ) {
    cout << "ERROR: Las tablas tienen que tener la misma cantidad de atributos"
         << endl;
    return typeRet::ERROR;
  }
  if( createTableUnion( table1, table2, tableNameResult ) == typeRet::ERROR ) {
    return typeRet::ERROR;
  }
  return typeRet::OK;
}
typeRet createTableUnion( Tables table1, Tables table2,
                          string tableNameResult ) {
  createTable( tableNameResult );
  Tuple attributesTable1 = table1->attributes;
  while( attributesTable1 != NULL ) {
    string type, restriction;  // addCol requires string not enums
    if( attributesTable1->type == typeOfData::STRING ) type = "string";
    else
      type = "integer";
    if( attributesTable1->restriction == typeOfRestriction::ANY )
      restriction = "ANY";
    else if( attributesTable1->restriction == typeOfRestriction::NOT_EMPTY )
      restriction = "NOT_EMPTY";
    else
      restriction = "PRIMARY_KEY";
    addCol( tableNameResult, attributesTable1->name, type, restriction );
    attributesTable1 = attributesTable1->next;
  }
  if( insertIntoTableUnion( table1, tableNameResult ) == typeRet::ERROR )
    return typeRet::ERROR;

  if( insertIntoTableUnion( table2, tableNameResult ) == typeRet::ERROR )
    return typeRet::ERROR;
}
typeRet insertIntoTableUnion( Tables table, string tableNameResult ) {
  Tuples tuples = table->tuple;
  while( tuples != NULL ) {
    Tuple row    = tuples->row;
    string names  = "";
    string values = "";
    while( row != NULL ) {
      names += row->name + ":";
      if( row->type == typeOfData::STRING ) values += row->text + ":";
      else
        values += to_string( row->number ) + ":";
      row = row->next;
    }
    names  = names.substr( 0, names.length( ) - 1 );
    values = values.substr( 0, values.length( ) - 1 );
    if( insertInto( tableNameResult, names, values ) == typeRet::ERROR ) {
      cout << "Hubo un error al ingresar las tuplas en la nueva tabla, revise las primary key" << endl;
      return typeRet::ERROR;
    }
    tuples = tuples->next;
  }
  return typeRet::OK;
}
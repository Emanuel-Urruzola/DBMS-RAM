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
#include "operations.h"

TreeStr sets = NULL;
typeRet unionDB( string tableName1, string tableName2, string tableNameResult,
                 string type ) {
  // type method to enum
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
  if( type == "union" ) {
    if( insertIntoSet( table1, tableNameResult, "union", sets ) ==
        typeRet::ERROR )
      return typeRet::ERROR;
    if( insertIntoSet( table2, tableNameResult, "union", sets ) ==
        typeRet::ERROR )
      return typeRet::ERROR;
    releaseTree( sets );
  } else if( type == "intersect" ) {
    if( insertIntoTableIntersection( table1, tableNameResult, sets, type ) ==
        typeRet::ERROR )
      return typeRet::ERROR;
    if( insertIntoTableIntersection( table2, tableNameResult, sets, type ) ==
        typeRet::ERROR )
      return typeRet::ERROR;
    releaseTree( sets );
  } else if( type == "minus" ) {
    if( insertIntoTableIntersection( table1, tableNameResult, sets, type ) ==
        typeRet::ERROR )
      return typeRet::ERROR;
    if( insertIntoSet( table2, tableNameResult, "minus", sets ) ==
        typeRet::ERROR )
      return typeRet::ERROR;
    insertSetTreeInTable( sets, tableNameResult );
    releaseTree( sets );
  } else {
    cout << "Error: tipo incorrecto";
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
    if( addCol( tableNameResult, attributesTable1->name, type, restriction ) ==
        typeRet::ERROR ) {
      return typeRet::ERROR;
    }
    attributesTable1 = attributesTable1->next;
  }
  return typeRet::OK;
}
typeRet insertIntoSet( Tables table, string tableNameResult, string type,
                       TreeStr tree ) {
  Tuples tuples = table->tuple;
  while( tuples != NULL ) {
    Tuple row     = tuples->row;
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
    if( type == "union" &&
        insertInto( tableNameResult, names, values ) == typeRet::ERROR ) {
      cout << "Hubo un error al ingresar las tuplas en la nueva tabla, revise "
              "las primary key"
           << endl;
      return typeRet::ERROR;
    } else if( type == "minus" ) {
      deleteNodeTree( tree, values );
    }
    tuples = tuples->next;
  }
  return typeRet::OK;
}
typeRet insertIntoTableIntersection( Tables table, string tableNameResult,
                                     TreeStr& sets, string type ) {
  // TODO Emanuel: If there are repeated elements within the same table?
  Tuples tuples = table->tuple;
  while( tuples != NULL ) {
    Tuple row     = tuples->row;
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
    insertAndCreate( sets, values, names, tableNameResult, type );
    tuples = tuples->next;
  }
  return typeRet::OK;
}

typeRet insertAndCreate( TreeStr& tree, string values, string names,
                         string tableNameResult, string type ) {
  if( tree == NULL ) {
    TreeStr newTree = newNodeStr( values, names );
    tree            = newTree;
    return typeRet::OK;
  } else {
    if( values.compare( tree->value ) < 0 ) {
      insertAndCreate( tree->left, values, names, tableNameResult, type );
      return typeRet::OK;
    } else if( values.compare( tree->value ) == 0 ) {
      if( type != "minus" ) {
        if( insertInto( tableNameResult, names, values ) == typeRet::ERROR ) {
          cout << "Hubo un error al ingresar las tuplas en la nueva tabla, "
                  "revise "
                  "las primary key"
               << endl;
          return typeRet::ERROR;
        }
        return typeRet::OK;
      } else
        deleteNodeTree( tree, values );
      insertAndCreate( tree->right, values, names, tableNameResult, type );
      return typeRet::OK;
    } else {
      insertAndCreate( tree->right, values, names, tableNameResult, type );
      return typeRet::OK;
    }
  }
}
TreeStr deleteNodeTree( TreeStr& tree, string value ) {
  if( tree == NULL ) return NULL;
  else if( value < tree->value )
    return deleteNodeTree( tree->left, value );
  else if( value > tree->value )
    return deleteNodeTree( tree->right, value );
  else {
    if( tree->left == NULL && tree->right == NULL ) {
      delete tree;
      tree = NULL;
    } else if( tree->left == NULL || tree->right == NULL ) {
      TreeStr aux = tree;
      if( tree->left == NULL ) tree = tree->right;
      else
        tree = tree->left;
      delete aux;
    } else {
      TreeStr minimum = findMinimum( tree->right );
      tree->value     = minimum->value;
      deleteNodeTree( tree->left, tree->value );
    }
    return tree;
  }
}
int insertSetTreeInTable( TreeStr tree, string tableNameResult ) {
  if( tree == NULL ) return 0;
  else {
    if( insertInto( tableNameResult, tree->row, tree->value ) ==
        typeRet::ERROR ) {
      return 1;
    }
    if( tree->left != NULL )
      return 0 + insertSetTreeInTable( tree->left, tableNameResult );
    if( tree->right != NULL )
      return 0 + insertSetTreeInTable( tree->right, tableNameResult );
    return 0;
  }
}

void releaseTree( TreeStr& tree ) {
  if( tree != NULL ) {
    if( tree->left == NULL && tree->right == NULL ) {
      delete tree;
      tree = NULL;
    } else {
      releaseTree( tree->left );
      releaseTree( tree->right );
      delete tree;
      tree = NULL;
    }
  }
}
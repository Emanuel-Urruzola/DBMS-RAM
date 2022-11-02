#include <iostream>
#include <string>
#include "sets.h"
#include "variables.h"
#include "tables.h"
#include "columns.h"
#include "tuples.h"
#include "operations.h"
TreeStr sets = NULL;
bool IsEmptyString( string value, string error ) {
  if( value.length( ) != 0 ) return false;
  cout << "ERROR: El nombre de " + error + " debe ser especificado" << endl;
  return true;
}
bool tableIsNull( Tables table, string tableName, bool negation ) {
  if( table != NULL ) return false;
  if( ! negation )
    cout << "ERROR: La tabla '" << tableName << "' no existe." << endl;
  return true;
}
typeRet createSet( string tableName1, string tableName2, string tableNameResult,
                   string type ) {
  if( IsEmptyString( tableName1, "la tabla 1" ) ) return typeRet::ERROR;
  if( IsEmptyString( tableName1, "la tabla 2" ) ) return typeRet::ERROR;
  if( IsEmptyString( tableName1, "la nueva tabla" ) ) return typeRet::ERROR;
  Tables table1      = findTable( tablesList, tableName1 );
  Tables table2      = findTable( tablesList, tableName2 );
  Tables tableResult = findTable( tablesList, tableNameResult );
  if( tableIsNull( table1, tableName1, false ) ) return typeRet::ERROR;
  if( tableIsNull( table2, tableName2, false ) ) return typeRet::ERROR;
  if( ! tableIsNull( tableResult, tableNameResult, true ) )
    return typeRet::ERROR;
  if( ! checkSchema( table1, table2 ) ) return typeRet::ERROR;
  if( ! createTableUnion( table1, tableNameResult ) ) return typeRet::ERROR;
  if( type == "union" ) {
    if( ! insertIntoSet( table1, tableNameResult, type, sets ) ||
        ! insertIntoSet( table2, tableNameResult, type, sets ) )
      return typeRet::ERROR;
  } else if( type == "intersect" ) {
    if( ! insertIntoTableIntersection( table1, tableNameResult, sets, type ) ||
        ! insertIntoTableIntersection( table2, tableNameResult, sets, type ) )
      return typeRet::ERROR;
  } else if( type == "minus" ) {
    if( ! insertIntoTableIntersection( table1, tableNameResult, sets, type ) ||
        ! insertIntoSet( table2, tableNameResult, type, sets ) ||
        insertSetTreeInTable( sets, tableNameResult ) )
      return typeRet::ERROR;
  } else {
    cout << "Error: tipo incorrecto";
    return typeRet::ERROR;
  }
  releaseTree( sets );
  return typeRet::OK;
}
bool checkSchema( Tables table1, Tables table2 ) {
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
      return false;
    }
    attributesTable1 = attributesTable1->next;
    attributesTable2 = attributesTable2->next;
  }
  if( attributesTable1 != NULL || attributesTable2 != NULL ) {
    cout << "ERROR: Las tablas tienen que tener la misma cantidad de atributos"
         << endl;
    return false;
  }
  return true;
}
bool createTableUnion( Tables table1, string tableNameResult ) {
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
      return false;
    }
    attributesTable1 = attributesTable1->next;
  }
  return true;
}
void getStrings( Tuples tuples, string& names, string& values ) {
  Tuple row = tuples->row;
  while( row != NULL ) {
    names += row->name + ":";
    if( row->type == typeOfData::STRING ) values += row->text + ":";
    else
      values += to_string( row->number ) + ":";
    row = row->next;
  }
  names  = names.substr( 0, names.length( ) - 1 );
  values = values.substr( 0, values.length( ) - 1 );
}
bool insertIntoSet( Tables table, string tableNameResult, string type,
                    TreeStr tree ) {
  Tuples tuples = table->tuple;
  while( tuples != NULL ) {
    string names  = "";
    string values = "";
    getStrings( tuples, names, values );
    if( type == "union" &&
        insertInto( tableNameResult, names, values ) == typeRet::ERROR ) {
      cout << "Hubo un error al ingresar las tuplas en la nueva tabla, revise "
              "las primary key"
           << endl;
      return false;
    } else if( type == "minus" ) {
      deleteNodeTree( tree, values );
    }
    tuples = tuples->next;
  }
  return true;
}
bool insertIntoTableIntersection( Tables table, string tableNameResult,
                                  TreeStr& sets, string type ) {
  // TODO Emanuel: If there are repeated elements within the same table?
  Tuples tuples = table->tuple;
  while( tuples != NULL ) {
    string names  = "";
    string values = "";
    getStrings( tuples, names, values );
    if( ! insertAndCreate( sets, values, names, tableNameResult, type ) )
      return false;
    tuples = tuples->next;
  }
  return true;
}
bool insertAndCreate( TreeStr& tree, string values, string names,
                      string tableNameResult, string type ) {
  if( tree == NULL ) {
    TreeStr newTree = newNodeStr( values, names );
    tree            = newTree;
    return true;
  }
  switch( values.compare( tree->value ) ) {
    case 0:
      if( type == "minus" ) deleteNodeTree( tree, values );
      else {
        if( insertInto( tableNameResult, names, values ) == typeRet::ERROR ) {
          cout << "Hubo un error al ingresar las tuplas en la nueva tabla, "
                  "revise las primary key"
               << endl;
          return false;
        }
      }
      insertAndCreate( tree->right, values, names, tableNameResult, type );
      break;
    case -1:
      insertAndCreate( tree->left, values, names, tableNameResult, type );
      break;
    case 1:
      insertAndCreate( tree->right, values, names, tableNameResult, type );
      break;
  }
  return true;
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
  if( insertInto( tableNameResult, tree->row, tree->value ) == typeRet::ERROR )
    return 1;
  return insertSetTreeInTable( tree->left, tableNameResult ) +
         insertSetTreeInTable( tree->right, tableNameResult );
}
void releaseTree( TreeStr& tree ) {
  if( tree == NULL ) return;
  if( tree->left != NULL || tree->right != NULL ) {
    releaseTree( tree->left );
    releaseTree( tree->right );
  }
  delete tree;
  tree = NULL;
}
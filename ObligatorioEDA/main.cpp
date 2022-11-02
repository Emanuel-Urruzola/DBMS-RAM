#include <iostream>
#include <string>
#include "columns.h"
#include "tables.h"
#include "tuples.h"
#include "variables.h"
#include "print.h"
#include "tests.h"
#include "sets.h"

using namespace std;
void seed( ) {
  createTable( "Subject" );
  addCol( "Subject", "Credits", "integer", "ANY" );
  addCol( "Subject", "Semester", "integer", "ANY" );
  addCol( "Subject", "Name", "string", "ANY" );
  addCol( "Subject", "ID", "integer", "ANY" );
  insertInto( "Subject", "ID:Name:Semester:Credits", "1:PP:1:10" );
  insertInto( "Subject", "ID:Name:Semester:Credits", "-1:EDA:2:13" );
  insertInto( "Subject", "ID:Name:Semester:Credits", "3:ARQ:1:7" );
  insertInto( "Subject", "ID:Name:Semester:Credits", "4:KDD:2:10" );
  // alterCol( "Subject", "Name", "string", "primary_key", "NAME" );

  createTable( "Subject2" );
  addCol( "Subject2", "Credits", "integer", "ANY" );
  addCol( "Subject2", "Semester", "integer", "ANY" );
  addCol( "Subject2", "Name", "string", "ANY" );
  addCol( "Subject2", "ID", "integer", "ANY" );
  insertInto( "Subject2", "ID:Name:Semester:Credits", "4:ER:4:15" );
  insertInto( "Subject2", "ID:Name:Semester:Credits", "6:GFD:5:7" );
  insertInto( "Subject2", "ID:Name:Semester:Credits", "3:ARQ:1:7" );
  insertInto( "Subject2", "ID:Name:Semester:Credits", "8:HTT:2:24" );
  insertInto( "Subject2", "ID:Name:Semester:Credits", "10:AWS:6:20" );
  insertInto( "Subject2", "ID:Name:Semester:Credits", "4:KDD:2:10" );
  // alterCol( "Subject2", "Name", "string", "primary_key", "NAME" );

  printDataTable( "Subject", "\"\"" );
  printDataTable( "Subject2", "\"\"" );
}
int main( ) {
  // runTests( );
  seed( );
  string opc;
  do {
    cin >> opc;
    if( ( opc.substr( 0, opc.find( "(" ) ) == "createTable" ) ) {
      typeRet response = createTable( opc.substr(
          opc.find( "(" ) + 1, opc.length( ) - opc.find( "(" ) - 2 ) );
      if( response == typeRet::OK )
        cout << "Operacion realizada con exito." << endl;
      else if( response == typeRet::NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "dropTable" ) {
      typeRet response = dropTable( opc.substr(
          opc.find( "(" ) + 1, opc.find( ")" ) - opc.find( "(" ) - 1 ) );
      if( response == typeRet::OK )
        cout << "Operacion realizada con exito." << endl;
      else if( response == typeRet::NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "addCol" ) {
      opc                      = opc.erase( 0, opc.find( "(" ) + 1 );
      string table             = opc.substr( 0, opc.find( "," ) );
      opc                      = opc.erase( 0, opc.find( "," ) + 1 );
      string columnName        = opc.substr( 0, opc.find( "," ) );
      opc                      = opc.erase( 0, opc.find( "," ) + 1 );
      string typeOfData        = opc.substr( 0, opc.find( "," ) );
      opc                      = opc.erase( 0, opc.find( "," ) + 1 );
      string typeOfRestriction = opc.substr( 0, opc.find( ")" ) );

      typeRet response =
          addCol( table, columnName, typeOfData, typeOfRestriction );
      if( response == typeRet::OK )
        cout << "Operacion realizada con exito." << endl;
      else if( response == typeRet::NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "dropCol" ) {
      typeRet response =
          dropCol( opc.substr( opc.find( "(" ) + 1,
                               opc.find( "," ) - opc.find( "(" ) - 1 ),
                   opc.substr( opc.find( "," ) + 1,
                               opc.find( ")" ) - opc.find( "," ) - 1 ) );
      if( response == typeRet::OK )
        cout << "Operacion realizada con exito." << endl;
      else if( response == typeRet::NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "alterCol" ) {
      opc                      = opc.erase( 0, opc.find( "(" ) + 1 );
      string table             = opc.substr( 0, opc.find( "," ) );
      opc                      = opc.erase( 0, opc.find( "," ) + 1 );
      string columnName        = opc.substr( 0, opc.find( "," ) );
      opc                      = opc.erase( 0, opc.find( "," ) + 1 );
      string typeOfData        = opc.substr( 0, opc.find( "," ) );
      opc                      = opc.erase( 0, opc.find( "," ) + 1 );
      string typeOfRestriction = opc.substr( 0, opc.find( "," ) );
      opc                      = opc.erase( 0, opc.find( "," ) + 1 );
      string newColumnName     = opc.substr( 0, opc.find( ")" ) );

      typeRet response = alterCol( table, columnName, typeOfData,
                                   typeOfRestriction, newColumnName );
      if( response == typeRet::OK )
        cout << "Operacion realizada con exito." << endl;
      else if( response == typeRet::NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "insertInto" ) {
      opc               = opc.erase( 0, opc.find( "(" ) + 2 );
      string table      = opc.substr( 0, opc.find( "\"" ) );
      opc               = opc.erase( 0, opc.find( "," ) + 2 );
      string attributes = opc.substr( 0, opc.find( "\"" ) );
      opc               = opc.erase( 0, opc.find( "," ) + 2 );
      string values     = opc.substr( 0, opc.find( "\"" ) );
      typeRet response  = insertInto( table, attributes, values );
      if( response == typeRet::OK )
        cout << "Operacion realizada con exito." << endl;
      else if( response == typeRet::NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "delete" ) {
      typeRet response =
          deleteQuery( opc.substr( opc.find( "(" ) + 1,
                                   opc.find( "," ) - opc.find( "(" ) - 1 ),
                       opc.substr( opc.find( "," ) + 1,
                                   opc.find( ")" ) - opc.find( "," ) - 1 ) );
      if( response == typeRet::OK )
        cout << "Operacion realizada con exito." << endl;
      else if( response == typeRet::NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "update" ) {
      opc              = opc.erase( 0, opc.find( "(" ) + 1 );
      string table     = opc.substr( 0, opc.find( "," ) );
      opc              = opc.erase( 0, opc.find( "," ) + 1 );
      string condition = opc.substr( 0, opc.find( "," ) );
      opc              = opc.erase( 0, opc.find( "," ) + 1 );
      string column    = opc.substr( 0, opc.find( "," ) );
      opc              = opc.erase( 0, opc.find( "," ) + 1 );
      string newValue  = opc.substr( 0, opc.find( ")" ) );

      typeRet response = update( table, condition, column, newValue );
      if( response == typeRet::OK )
        cout << "Operacion realizada con exito." << endl;
      else if( response == typeRet::NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "printDataTable" ) {
      string column =
          opc.substr( opc.find( "(" ) + 1,
                      opc.length( ) - ( ( opc.find( "(" ) + 1 ) +
                                        ( opc.length( ) - opc.find( "," ) ) ) );
      string orderBy = opc.substr(
          opc.find( "," ) + 1, ( opc.length( ) - ( opc.find( "," ) + 2 ) ) );
      printDataTable( column, orderBy );

    } else if( opc.substr( 0, opc.find( "(" ) ) == "alterTable" ) {
      opc                 = opc.erase( 0, opc.find( "(" ) + 1 );
      string table        = opc.substr( 0, opc.find( "," ) );
      opc                 = opc.erase( 0, opc.find( "," ) + 1 );
      string newTableName = opc.substr( 0, opc.find( ")" ) );

      typeRet response = modifyTable( table, newTableName );
      if( response == typeRet::OK )
        cout << "Operacion realizada con exito." << endl;
      else if( response == typeRet::NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;
    } else if( opc.substr( 0, opc.find( "(" ) ) == "union" ) {
      opc                = opc.erase( 0, opc.find( "(" ) + 1 );
      string table1      = opc.substr( 0, opc.find( "," ) );
      opc                = opc.erase( 0, opc.find( "," ) + 1 );
      string table2      = opc.substr( 0, opc.find( "," ) );
      opc                = opc.erase( 0, opc.find( "," ) + 1 );
      string tableResult = opc.substr( 0, opc.find( ")" ) );
      if( createSet( table1, table2, tableResult, "union" ) == typeRet::OK ) {
        cout << "Operacion realizada con exito." << endl;
      } else {
        dropTable( tableResult );
      }
    } else if( opc.substr( 0, opc.find( "(" ) ) == "intersect" ) {
      opc                = opc.erase( 0, opc.find( "(" ) + 1 );
      string table1      = opc.substr( 0, opc.find( "," ) );
      opc                = opc.erase( 0, opc.find( "," ) + 1 );
      string table2      = opc.substr( 0, opc.find( "," ) );
      opc                = opc.erase( 0, opc.find( "," ) + 1 );
      string tableResult = opc.substr( 0, opc.find( ")" ) );
      if( createSet( table1, table2, tableResult, "intersect" ) == typeRet::OK ) {
        cout << "Operacion realizada con exito." << endl;
      } else {
        dropTable( tableResult );
      }
    } else if( opc.substr( 0, opc.find( "(" ) ) == "minus" ) {
      opc                = opc.erase( 0, opc.find( "(" ) + 1 );
      string table1      = opc.substr( 0, opc.find( "," ) );
      opc                = opc.erase( 0, opc.find( "," ) + 1 );
      string table2      = opc.substr( 0, opc.find( "," ) );
      opc                = opc.erase( 0, opc.find( "," ) + 1 );
      string tableResult = opc.substr( 0, opc.find( ")" ) );
      if( createSet( table1, table2, tableResult, "minus" ) == typeRet::OK ) {
        cout << "Operacion realizada con exito." << endl;
      } else {
        dropTable( tableResult );
      }
    } else if( opc != "exit" )
      cout << "ERROR: Entrada invalida." << endl;

  } while( opc != "exit" );
}
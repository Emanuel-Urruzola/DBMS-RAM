#include <iostream>
#include <string>
#include "include/columns.h"
#include "include/tables.h"
#include "include/tuples.h"
#include "include/variables.h"
#include "include/print.h"
#include "include/tests.h"

using namespace std;

int main( ) {
  runTests( );
  string opc;
  do {
    cin >> opc;
    if( ( opc.substr( 0, opc.find( "(" ) ) == "createTable" ) ) {
      typeRet response = createTable( opc.substr(
          opc.find( "(" ) + 1, opc.length( ) - opc.find( "(" ) - 2 ) );
      if( response == OK ) cout << "Operacion realizada con exito." << endl;
      else if( response == NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "dropTable" ) {
      typeRet response = dropTable( opc.substr(
          opc.find( "(" ) + 1, opc.find( ")" ) - opc.find( "(" ) - 1 ) );
      if( response == OK ) cout << "Operacion realizada con exito." << endl;
      else if( response == NOT_IMPLEMENTED )
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
      if( response == OK ) cout << "Operacion realizada con exito." << endl;
      else if( response == NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "dropCol" ) {
      typeRet response =
          dropCol( opc.substr( opc.find( "(" ) + 1,
                               opc.find( "," ) - opc.find( "(" ) - 1 ),
                   opc.substr( opc.find( "," ) + 1,
                               opc.find( ")" ) - opc.find( "," ) - 1 ) );
      if( response == OK ) cout << "Operacion realizada con exito." << endl;
      else if( response == NOT_IMPLEMENTED )
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
      if( response == OK ) cout << "Operacion realizada con exito." << endl;
      else if( response == NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "insertInto" ) {
      opc               = opc.erase( 0, opc.find( "(" ) + 2 );
      string table      = opc.substr( 0, opc.find( "\"" ) );
      opc               = opc.erase( 0, opc.find( "," ) + 2 );
      string attributes = opc.substr( 0, opc.find( "\"" ) );
      opc               = opc.erase( 0, opc.find( "," ) + 2 );
      string values     = opc.substr( 0, opc.find( "\"" ) );
      typeRet response  = insertInto( table, attributes, values );
      if( response == OK ) cout << "Operacion realizada con exito." << endl;
      else if( response == NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;

    } else if( opc.substr( 0, opc.find( "(" ) ) == "delete" ) {
      typeRet response =
          deleteQuery( opc.substr( opc.find( "(" ) + 1,
                                   opc.find( "," ) - opc.find( "(" ) - 1 ),
                       opc.substr( opc.find( "," ) + 1,
                                   opc.find( ")" ) - opc.find( "," ) - 1 ) );
      if( response == OK ) cout << "Operacion realizada con exito." << endl;
      else if( response == NOT_IMPLEMENTED )
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
      if( response == OK ) cout << "Operacion realizada con exito." << endl;
      else if( response == NOT_IMPLEMENTED )
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
      if( response == OK ) cout << "Operacion realizada con exito." << endl;
      else if( response == NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;
    } else if( opc != "exit" )
      cout << "ERROR: Entrada invalida." << endl;

  } while( opc != "exit" );
}
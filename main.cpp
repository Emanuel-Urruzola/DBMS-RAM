#include <iostream>
#include <string>

#include "columns.hpp"
#include "tables.hpp"
#include "tuples.hpp"
#include "variables.hpp"
#include "print.hpp"

using namespace std;

int main( ) {
  string opc;
  do {
    cin >> opc;
    if( opc.substr( 0, opc.find( "(" ) ) == "createTable" ) {
      createTable( opc.substr( opc.find( "(" ) + 1,
                               opc.length( ) - opc.find( "(" ) - 2 ) );
    }

    if( opc.substr( 0, opc.find( "(" ) ) == "dropTable" )
      cout << "No implementado" << endl;
    if( opc.substr( 0, opc.find( "(" ) ) == "alterTable" )
      cout << "No implementado" << endl;
    if( opc.substr( 0, opc.find( "(" ) ) == "addCol" ) {
      AddCol( "persona", "color", STRING, ANY );
      AddCol( "persona", "ci", STRING, ANY );
      AddCol( "persona", "nombre", STRING, ANY );
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "dropCol" )
      cout << "No implementado" << endl;
    if( opc.substr( 0, opc.find( "(" ) ) == "alterCol" )
      cout << "No implementado" << endl;
    if( opc.substr( 0, opc.find( "(" ) ) == "insertInto" ) {
      InsertInto( "persona", "ci:nombre:color", "5555:Jona:Negro" );
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "delete" )
      cout << "No implementado" << endl;
    if( opc.substr( 0, opc.find( "(" ) ) == "update" )
      if( update( "persona", "nombre='Pepe'", "ci", "1555000" ) == OK ) {
        cout << "Columna mofidicada sastifactoriamente" << endl;
      } else {
        cout << "Ocurrio un error, por favor revise la instruccion" << endl;
      }
    if( opc.substr( 0, opc.find( "(" ) ) == "printDataTable" ) {
      string column =
          opc.substr( opc.find( "(" ) + 1,
                      opc.length( ) - ( ( opc.find( "(" ) + 1 ) +
                                        ( opc.length( ) - opc.find( "," ) ) ) );
      string orderBy = opc.substr(
          opc.find( "," ) + 1, ( opc.length( ) - ( opc.find( "," ) + 2 ) ) );
      if( PrintDataTable( column, orderBy ) == ERROR ) {
        cout << "Ocurrio un error, revise el nombre de la tabla" << endl;
      }
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "find" ) {  // test
      if( validColumns( "ci:nombre:color", findTable( "persona" ) ) )
        cout << "true";
      else
        cout << "false";
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "test" ) {
      createTable( "persona" );
      AddCol( "persona", "color", STRING, ANY );
      AddCol( "persona", "ci", STRING, ANY );
      AddCol( "persona", "nombre", STRING, ANY );
      InsertInto( "persona", "ci:nombre:color", "5555:Jona:Negro" );
      InsertInto( "persona", "ci:nombre:color", "4444:Steven:Azul" );
      InsertInto( "persona", "ci:nombre:color", "3233:Emanuel:Amarillo" );
      InsertInto( "persona", "ci:nombre:color", "3333:Juan:Verde" );
      InsertInto( "persona", "ci:nombre:color", "9969:Cintya:Rosada" );
      // if( update( "persona", "nombre='Emanuel'", "ci", "1555000" ) == OK ) {
      //   cout << "Column modified successfully" << endl;
      // } else {
      //   cout << "An error occurred, please check the instruction" << endl;
      // }
    }
  } while( opc != "exit" );
}
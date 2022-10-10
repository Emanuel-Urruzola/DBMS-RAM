#include <iostream>
#include <string>

#include "columns.hpp"
#include "tables.hpp"
#include "tuples.hpp"
#include "variables.hpp"

using namespace std;

int main( ) {
  string opc;

  do {
    cin >> opc;

    if( opc == "createTable()" ){
      cout<<"ERROR"<<endl;
    }
    else{
      if(( opc.substr( 0, opc.find( "(" ) ) == "createTable" ))
      createTable( opc.substr( opc.find( "(" ) + 1,
                               opc.length( ) - opc.find( "(" ) - 2 ) );
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "dropTable" ) {
      typeRet response = dropTable( opc.substr(
          opc.find( "(" ) + 1, opc.find( ")" ) - opc.find( "(" ) - 1 ) );
      if( response == OK ) cout << "Operación realizada con éxito";
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "alterTable" )
      cout << "Not implemented yet" << endl;
    // if( opc == "addCol()" || opc == "addCol"){
    //   cout<<"ERROR"<<endl;
    // }
    // else{
      if( opc.substr( 0, opc.find( "(" ) ) == "addCol" ) {
         AddCol( tablesList, "persona", "color", STRING, ANY );
         AddCol( tablesList, "persona", "color", INT, PRIMARY_KEY );
         AddCol( tablesList, "persona", "nombre", STRING, ANY );
         AddCol( tablesList, "persona", "combo", STRING, ANY );
      }
    
    if( opc.substr( 0, opc.find( "(" ) ) == "dropCol" )
      cout << "Not implemented yet" << endl;
    if( opc.substr( 0, opc.find( "(" ) ) == "dropCol" ) {
      typeRet response =
          dropCol( opc.substr( opc.find( "(" ) + 1,
                               opc.find( "," ) - opc.find( "(" ) - 1 ),
                   opc.substr( opc.find( "," ) + 1,
                               opc.find( ")" ) - opc.find( "," ) - 1 ) );
      if( response == OK ) cout << "Operación realizada con éxito";
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "alterCol" )
      cout << "Not implemented yet" << endl;
    if( opc.substr( 0, opc.find( "(" ) ) == "insertInto" )
      cout << "Not implemented yet" << endl;
    if( opc.substr( 0, opc.find( "(" ) ) == "delete" ) {
      typeRet response =
          deleteQuery( opc.substr( opc.find( "(" ) + 1,
                                   opc.find( "," ) - opc.find( "(" ) - 1 ),
                       opc.substr( opc.find( "," ) + 1,
                                   opc.find( ")" ) - opc.find( "," ) - 1 ) );
      if( response == OK ) cout << "Operación realizada con éxito";
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "update" )
      cout << "Not implemented yet" << endl;
    if( opc.substr( 0, opc.find( "(" ) ) == "printDataTable" )
      cout << "Not implemented yet" << endl;
    if( opc.substr( 0, opc.find( "(" ) ) == "find" ) {  // test
      showTables( tablesList );
    }
  } while( opc != "exit" );
}
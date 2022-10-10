#include <iostream>
#include <string>

#include "columns.hpp"
#include "tables.hpp"
#include "tuples.hpp"
#include "variables.hpp"

using namespace std;

void seedTable( ) {
  createTable( "Student" );
  AddCol( "Student", "Lastname", STRING, ANY );
  AddCol( "Student", "Name", STRING, ANY );
  AddCol( "Student", "ID", STRING, PRIMARY_KEY );
  InsertInto( "Student", "ID:Lastname:Name", "11:Netto:Jona" );
  InsertInto( "Student", "ID:Name:Lastname", "22:Emanuel:Urruzola" );
  InsertInto( "Student", "Lastname:ID:Name", "Acosta:33:Steven" );

  createTable( "Subject" );
  AddCol( "Subject", "Credits", STRING, ANY );
  AddCol( "Subject", "Semester", STRING, ANY );
  AddCol( "Subject", "Name", STRING, ANY );
  AddCol( "Subject", "ID", STRING, PRIMARY_KEY );
  InsertInto( "Subject", "ID:Name:Semester:Credits", "1:PP:1:10" );
  InsertInto( "Subject", "ID:Name:Semester:Credits", "2:EDA:2:13" );
  InsertInto( "Subject", "ID:Name:Semester:Credits", "3:ARQ:1:7" );
  InsertInto( "Subject", "ID:Name:Semester:Credits", "4:OS:2:10" );

  // deleteQuery( "Subject", "Name=\"PP\"" );

  // dropCol( "Subject", "Credits" );

  // dropTable( "Student" );

  // Tables tablesCopy = tablesList;
  // cout << "";
}

int main( ) {
  seedTable( );
  string opc;

  do {
    cin >> opc;
    if( opc.substr( 0, opc.find( "(" ) ) == "createTable" ) {
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
    if( opc.substr( 0, opc.find( "(" ) ) == "addCol" )
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
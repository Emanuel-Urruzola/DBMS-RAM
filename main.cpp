#include <iostream>
#include <string>

#include "columns.hpp"
#include "tables.hpp"
#include "tuples.hpp"
#include "variables.hpp"
#include "print.hpp"

using namespace std;

void seedTable( ) {
  createTable("Student");
  createTable("Tools");
  createTable("Teachers");
  modifyTable("Teachers", "Profesoreeeee");
  createTable("Student2");
  createTable("Student2");

  // AddCol( "Student", "Name", "STRING",  ANY);
  // AddCol( "Student", "Lastname", "STRING", ANY );
  // AddCol( "Student", "ID", "INT", PRIMARY_KEY );
  //  InsertInto( "Student", "ID:Lastname:Name", "11:Netto:Jona" );
  // // AddCol( "Student", "ID2", "INT", ANY );
  //  InsertInto( "Student", "ID:Name:Lastname", "22:Emanuel:Urruzola" );
  //  InsertInto( "Student", "Lastname:ID:Name", "Acosta:33:Steven" );
  PrintDataTable( "Student", "" );
  // createTable( "Subject" );
  // AddCol( "Subject", "Credits", INT, ANY );
  // AddCol( "Subject", "Semester", STRING, ANY );
  // AddCol( "Subject", "Name", STRING, ANY );
  // AddCol( "Subject", "ID", STRING, PRIMARY_KEY );
  // InsertInto( "Subject", "ID:Name:Semester:Credits", "1:PP:1:10" );
  // InsertInto( "Subject", "ID:Name:Semester:Credits", "2:EDA:2:13" );
  // InsertInto( "Subject", "ID:Name:Semester:Credits", "3:ARQ:1:7" );
  // InsertInto( "Subject", "ID:Name:Semester:Credits", "4:OS:2:10" );

  // deleteQuery( "Subject", "Name=\"PP\"" );

  // dropCol( "Subject", "Name" );

  //dropTable( "Student" );

  Tables tablesCopy = tablesList;
  cout << "";
}

int main( ) {
  seedTable( );
  string opc;

  do {
    cin >> opc;
    if( opc == "createTable()" ) {
      cout << "ERROR" << endl;
    } else {
      if( ( opc.substr( 0, opc.find( "(" ) ) == "createTable" ) )
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
    // if( opc.substr( 0, opc.find( "(" ) ) == "addCol" ) {
    //   AddCol( "persona", "color", STRING, ANY );
    //   AddCol( "persona", "color", INT, PRIMARY_KEY );
    //   AddCol( "persona", "nombre", STRING, ANY );
    //   AddCol( "persona", "combo", STRING, ANY );
    // }

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
  } while( opc != "exit" );
}
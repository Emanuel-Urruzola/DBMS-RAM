#include <iostream>
#include <string>
#include "include/columns.h"
#include "include/tables.h"
#include "include/tuples.h"
#include "include/variables.h"
#include "include/print.h"

using namespace std;

void seedTable( ) {
  // createTable( "Student" );
  // createTable( "Tools" );
  // createTable( "Teachers" );
  // modifyTable( "Teacher", "Profesoreeeee" );
  // createTable( "Student2" );
  // createTable( "Student2" );
  // AddCol( "Student", "Name", "STRING", ANY );
  // AddCol( "Student", "Lastname", "STRING", ANY );
  // AddCol( "Student", "ID", "INT", PRIMARY_KEY );
  // InsertInto( "Student", "ID:Lastname:Name", "11:Netto:Jona" );
  // InsertInto( "Student", "ID:Lastname:Name", "12:Acosta:Steven" );
  // InsertInto( "Student", "ID:Lastname:Name", "13:Urruzola:Emanuel" );
  // AddCol( "Student", "ID2", "INT", ANY );
  // InsertInto( "Student", "ID:Name:Lastname", "22:Emanuel:Urruzola" );
  // InsertInto( "Student", "Lastname:ID:Name", "Acosta:33:Steven" );
  // PrintDataTable( "Student", "" );
  createTable( "Subject" );
  AddCol( "Subject", "Credits", "integer", "ANY" );
  AddCol( "Subject", "Semester", "integer", "ANY" );
  AddCol( "Subject", "Name", "string", "PRIMARY_KEY" );
  AddCol( "Subject", "ID", "integer", "ANY" );
  InsertInto( "Subject", "ID:Name:Semester:Credits", "1:PP:1:10" );
  InsertInto( "Subject", "ID:Name:Semester:Credits", "-1:EDA:2:13" );
  InsertInto( "Subject", "ID:Name:Semester:Credits", "3:ARQ:1:7" );
  InsertInto( "Subject", "ID:Name:Semester:Credits", "4:KDD:2:10" );

  // deleteQuery( "Subject", "ID>1" );

  // dropCol( "Subject", "ID" );

  // dropTable( "Subject" );

  PrintDataTable( "Subject", "ID" );

  Tables tablesCopy = tablesList;
  cout << "";
}

int main( ) {
  seedTable( );
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
          AddCol( table, columnName, typeOfData, typeOfRestriction );
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
      InsertInto( table, attributes, values );
      typeRet response = InsertInto( table, attributes, values );
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
      PrintDataTable( column, orderBy );

    } else if( opc.substr( 0, opc.find( "(" ) ) == "alterTable" ) {
      opc                 = opc.erase( 0, opc.find( "(" ) + 1 );
      string table        = opc.substr( 0, opc.find( "," ) );
      opc                 = opc.erase( 0, opc.find( "," ) + 1 );
      string newTableName = opc.substr( 0, opc.find( ")" ) );

      typeRet response = modifyTable( table, newTableName );
      if( response == OK ) cout << "Operacion realizada con exito." << endl;
      else if( response == NOT_IMPLEMENTED )
        cout << "La operacion aun no esta implementada." << endl;
    } else
      cout << "ERROR: Entrada invalida." << endl;

  } while( opc != "exit" );
}
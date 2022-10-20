#include <iostream>
#include <string>
#include <stdio.h>

#include "columns.hpp"
#include "tables.hpp"
#include "tuples.hpp"
#include "variables.hpp"
#include "print.hpp"

using namespace std;

void seedTable( ) {
  createTable( "Student" );
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
  InsertInto( "Subject", "ID:", "10" );
  InsertInto( "Subject", "Credits:", "13" );
  InsertInto( "Subject", "CREDITS:", "3" );
  InsertInto( "Subject", "JAJA:", "11" );

  // deleteQuery( "Subject", "ID>1" );

  // dropCol( "Subject", "ID" );

  // dropTable( "Subject" );

  PrintDataTable( "Subject", "Credits" );

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
    if( opc.substr( 0, opc.find( "(" ) ) == "addCol" ) {
      // addCol (Personas,CI,integer,PRIMARY KEY)
      opc                      = opc.erase( 0, opc.find( "(" ) + 1 );
      string table             = opc.substr( 0, opc.find( "," ) );
      opc                      = opc.erase( 0, opc.find( "," ) + 1 );
      string columnName        = opc.substr( 0, opc.find( "," ) );
      opc                      = opc.erase( 0, opc.find( "," ) + 1 );
      string typeOfData        = opc.substr( 0, opc.find( "," ) );
      opc                      = opc.erase( 0, opc.find( "," ) + 1 );
      string typeOfRestriction = opc.substr( 0, opc.find( ")" ) );
      AddCol( table, columnName, typeOfData, typeOfRestriction );
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "dropCol" ) {
      typeRet response =
          dropCol( opc.substr( opc.find( "(" ) + 1,
                               opc.find( "," ) - opc.find( "(" ) - 1 ),
                   opc.substr( opc.find( "," ) + 1,
                               opc.find( ")" ) - opc.find( "," ) - 1 ) );
      if( response == OK ) cout << "Operación realizada con éxito";
    }
    // alterCol (Personas,Name,string,NOT EMPTY, Nombre)
    if( opc.substr( 0, opc.find( "(" ) ) == "alterCol" ) {
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
      if( alterCol( table, columnName, typeOfData, typeOfRestriction,
                    newColumnName ) == OK ) {
        cout << "Columna modificada correctamente" << endl;
      } else {
        cout << "Ocurrio un error" << endl;
      }
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "insertInto" ) {
      // insertInto (“Personas”,“Nombre:CI”,“Telma:3333111” );
      opc               = opc.erase( 0, opc.find( "(" ) + 2 );
      string table      = opc.substr( 0, opc.find( "\"" ) );
      opc               = opc.erase( 0, opc.find( "," ) + 2 );
      string attributes = opc.substr( 0, opc.find( "\"" ) );
      opc               = opc.erase( 0, opc.find( "," ) + 2 );
      string values     = opc.substr( 0, opc.find( "\"" ) );
      cout << attributes << " " << values << endl;
      InsertInto( table, attributes, values );
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "delete" ) {
      typeRet response =
          deleteQuery( opc.substr( opc.find( "(" ) + 1,
                                   opc.find( "," ) - opc.find( "(" ) - 1 ),
                       opc.substr( opc.find( "," ) + 1,
                                   opc.find( ")" ) - opc.find( "," ) - 1 ) );
      if( response == OK ) cout << "Operación realizada con éxito";
    }
    if( opc.substr( 0, opc.find( "(" ) ) == "update" ) {
      opc          = opc.erase( 0, opc.find( "(" ) + 1 );
      string table = opc.substr( 0, opc.find( "," ) );
      opc          = opc.erase( 0, opc.find( "," ) + 1 );
      string condition =
          opc.substr( 0, opc.find( "," ) );  // TODO: If the string has , ?
      opc             = opc.erase( 0, opc.find( "," ) + 1 );
      string column   = opc.substr( 0, opc.find( "," ) );
      opc             = opc.erase( 0, opc.find( "," ) + 1 );
      string newValue = opc.substr( 0, opc.find( ")" ) );
      // TODO: Evaluate if a string is ""
      if( update( table, condition, column, newValue ) == OK ) {
        cout << "Columna mofidicada satisfactoriamente" << endl;
      } else {
        cout << "Ocurrio un error, por favor revise la instruccion" << endl;
      }
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
    if( opc.substr( 0, opc.find( "(" ) ) == "modifyTable" ) {
      opc                 = opc.erase( 0, opc.find( "(" ) + 1 );
      string table        = opc.substr( 0, opc.find( "," ) );
      opc                 = opc.erase( 0, opc.find( "," ) + 1 );
      string newTableName = opc.substr( 0, opc.find( ")" ) );
      modifyTable( table, newTableName );
    }
  } while( opc != "exit" );
}
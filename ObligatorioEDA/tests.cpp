#include <iostream>
#include "tests.h"
#include "variables.h"
#include "tables.h"
#include "columns.h"
#include "tuples.h"
#include "print.h"

void runTests( ) {
  // casos de prueba
  // crear tabla
  if( createTable( "Subject" ) == typeRet::OK ) cout << "OK" << endl;
  else
    cout << "FALLO 1" << endl;

  // Si nombreTabla existe.
  if( createTable( "Subject" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 2" << endl;
  // Si nombreTabla no se especifica
  if( createTable( "" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 3" << endl;

  // eliminar tabla
  if( dropTable( "Subject" ) == typeRet::OK ) cout << "OK" << endl;
  else
    cout << "FALLO 4" << endl;

  // Si nombreTabla no existe.
  if( dropTable( "Subject" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 5" << endl;
  // Si nombreTabla no se especifica
  if( dropTable( "" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 6" << endl;

  if( createTable( "Subject" ) == typeRet::OK ) cout << "OK" << endl;
  else
    cout << "FALLO 7" << endl;

  // agregar columna
  if( addCol( "Subject", "ID", "integer", "PRIMARY_KEY" ) == typeRet::OK )
    cout << "OK" << endl;
  else
    cout << "FALLO 8" << endl;

  // Si nombreTabla no existe o no se especifica.
  if( addCol( "Subject2", "ID", "integer", "PRIMARY_KEY" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 9" << endl;

  // Si nombreCol existe.
  if( addCol( "Subject", "ID", "integer", "PRIMARY_KEY" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 9" << endl;

  // Si nombreCol no se especifica.
  if( addCol( "Subject", "", "integer", "PRIMARY_KEY" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 10" << endl;

  // Si tipoCol no se especifica.
  if( addCol( "Subject", "Nombre", "", "ANY" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 11" << endl;

  // Si tipoCol no corresponde.
  if( addCol( "Subject", "Nombre", "str", "ANY" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 12" << endl;

  // Si calificadorCol no se especifica.
  if( addCol( "Subject", "Nombre", "string", "" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 13" << endl;

  // Si calificadorCol no corresponde.
  if( addCol( "Subject", "Nombre", "string", "FOREIGN" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 14" << endl;

  // Si la tabla nombreTabla tiene al menos una tupla y se agrega un
  // calificador
  // distinto a ANY

  // eliminar columna
  // Si nombreTabla no existe .
  if( dropCol( "Subject2", "ID" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 15" << endl;
  // Si nombreTabla no se especifica.
  if( dropCol( "", "ID" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 16" << endl;

  // Si nombreCol no existe.
  if( dropCol( "Subject", "ID2" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 17" << endl;

  // Si nombreCol no se especifica.
  if( dropCol( "Subject", "" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 18" << endl;

  // Si nombreCol es la PRIMARY KEY y la tabla tiene m�s columnas.
  addCol( "Subject", "Nombre", "string", "ANY" );

  if( dropCol( "Subject", "ID" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 19" << endl;

  dropCol( "Subject", "Nombre" );

  // insertar tupla Si nombreTabla no existe.

  if( insertInto( "Subject2", "ID", "4" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 20" << endl;

  // Si nombreTabla no se especifica.
  if( insertInto( "", "ID", "4" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 21" << endl;

  // Si columnaTupla no existe.
  addCol( "Subject", "Nombre", "string", "ANY" );
  if( insertInto( "Subject", "ID2:Nombre", "4:Steven" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 22" << endl;
  dropCol( "Subject", "Nombre" );

  // Si la tabla nombreTabla no tiene columnas.
  // dropCol( "Subject", "ID" );

  // if( insertInto( "Subject", "ID", "4" ) == ERROR ) cout << "OK" << endl;
  // else
  //   cout << "FALLO" << endl;

  // addCol( "Subject", "ID", "integer", "PRIMARY_KEY" );

  // Si el valor de la PRIMARY KEY se repite en otra tupla.
  insertInto( "Subject", "ID", "1" );

  if( insertInto( "Subject", "ID", "1" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 23" << endl;

  // eliminar tupla
  // Si nombreTabla no existe.
  if( deleteQuery( "Subject2", "ID=1" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 24" << endl;

  // Si nombreTabla no se especifica.
  if( deleteQuery( "", "ID=1" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 25" << endl;

  // Si la columna dentro de condicionEliminar no pertenece a la tabla
  if( deleteQuery( "Subject", "ID2=1" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 26" << endl;

  // listar tabla
  // Si nombreTabla no existe.
  if( printDataTable( "Subject2", "ID" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 27" << endl;

  // Si nombreTabla no se especifico.
  if( printDataTable( "", "ID" ) == typeRet::ERROR ) cout << "OK" << endl;
  else
    cout << "FALLO 28" << endl;
  // modificar columna
  // Si nombreTabla no existe.
  if( alterCol( "Subject2", "ID", "string", "PRIMARY_KEY", "ID2" ) ==
      typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 29" << endl;

  // Si nombreTabla no se especifica.
  if( alterCol( "", "ID", "string", "PRIMARY_KEY", "ID2" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 30" << endl;

  // Si nombreCol no existe.
  if( alterCol( "Subject", "ID2", "string", "PRIMARY_KEY", "ID2" ) ==
      typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 31" << endl;

  // Si nombreCol no se especifica.
  if( alterCol( "Subject", "", "string", "PRIMARY_KEY", "ID2" ) ==
      typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 32" << endl;

  // Si nombreCol es la PRIMARY KEY y la tabla tiene m�s columnas.
  // addCol( "Subject", "Nombre", "string", "ANY" );

  // if( alterCol( "Subject2", "ID", "string", "PRIMARY_KEY", "ID2" ) ==
  // ERROR )
  //   cout << "OK" << endl;
  // else
  //   cout << "FALLO" << endl;
  // dropCol( "Subject", "Nombre" );

  // Si tipoColNuevo no se especifica.
  if( alterCol( "Subject", "ID", "", "PRIMARY_KEY", "ID2" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 33" << endl;

  // Si tipoColNuevo no corresponde.
  if( alterCol( "Subject", "ID", "boolean", "PRIMARY_KEY", "ID2" ) ==
      typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 34" << endl;

  // Si calificadorColNuevo no se especifica.
  if( alterCol( "Subject", "ID", "string", "", "ID2" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 35" << endl;

  // Si calificadorColNuevo no corresponde.
  if( alterCol( "Subject", "ID", "string", "primario", "ID2" ) ==
      typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 36" << endl;

  // Si nombreCol no se especifica
  if( alterCol( "Subject", "ID", "string", "PRIMARY_KEY", "" ) ==
      typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 37" << endl;
  // modificar tupla
  // Si nombreTabla no existe.
  deleteQuery( "Subject", "" );
  addCol( "Subject", "Nombre", "string", "ANY" );

  insertInto( "Subject", "ID:Nombre", "1:Steven" );
  insertInto( "Subject", "ID:Nombre", "2:Emanuel" );
  insertInto( "Subject", "ID:Nombre", "3:Jonathan" );
  if( update( "Subject2", "ID=3", "Nombre", "Netto" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 38" << endl;
  deleteQuery( "Subject", "" );
  dropCol( "Subject", "Nombre" );

  // Si nombreTabla no se especifica.
  addCol( "Subject", "Nombre", "string", "ANY" );
  insertInto( "Subject", "ID:Nombre", "1:Steven" );
  insertInto( "Subject", "ID:Nombre", "2:Emanuel" );
  insertInto( "Subject", "ID:Nombre", "3:Jonathan" );
  if( update( "", "ID=3", "Nombre", "Netto" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 39" << endl;
  deleteQuery( "Subject", "" );
  dropCol( "Subject", "Nombre" );

  // Si la columna dentro de condicionModificar no pertenece a la tabla
  // nombreTabla.
  addCol( "Subject", "Nombre", "string", "ANY" );
  insertInto( "Subject", "ID:Nombre", "1:Steven" );
  insertInto( "Subject", "ID:Nombre", "2:Emanuel" );
  insertInto( "Subject", "ID:Nombre", "3:Jonathan" );
  if( update( "Subject2", "ID2=3", "Nombre", "Netto" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 40" << endl;
  deleteQuery( "Subject", "" );
  dropCol( "Subject", "Nombre" );

  // Si la columna dentro de condicionModificar no se especifica.
  addCol( "Subject", "Nombre", "string", "ANY" );
  insertInto( "Subject", "ID:Nombre", "1:Steven" );
  insertInto( "Subject", "ID:Nombre", "2:Emanuel" );
  insertInto( "Subject", "ID:Nombre", "3:Jonathan" );
  if( update( "Subject2", "=3", "Nombre", "Netto" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 41" << endl;
  deleteQuery( "Subject", "" );
  dropCol( "Subject", "Nombre" );

  // Si la columna dentro de columnaModificar no pertenece a la tabla
  // nombreTabla.
  addCol( "Subject", "Nombre", "string", "ANY" );
  insertInto( "Subject", "ID:Nombre", "1:Steven" );
  insertInto( "Subject", "ID:Nombre", "2:Emanuel" );
  insertInto( "Subject", "ID:Nombre", "3:Jonathan" );
  if( update( "Subject2", "ID=3", "Apellido", "Netto" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 42" << endl;
  deleteQuery( "Subject", "" );
  dropCol( "Subject", "Nombre" );

  // Si la columna dentro de columnaModificar no se especifica.
  addCol( "Subject", "Nombre", "string", "ANY" );
  insertInto( "Subject", "ID:Nombre", "1:Steven" );
  insertInto( "Subject", "ID:Nombre", "2:Emanuel" );
  insertInto( "Subject", "ID:Nombre", "3:Jonathan" );
  if( update( "Subject2", "ID=3", "", "Netto" ) == typeRet::ERROR )
    cout << "OK" << endl;
  else
    cout << "FALLO 43" << endl;
  deleteQuery( "Subject", "" );
  dropCol( "Subject", "Nombre" );
  dropCol( "Subject", "ID" );
}
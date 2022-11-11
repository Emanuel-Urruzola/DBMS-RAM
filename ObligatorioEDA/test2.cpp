#include <iostream>
#include <string>
#include "variables.h"
#include "tuples.h"
#include "columns.h"
#include "tables.h"

using namespace std;
string line = "************************* ";
void testMessage( typeRet type, string test, typeRet expected ) {
  if( type != expected )
    cout << endl << line << test << " FALLO    " << line << endl << endl;
  else
    cout << line << test << " APROBADO " << line << endl;
}
void test2( ) {
  //*********** TABLAS **************
  //*********************************
  testMessage( createTable( "subject" ), "TEST1", typeRet::OK );  // crear tabla
  // crear tabla sin nombre
  testMessage( createTable( "" ), "TEST2", typeRet::ERROR );
  // crear la misma tabla
  testMessage( createTable( "subject" ), "TEST3", typeRet::ERROR );
  // crear otra tabla
  testMessage( createTable( "subject2" ), "TEST4", typeRet::OK );
  // eliminar tablas
  testMessage( dropTable( "subject" ), "TEST5", typeRet::OK );
  // eliminar tabla sin poner el nombre de la tabla
  testMessage( dropTable( "" ), "TEST5", typeRet::ERROR );
  // eliminar tabla que no existe
  testMessage( dropTable( "dsfsdjkfh" ), "TEST5-2", typeRet::ERROR );
  createTable( "subject" );
  // modificar el nombre por otro existente
  testMessage( modifyTable( "subject", "subject2" ), "TEST6", typeRet::ERROR );
  // cambiar el nombre
  testMessage( modifyTable( "subject", "subject1" ), "TEST7", typeRet::OK );
  // primer tabla sin nombre
  testMessage( modifyTable( "", "subject1" ), "TEST8", typeRet::ERROR );
  // segunda tabla sin nombre
  testMessage( modifyTable( "subject1", "" ), "TEST9", typeRet::ERROR );

  //*********** COLUMNAS ************
  //*********************************
  // ingresar una columna
  testMessage( addCol( "subject1", "ID", "integer", "PRIMARY_KEY" ), "TEST10",
               typeRet::OK );
  // ingresar una columna sin tabla
  testMessage( addCol( "", "ID", "integer", "PRIMARY_KEY" ), "TEST11",
               typeRet::ERROR );
  // ingresar una columna sin nombre de columna
  testMessage( addCol( "subject1", "", "integer", "PRIMARY_KEY" ), "TEST12",
               typeRet::ERROR );
  // ingresar una columna sin tipo de columna
  testMessage( addCol( "subject1", "ID", "", "PRIMARY_KEY" ), "TEST13",
               typeRet::ERROR );
  // ingresar una columna sin tipo de restriccion
  testMessage( addCol( "subject1", "ID", "integer", "" ), "TEST14",
               typeRet::ERROR );
  // ingresar una columna con un tipo incorrecto
  testMessage( addCol( "subject1", "Name", "cadena", "PRIMARY_KEY" ), "TEST15",
               typeRet::ERROR );
  // ingresar una columna con una resticcion incorrecta
  testMessage( addCol( "subject1", "Name", "string", "DSFEWRF" ), "TEST16",
               typeRet::ERROR );
  // ingresar otra primary key ya existiendo otra
  testMessage( addCol( "subject1", "Name", "string", "PRIMARY_KEY" ), "TEST17",
               typeRet::ERROR );
  // ingresar otra columna
  testMessage( addCol( "subject1", "Name", "string", "ANY" ), "TEST18",
               typeRet::OK );
  addCol( "subject1", "Semester", "integer", "ANY" );
  // ingresar la misma columna 2 veces
  testMessage( addCol( "subject1", "Name", "string", "ANY" ), "TEST19",
               typeRet::ERROR );
  testMessage( dropCol( "", "Name" ), "TEST20", typeRet::ERROR );
  // eliminar una columna sin especificar columna
  testMessage( dropCol( "subject1", "" ), "TEST21", typeRet::ERROR );
  // eliminar una columna que no existe
  testMessage( dropCol( "subject1", "Name2" ), "TEST22", typeRet::ERROR );
  // eliminar una columna de una tabla que no existe
  testMessage( dropCol( "FSdfsd", "Name" ), "TEST23", typeRet::ERROR );
  // eliminar una columna
  testMessage( dropCol( "subject1", "Name" ), "TEST24", typeRet::OK );
  // eliminar una columna: Si nombreCol es la PRIMARY KEY y la tabla tiene más
  // columnas.
  testMessage( dropCol( "subject1", "ID" ), "TEST25", typeRet::ERROR );
  // modificar columna sin especificar nombre de la tabla
  testMessage( alterCol( "", "Semester", "string", "ANY", "semester" ),
               "TEST26", typeRet::ERROR );
  // modificar columna sin especificar nombre de columnna
  testMessage( alterCol( "subject1", "", "string", "ANY", "semester" ),
               "TEST27", typeRet::ERROR );
  // modificar columna sin especificar tipo
  testMessage( alterCol( "subject1", "Semester", "", "ANY", "semester" ),
               "TEST28", typeRet::ERROR );
  // modificar columna sin especificar restriccion
  testMessage( alterCol( "subject1", "Semester", "string", "", "semester" ),
               "TEST29", typeRet::ERROR );
  // modificar columna sin especificar nuevo nombre
  testMessage( alterCol( "subject1", "Semester", "string", "ANY", "" ),
               "TEST30", typeRet::ERROR );
  // modificar columna sin especificar nombre de la tabla
  testMessage( alterCol( "dsafasd", "Semester", "string", "ANY", "semester" ),
               "TEST31", typeRet::ERROR );
  // modificar columna sin especificar nombre de columnna
  testMessage(
      alterCol( "subject1", "adsfasfasdf", "string", "ANY", "semester" ),
      "TEST32", typeRet::ERROR );
  // modificar columna sin especificar tipo
  testMessage( alterCol( "subject1", "Semester", "werfwf", "ANY", "semester" ),
               "TEST33", typeRet::ERROR );
  // modificar columna sin especificar restriccion
  testMessage(
      alterCol( "subject1", "Semester", "string", "dfsgsdfgr", "semester" ),
      "TEST34", typeRet::ERROR );
  //  modificar si nombreCol es la PRIMARY KEY y la tabla tiene más
  testMessage( alterCol( "subject1", "ID", "integer", "ANY", "semester" ),
               "TEST35", typeRet::ERROR );
  // modificar columna
  testMessage( alterCol( "subject1", "Semester", "string", "ANY", "Semester" ),
               "TEST36", typeRet::OK );
  //*********** TUPLAS **************
  //*********************************
  // insertar tupla sin especificar tabla
  testMessage( insertInto( "", "ID:Semester", "1:4" ), "TEST37",
               typeRet::ERROR );
  // insertar tupla
  testMessage( insertInto( "subject1", "ID:Semester", "2:4" ), "TEST40",
               typeRet::OK );
  // insertar tupla con mismo id
  // testMessage( insertInto( "subject1", "ID:Semester", "2:6" ), "TEST41",
  //              typeRet::ERROR );
  // insertar otra tupla
  testMessage( insertInto( "subject1", "ID:Semester", "3:4" ), "TEST42",
               typeRet::OK );
  // // insertar tupla con primary key empty
  // testMessage( insertInto( "subject1", "ID:Semester", "-1:4" ), "TEST43",
  //              typeRet::ERROR );
  // Si nombreTabla no existe o no se especifica.
  //  Si la columna dentro de condicionModificar no pertenece a la
  // tabla nombreTabla o no se especifica.
  //  Si la columna dentro de columnaModificar no pertenece a la
  // tabla nombreTabla o no se especifica
  // No se considera error si ninguna tupla cumple la condición.
  // Además se asume que la
  // modificar tupla sin especificar tabla
  testMessage( update( "", "id>2", "Semester", "100" ), "TEST43",
               typeRet::ERROR );
  // modificar tupla sin especificar columna a modificar
  testMessage( update( "subject1", "ID>2", "", "100" ), "TEST44",
               typeRet::ERROR );
  // TODO Emanuel name="" esta mal, es directamente meter ""
  // modificar tupla sin nuevo valor de columna a modificar
  testMessage( update( "subject1", "ID>2", "Semester", "" ), "TEST45",
               typeRet::ERROR );
  // modificar tupla en tabla no existente
  testMessage( update( "welkjnf", "ID>2", "Semester", "100" ), "TEST46",
               typeRet::ERROR );
  // modificar tupla en columna no existente
  testMessage( update( "subject1", "ID>2", "dsfsadfqwe", "100" ), "TEST47",
               typeRet::ERROR );
  // modificar tupla con tipo incorrecto
  testMessage( update( "subject1", "ID>2", "ID", "dstdrtre" ),
               "TEST48", typeRet::ERROR );
  // modificar tupla con columna en condicion no existente
  testMessage( update( "subject1", "asdfasdfasdf>2", "dsfsadfqwe", "100" ),
               "TEST49", typeRet::ERROR );
}
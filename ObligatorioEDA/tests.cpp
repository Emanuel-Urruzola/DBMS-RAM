#include <iostream>
#include "tests.h"
#include "variables.h"
#include "tables.h"
#include "columns.h"
#include "tuples.h"
#include "print.h"

void runTests() {
    // casos de prueba
    // crear tabla
    if (createTable("Subject") == OK) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreTabla existe.
    if (createTable("Subject") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    // Si nombreTabla no se especifica
    if (createTable("") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // eliminar tabla
    if (dropTable("Subject") == OK) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreTabla no existe.
    if (dropTable("Subject") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    // Si nombreTabla no se especifica
    if (dropTable("") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    if (createTable("Subject") == OK) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // agregar columna
    if (addCol("Subject", "ID", "integer", "PRIMARY_KEY") == OK)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreTabla no existe o no se especifica.
    if (addCol("Subject2", "ID", "integer", "PRIMARY_KEY") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreCol existe.
    if (addCol("Subject", "ID", "integer", "PRIMARY_KEY") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreCol no se especifica.
    if (addCol("Subject", "", "integer", "PRIMARY_KEY") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si tipoCol no se especifica.
    if (addCol("Subject", "Nombre", "", "ANY") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si tipoCol no corresponde.
    if (addCol("Subject", "Nombre", "str", "ANY") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si calificadorCol no se especifica.
    if (addCol("Subject", "Nombre", "string", "") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si calificadorCol no corresponde.
    if (addCol("Subject", "Nombre", "string", "FOREIGN") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si la tabla nombreTabla tiene al menos una tupla y se agrega un
    // calificador
    // distinto a ANY

    // eliminar columna
    // Si nombreTabla no existe .
    if (dropCol("Subject2", "ID") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    // Si nombreTabla no se especifica.
    if (dropCol("", "ID") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreCol no existe.
    if (dropCol("Subject", "ID2") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreCol no se especifica.
    if (dropCol("Subject", "") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreCol es la PRIMARY KEY y la tabla tiene más columnas.
    addCol("Subject", "Nombre", "string", "ANY");

    if (dropCol("Subject", "ID") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    dropCol("Subject", "Nombre");

    // insertar tupla Si nombreTabla no existe.

    if (insertInto("Subject2", "ID", "4") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreTabla no se especifica.
    if (insertInto("", "ID", "4") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si columnaTupla no existe.
    addCol("Subject", "Nombre", "string", "ANY");
    if (insertInto("Subject", "ID2:Nombre", "4:Steven") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    dropCol("Subject", "Nombre");

    // Si la tabla nombreTabla no tiene columnas.
    // dropCol( "Subject", "ID" );

    // if( insertInto( "Subject", "ID", "4" ) == ERROR ) cout << "OK" << endl;
    // else
    //   cout << "FALLO" << endl;

    // addCol( "Subject", "ID", "integer", "PRIMARY_KEY" );

    // Si el valor de la PRIMARY KEY se repite en otra tupla.
    insertInto("Subject", "ID", "1");

    if (insertInto("Subject", "ID", "1") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // eliminar tupla
    // Si nombreTabla no existe.
    if (deleteQuery("Subject2", "ID=1") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreTabla no se especifica.
    if (deleteQuery("", "ID=1") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si la columna dentro de condicionEliminar no pertenece a la tabla
    if (deleteQuery("Subject", "ID2=1") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // listar tabla
    // Si nombreTabla no existe.
    if (printDataTable("Subject2", "ID") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreTabla no se especifico.
    if (printDataTable("", "ID") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    // modificar columna
    // Si nombreTabla no existe.
    if (alterCol("Subject2", "ID", "string", "PRIMARY_KEY", "ID2") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreTabla no se especifica.
    if (alterCol("", "ID", "string", "PRIMARY_KEY", "ID2") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreCol no existe.
    if (alterCol("Subject", "ID2", "string", "PRIMARY_KEY", "ID2") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreCol no se especifica.
    if (alterCol("Subject", "", "string", "PRIMARY_KEY", "ID2") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreCol es la PRIMARY KEY y la tabla tiene más columnas.
    // addCol( "Subject", "Nombre", "string", "ANY" );

    // if( alterCol( "Subject2", "ID", "string", "PRIMARY_KEY", "ID2" ) ==
    // ERROR )
    //   cout << "OK" << endl;
    // else
    //   cout << "FALLO" << endl;
    // dropCol( "Subject", "Nombre" );

    // Si tipoColNuevo no se especifica.
    if (alterCol("Subject", "ID", "", "PRIMARY_KEY", "ID2") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si tipoColNuevo no corresponde.
    if (alterCol("Subject", "ID", "boolean", "PRIMARY_KEY", "ID2") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si calificadorColNuevo no se especifica.
    if (alterCol("Subject", "ID", "string", "", "ID2") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si calificadorColNuevo no corresponde.
    if (alterCol("Subject", "ID", "string", "primario", "ID2") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;

    // Si nombreCol no se especifica
    if (alterCol("Subject", "ID", "string", "PRIMARY_KEY", "") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    // modificar tupla
    // Si nombreTabla no existe.
    deleteQuery("Subject", "");
    addCol("Subject", "Nombre", "string", "ANY");

    insertInto("Subject", "ID:Nombre", "1:Steven");
    insertInto("Subject", "ID:Nombre", "2:Emanuel");
    insertInto("Subject", "ID:Nombre", "3:Jonathan");
    if (update("Subject2", "ID=3", "Nombre", "Netto") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    deleteQuery("Subject", "");
    dropCol("Subject", "Nombre");

    // Si nombreTabla no se especifica.
    addCol("Subject", "Nombre", "string", "ANY");
    insertInto("Subject", "ID:Nombre", "1:Steven");
    insertInto("Subject", "ID:Nombre", "2:Emanuel");
    insertInto("Subject", "ID:Nombre", "3:Jonathan");
    if (update("", "ID=3", "Nombre", "Netto") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    deleteQuery("Subject", "");
    dropCol("Subject", "Nombre");

    // Si la columna dentro de condicionModificar no pertenece a la tabla
    // nombreTabla.
    addCol("Subject", "Nombre", "string", "ANY");
    insertInto("Subject", "ID:Nombre", "1:Steven");
    insertInto("Subject", "ID:Nombre", "2:Emanuel");
    insertInto("Subject", "ID:Nombre", "3:Jonathan");
    if (update("Subject2", "ID2=3", "Nombre", "Netto") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    deleteQuery("Subject", "");
    dropCol("Subject", "Nombre");

    // Si la columna dentro de condicionModificar no se especifica.
    addCol("Subject", "Nombre", "string", "ANY");
    insertInto("Subject", "ID:Nombre", "1:Steven");
    insertInto("Subject", "ID:Nombre", "2:Emanuel");
    insertInto("Subject", "ID:Nombre", "3:Jonathan");
    if (update("Subject2", "=3", "Nombre", "Netto") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    deleteQuery("Subject", "");
    dropCol("Subject", "Nombre");

    // Si la columna dentro de columnaModificar no pertenece a la tabla
    // nombreTabla.
    addCol("Subject", "Nombre", "string", "ANY");
    insertInto("Subject", "ID:Nombre", "1:Steven");
    insertInto("Subject", "ID:Nombre", "2:Emanuel");
    insertInto("Subject", "ID:Nombre", "3:Jonathan");
    if (update("Subject2", "ID=3", "Apellido", "Netto") == ERROR)
        cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    deleteQuery("Subject", "");
    dropCol("Subject", "Nombre");

    // Si la columna dentro de columnaModificar no se especifica.
    addCol("Subject", "Nombre", "string", "ANY");
    insertInto("Subject", "ID:Nombre", "1:Steven");
    insertInto("Subject", "ID:Nombre", "2:Emanuel");
    insertInto("Subject", "ID:Nombre", "3:Jonathan");
    if (update("Subject2", "ID=3", "", "Netto") == ERROR) cout << "OK" << endl;
    else
        cout << "FALLO" << endl;
    deleteQuery("Subject", "");
    dropCol("Subject", "Nombre");
}
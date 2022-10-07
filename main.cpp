#include <iostream>
#include <string>

#include "columns.hpp"
#include "tables.hpp"
#include "tuples.hpp"
#include "variables.hpp"

using namespace std;

int main() {
  string opc;
  do {
    cin >> opc;
    if (opc.substr(0, opc.find("(")) == "createTable") {
      createTable(tablesList, opc.substr(opc.find("(") + 1,
                                         opc.length() - opc.find("(") - 2));
    }

    if (opc.substr(0, opc.find("(")) == "dropTable")
      cout << "Not implemented yet" << endl;
    if (opc.substr(0, opc.find("(")) == "alterTable")
      cout << "Not implemented yet" << endl;
    if (opc.substr(0, opc.find("(")) == "addCol") {
      AddCol("persona", "color", STRING, ANY);
      AddCol("persona", "ci", STRING, ANY);
      AddCol("persona", "nombre", STRING, ANY);
    }
    if (opc.substr(0, opc.find("(")) == "dropCol")
      cout << "Not implemented yet" << endl;
    if (opc.substr(0, opc.find("(")) == "alterCol")
      cout << "Not implemented yet" << endl;
    if (opc.substr(0, opc.find("(")) == "insertInto")
      cout << "Not implemented yet" << endl;
    if (opc.substr(0, opc.find("(")) == "delete")
      cout << "Not implemented yet" << endl;
    if (opc.substr(0, opc.find("(")) == "update")
      cout << "Not implemented yet" << endl;
    if (opc.substr(0, opc.find("(")) == "printDataTable")
      cout << "Not implemented yet" << endl;
    if (opc.substr(0, opc.find("(")) == "find") {  // test
      if (validColumns("ci:nombre:color", findTable(tablesList, "persona")))
        cout << "true";
      else
        cout << "false";
    }
    showTables(tablesList);
  } while (opc != "exit");
}
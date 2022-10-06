#include "variables.hpp"
#include "tables.hpp"
#include <iostream>
#include <string>
using namespace std;

Tables tablesList = NULL;
int main()
{
  string opc;
  do
  {
    cin >> opc;
    if (opc.substr(0, opc.find("(")) == "createTable")
    {
      createTable(tablesList, opc.substr(opc.find("(") + 1,
                                         opc.length() - opc.find("(") - 2));
    }

    if (opc.substr(0, opc.find("(")) == "dropTable")
      cout << "Not implemented yet" << endl;
    if (opc.substr(0, opc.find("(")) == "alterTable")
      cout << "Not implemented yet" << endl;
    if (opc.substr(0, opc.find("(")) == "addCol")
      cout << "Not implemented yet" << endl;
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
    showTables(tablesList);
  } while (opc != "exit");
}
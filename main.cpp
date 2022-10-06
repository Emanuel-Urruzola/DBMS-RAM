#include <iostream>
#include <string>
#include "variables.h"
using std::string, std::cout, std::cin, std::endl;

int main(){
  string opc;
  do{
    cin >> opc;
    if ( opc.substr( 0 , opc.find("(") ) == "createTable" )
      cout << "Not implemented yet" << endl;
    if ( opc.substr( 0 , opc.find("(") ) == "dropTable" )
      cout << "Not implemented yet" << endl;
    if ( opc.substr( 0 , opc.find("(") ) == "alterTable" )
      cout << "Not implemented yet" << endl;
    if ( opc.substr( 0 , opc.find("(") ) == "addCol" )
      cout << "Not implemented yet" << endl;
    if ( opc.substr( 0 , opc.find("(") ) == "dropCol" )
      cout << "Not implemented yet" << endl;
    if ( opc.substr( 0 , opc.find("(") ) == "alterCol" )
      cout << "Not implemented yet" << endl;
    if ( opc.substr( 0 , opc.find("(") ) == "insertInto" )
      cout << "Not implemented yet" << endl;
    if ( opc.substr( 0 , opc.find("(") ) == "delete" )
      cout << "Not implemented yet" << endl;
    if ( opc.substr( 0 , opc.find("(") ) == "update" )
      cout << "Not implemented yet" << endl;
    if ( opc.substr( 0 , opc.find("(") ) == "printDataTable" )
      cout << "Not implemented yet" << endl;
  }while( opc != "exit" );
}
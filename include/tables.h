#ifndef _TABLES_H
#define _TABLES_H
#include "variables.h"

typeRet createTable( string );

void showTables( Tables );

Tables findTable( string );

typeRet dropTable( string );

typeRet modifyTable( string, string );

#endif
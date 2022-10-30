#pragma once
#include "variables.h"

typeRet createTable( string );

typeRet printTables( Tables );

Tables findTable( Tables, string );

typeRet dropTable( string );

typeRet modifyTable( string, string );

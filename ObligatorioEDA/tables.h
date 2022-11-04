#pragma once
#include "variables.h"

typeRet createTable( string );

typeRet printTables( Tables );

Tables findTable( Tables, string );

typeRet dropTable( string );

typeRet modifyTable( string, string );

bool isIncluded( Tables, string );

void insertTable( Tables, string );

Tables minTable( Tables );

Tables deleteTable( Tables &, string );

typeRet printMetadata( string tableName );

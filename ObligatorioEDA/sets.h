#pragma once
#include "variables.h"

typeRet insertIntoTableUnion( Tables, string );

typeRet createTableUnion( Tables, Tables, string );

typeRet checkSchema( Tables, Tables, string );

typeRet unionDB( string, string, string );
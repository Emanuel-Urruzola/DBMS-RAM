#pragma once
#include "variables.h"

typeRet addCol( string, string, string, string );

typeRet pkCondition( typeOfData, int, Tuples );

typeRet alterCol( string, string, string, string, string );

typeRet dropCol( string, string );

void showColumns( Tables );

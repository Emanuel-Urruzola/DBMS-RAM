#ifndef _COLUMNS_H
#define _COLUMNS_H
#include "variables.h"

typeRet AddCol( string, string, string, string );

typeRet PKCondition( typeOfData, int, Tuples );

typeRet alterCol( string, string, string, string, string );

typeRet dropCol( string, string );

void showColumns( Tables );

#endif

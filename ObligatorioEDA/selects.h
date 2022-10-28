#pragma once
#include "variables.h"

void insertRow( Tuples, string );

typeRet selectWhere( string, string, string );

void addNewTableColumns( Tables, Tables &, string );

typeRet select( string, string, string );

void addJoinColumns( Tables, Tables, Tables &, int );

void addJoinTuples( Tables, Tables, Tables &, int );

typeRet join( string, string, string );
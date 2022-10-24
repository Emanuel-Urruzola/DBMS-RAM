#pragma once
#include "variables.h"

void splitCondition(string, string&, string&, string, int);

bool validColumns(string, Tables);

typeRet insertInto(string, string, string);

int whereConditionColumn(Tables, string);

typeRet findColumn(Tables, string);

int findIndexColumn(Tables, string);

typeRet replaceInRow(Tuple, string, string, typeOfData);

typeRet findMatches(Tables, int, string, typeOfData, string, string, int);

typeOfData findTypeColumn(Tables, int);

typeRet update(string, string, string, string);

int columnExists(Tables, string);

int validCondition(Tables, Tuples, int, string, string);

typeRet deleteQuery(string, string);
#pragma once
#include "variables.h"

void releaseTree( TreeStr& tree );
// Check if STRING is "", if so, prints an ERROR string
bool IsEmptyString( string, string );
// Check TABLE the name TABLENAME
bool tableIsNull( Tables, string, bool );
bool insertAndCreate( TreeStr&, string, string, string, string );
// Iterates through TUPLES, gets names and values ​​from each row and
// separates them by ":" and returns them by &NAMES and &VALUES
void getStrings( Tuples tuples, string& names, string& values );

bool insertIntoTableIntersection( Tables, string, TreeStr&, string );
// Delete in a TREE, a node with the following VALUE
TreeStr deleteNodeTree( TreeStr&, string );

bool insertIntoSet( Tables, string, string, TreeStr );

bool createTableUnion( Tables, string );
// Evaluates if TABLE1 and TABLE2 have the same schema
bool checkSchema( Tables, Tables );

int insertSetTreeInTable( TreeStr, string );
// From TABLENAME1 and TABLENAME2 create a table named TABLERESULT. The set is
// of TYPE "union", "intersect" or "minus"
typeRet createSet( string, string, string, string );
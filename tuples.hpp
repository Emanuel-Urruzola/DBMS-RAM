#ifndef tuples
#define tuples
#include "variables.hpp"
#include "tables.hpp"
bool validColumns( string columnsOrder, Tables table ) {
  size_t position;
  int userAttributesCounter = 0;
  //  TODO: Check possible double name in columns
  //  TODO: Validate types and restrictions
  while( ( position = columnsOrder.find( ":" ) ) != string::npos ) {
    userAttributesCounter++;
    int counter               = 0;
    Tuple tableAttributesCopy = table->attributes;
    while( tableAttributesCopy != NULL ) {
      if( columnsOrder.substr( 0, position ) == tableAttributesCopy->name )
        counter++;
      tableAttributesCopy = tableAttributesCopy->next;
    }
    if( counter != 1 ) {
      return false;
    }
    columnsOrder.erase( 0, position + 1 );
  }
  if( userAttributesCounter == table->attributes->index ) return true;
  return false;
}
void InsertInto( string tableName, string columnsOrder, string columnValues ) {
  Tables table = findTable( tablesList, tableName );
  if( table == NULL ) {
    cout << "Doesn't exist";
  } else {
    cout << "Exist";
  }
}
#endif  // !tuples test
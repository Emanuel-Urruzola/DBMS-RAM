#ifndef columns
#define columns
#include "tables.hpp"
#include "variables.hpp"

void AddCol( Tables tablesList, string tableName, string columnName,
             typeOfData columnType, typeOfRestriction restriction ) {
  Tables table = findTable( tablesList, tableName );
  if( table == NULL ) cout << "What table?";
  else {
    Tuple column        = new nodeElement;
    column->name        = columnName;
    column->type        = columnType;
    column->restriction = restriction;
    column->next        = NULL;
    if( table->attributes == NULL ) {
      table->attributes = column;
      column->index     = 0;
    } 
    else {
      Tuple tableAttributesCopy = table->attributes;
      while( tableAttributesCopy->next != NULL ) {
        tableAttributesCopy = tableAttributesCopy->next;
      }
      tableAttributesCopy->next = column;
      tableAttributesCopy->next->index = tableAttributesCopy->index + 1;
    }
  }
}

/** PARTE VIEJA DEL INSFRONT**/
//     if( table->attributes == NULL ) {
//       column->next  = NULL;
//       column->index = 0;
//     } else {
//       column->next  = table->attributes;
//       column->index = column->next->index + 1;  // descendent order
//     }
//     table->attributes = column;
//     cout << "";
//   }
// }

#endif  // !columns
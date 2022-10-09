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
    cout << "";
    if( table->attributes == NULL ) {
      table->attributes = column;
      column->index     = 0;
    } 
    else {
      //TODO: Corregir que al insertar detras no pierda datos anteriores.
      Tables tableCopy = table;
      while( tableCopy->attributes->next != NULL ) {
        // Encuentra el final de la copia de table
        tableCopy->attributes = tableCopy->attributes->next;
      }
      table->attributes->next = column;
      cout << "";
      // column->next  = table->attributes;
      // column->index = column->next->index + 1;  // descendent order
    }
    //table->attributes->next = column;
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
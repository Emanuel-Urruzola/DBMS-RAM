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
    if( table->attributes != NULL ) {
      Tuple tableAttributesCopy = table->attributes;
      bool finded               = false;
      while( tableAttributesCopy->next != NULL && ! finded ) {
        if( tableAttributesCopy->name == columnName ) {
          cout << "No se puede ingresar dos veces la misma columna"
               << endl;  // retornar tipoRet
          finded = true;
        }
        tableAttributesCopy = tableAttributesCopy->next;
      }
      if(!finded){
      tableAttributesCopy->next        = column;
      tableAttributesCopy->next->index = tableAttributesCopy->index + 1;
      }
    }
  }
}

void showColumns( Tables tablesList ) {
  Tables aux = tablesList;
  while( aux->attributes != NULL ) {
    cout << aux->attributes->name << endl;
    aux->attributes = aux->attributes->next;
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
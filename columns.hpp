#ifndef columns
#define columns
#include "variables.hpp"
#include "tables.hpp"

void AddCol(string tableName, string columnName, typeOfData columnType, typeOfRestriction restriction){
  Tables table = findTable(tablesList,tableName);
  if (table == NULL)
    cout << "What table?";
  else
  {
    Tuple column = new nodeElement;
    column->name = columnName;
    column->type = columnType;
    column->restriction = restriction;
    if ( table->attributes == NULL )
    {
      column->next = NULL;
      column->index = 0;
    }else{
      column->next = table->attributes;
      column->index = column->next->index+1; // descendent order
    }
    table->attributes = column;
    cout << "";
  }
}

#endif // !columns
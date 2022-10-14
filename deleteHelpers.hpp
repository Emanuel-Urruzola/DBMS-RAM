#ifndef deleteHeleprs
#define deleteHeleprs
#include "variables.hpp"

void deleteAllRows( Tuple &row ) {
  if( row != NULL ) {
    deleteAllRows( row->next );
    delete row;
    row = NULL;
  }
}

void deleteAllTuples( Tuples &tuple ) {
  if( tuple != NULL ) {
    deleteAllRows( tuple->row );
    deleteAllTuples( tuple->next );
    delete tuple;
    tuple = NULL;
  }
}

void deleteTuple( Tuples &tuple ) {
  deleteAllRows( tuple->row );
  Tuples aux = tuple;
  tuple      = tuple->next;
  delete aux;
}

void deleteNextTuple( Tuples &tuple ) {
  deleteAllRows( tuple->next->row );
  Tuples aux  = tuple->next;
  tuple->next = tuple->next->next;
  delete aux;
}

#endif  // !deleteHeleprs
#ifndef DATA_MANAGER_H_INCLUDED
#define DATA_MANAGER_H_INCLUDED

#include <memory.h>

#include "list.h"
#include "director.h"

typedef struct data_manager_s* data_manager_t;

data_manager_t data_manager_new ();

void data_manager_load (data_manager_t);
void data_manager_save (data_manager_t);

void data_manager_add (data_manager_t, director_t);
director_t data_manager_get (data_manager_t, int);
void data_manager_delete (data_manager_t, int);

char* data_manager_getAsString (data_manager_t, char [], int);

int data_manager_getSize (data_manger_t);

void data_manager_free (data_manager_t);

#endif // DATA_MANAGER_H_INCLUDED

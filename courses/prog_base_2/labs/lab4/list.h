#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdlib.h>

typedef struct list_s* list_t;

typedef enum {
    LIST_OK,
    LIST_INDEX_ERROR,
    LIST_EMPTY_ERROR
} list_Error;

list_t list_new(void);
void list_free(list_t self);
void list_deepDelete(list_t self, void Element_delete(void * element));
void * list_get(list_t self, unsigned int index, list_Error * error);
void * list_set(list_t self, unsigned int index, void * element, list_Error * error);
list_Error list_add(list_t self, unsigned int index, void * element);
void list_append(list_t self, void * element);
void * list_remove(list_t self, unsigned int index, list_Error * error);
size_t list_getSize(list_t self);
const char * list_errorStr(list_Error error);

#endif // LIST_H_INCLUDED

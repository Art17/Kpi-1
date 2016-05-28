#include "list.h"

static const size_t arrayInitialCapacity = 8;

static struct list_s{
    void ** array;
    size_t arrayCapacity;
    size_t size
};

typedef struct list list_s;

list_t list_new(void){
    list_t self = (list_t)malloc(sizeof(struct list_s));
    if(NULL == self){
        puts("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    self->array = (void **)malloc(sizeof(void *) * arrayInitialCapacity);
    if(NULL == self->array){
        puts("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    self->arrayCapacity = arrayInitialCapacity;
    self->size = 0;

    return self;
}

void list_free(list_t self){
    if(NULL == self) return;

    free(self->array);
    free(self);
}

void list_deepDelete(list_t self, void Element_delete(void * element)){
    if(NULL == self) return;

    for(int i = 0; i < self->size; i++){
        Element_delete(self->array[i]);
    }
    free(self->array);
    free(self);
}

void * list_get(list_t self, unsigned int index, list_Error * error){
    if(index >= self->size){
        if(error != NULL) *error = LIST_INDEX_ERROR;
        return NULL;
    }

    if(error != NULL) *error = LIST_OK;
    return self->array[index];
}

void * list_set(list_t self, unsigned int index, void * element, list_Error * error){
    if(index >= self->size){
        if(error != NULL) *error = LIST_INDEX_ERROR;
        return NULL;
    }

    void * old = self->array[index];
    self->array[index] = element;

    if(error != NULL) *error = LIST_OK;
    return old;
}

list_Error list_add(list_t self, unsigned int index, void * element){
    if(index > self->size){
        return LIST_INDEX_ERROR;
    }

    if(self->arrayCapacity == self->size){
        void ** oldArray = self->array;
        self->arrayCapacity *= 2;
        self->array = (void **)malloc(sizeof(void *) * self->arrayCapacity);
        if(NULL == self->array){
            puts("Error allocating memory");
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < index; i++){
            self->array[i] = oldArray[i];
        }
        self->array[index] = element;
        for(int i = index; i < self->size; i++){
            self->array[i + 1] = oldArray[i];
        }

        free(oldArray);
    }else{
        for(int i = self->size; i > index; i--){
            self->array[i] = self->array[i - 1];
        }
        self->array[index] = element;
    }

    self->size++;

    return LIST_OK;
}

void list_append(list_t self, void * element){
    list_add(self, self->size, element);
}

void * list_remove(list_t self, unsigned int index, list_Error * error){
    if(self->size == 0){
        if(error != NULL) *error = LIST_EMPTY_ERROR;
        return NULL;
    }

    if(index >= self->size){
        if(error != NULL) *error = LIST_INDEX_ERROR;
        return NULL;
    }

    void * removedEl = self->array[index];
    for(int i = index; i < self->size - 1; i++){
        self->array[i] = self->array[i + 1];
    }

    self->size--;

    if(error != NULL) *error = LIST_OK;
    return removedEl;
}

size_t list_getSize(list_t self){
    return self->size;
}

const char * list_errorStr(list_Error error){
    static const char * repr[] = {
        "OK",
        "Index error",
        "Empty list error"
    };
    return repr[error];
}

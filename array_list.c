#include "list.h"
#include <stdlib.h>

// Пользовательская структура, которая скрывает механизм хранения данных.
struct List {
  int* array; // динамический массив, в котором будут раниться все данные
  int length; // размер списка: последний занятый индекс в array
  int capacity; // ёмкость списка: реальный размер массива array
  int size; //количество элементов в списке
};

void MacroMemory(List* this) {
    this->capacity*=2;
    int* arr=calloc(sizeof(int), this->capacity);
    for (int i=0; i<this->size; i++) {
        arr[i]=this->array[i];
    }
    free(this->array);
    this->array=arr;
}

void MicroMemory(List* this) {
    this->capacity/=2;
    int* arr=calloc(sizeof(int), this->capacity);
    for (int i=0; i<this->size+1; i++) {
        arr[i]=this->array[i];
    }
    free(this->array);
    this->array=arr;
}

List *NewList() {
    List* list=(List*) malloc(sizeof(List));
    list->length=-1;
    list->capacity=0;
    list->size=0;
    return list;
}

void DestroyList(List* this) {
    this->length=-1;
    this->capacity=0;
    this->size=0;
    free(this);
}

void Append(List *this, int value) {
    this->size++;
    this->length++;
    if (this->capacity==0) {
        this->capacity=2;
        this->array=calloc(sizeof(int), this->capacity);
        this->array[0]=value;
        return;
    }
    if (this->size==this->capacity) {
        MacroMemory(this);
    }
    this->array[this->length]=value;
}
void Prepend(List *this, int value) {
    this->size++;
    this->length++;
    if (this->capacity==0) {
        this->capacity=2;
        this->array=calloc(sizeof(int), this->capacity);
        this->array[0]=value;
        return;
    }
    if (this->size==this->capacity) {
        MacroMemory(this);
    }
    for (int i=this->length; i>0; i--) {
        this->array[i]=this->array[i-1];
    }
    this->array[0]=value;
}
void AppendAll(List *this, const List *that) {
    int tmp=this->size;
    this->size+=that->size;
    this->capacity+=that->capacity;
    this->length=this->length+that->length+1;
    int* arr=calloc(sizeof(int), this->capacity);
    for (int i=0; i<tmp; i++) {
        arr[i]=this->array[i];
    }
    for (int i=tmp, j=0; j<that->size; i++, j++) {
        arr[i]=that->array[j];
    }
    free(this->array);
    this->array=arr;
}
void InsertAt(List *this, int index, int value) {
    this->size++;
    this->length++;
    if (this->capacity==0) {
        this->capacity=2;
        this->array=calloc(sizeof(int), this->capacity);
        this->array[0]=value;
        return;
    }
    if (this->size==this->capacity) {
        MacroMemory(this);
    }
    for (int i=this->length; i>index+1; i--) {
        this->array[i]=this->array[i-1];
    }
    this->array[index+1]=value;
}

void RemoveAt(List *this, int index) {
    if (this->size==0) {
        exit(-1);
    }
    if (this->capacity==0) {
        return;
    }
    this->size--;
    this->length--;
    if (this->capacity/this->size==4) {
        MicroMemory(this);
    }
    for (int i=index; i<=this->length; i++) {
        this->array[i]=this->array[i+1];
    }
}

void RemoveAll(List *this) {
    this->length=-1;
    this->size=0;
    this->capacity=2;
    free(this->array);
    this->array=calloc(sizeof(int), this->capacity);
}

int Pop(List *this) {
    if (this->size==0) {
        exit(-1);
    }
    this->size--;
    this->length--;
    if (this->capacity/this->size==4) {
        MicroMemory(this);
    }
    return this->array[this->length+1];
}
int Dequeue(List *this) {
    if (this->size==0) {
        exit(-1);
    }
    this->size--;
    this->length--;
    int a=this->array[0];
    if (this->capacity/this->size==4) {
        MicroMemory(this);
    }
    for (int i=0; i<this->length+1; i++) {
        this->array[i]=this->array[i+1];
    }
    return a;
}

int Length(const List *this) {
    return this->size;
}
int GetAt(const List *this, int index) {
    if (this->size==0) {
        exit(-1);
    }
    return this->array[index];
}

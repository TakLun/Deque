#ifndef DEQUE_ORIG_HPP__
#define DEQUE_ORIG_HPP__

#include <string.h>
#include <stdio.h>

struct Deque_int_Iterator{
  //##t
  int *iterator;

  void inc(Deque_int_Iterator *deq_it){
    deq_it->iterator++;
  }

  void dec(Deque_int_Iterator *deq_it){
    deq_it->iterator--;
  }

  //##t
  int deref(Deque_int_Iterator *deq_it){
    return *(deq_it->iterator);
  }
};

struct Deque_int{
  size_t length;
  size_t capacity;
  int *data;
  char type_name[sizeof("Deque_int")];

  size_t size(Deque_int *deq){
    return deq->length;
  }
  
  bool empty(Deque_int *deq){
    return size(deq) == 0;
  }

  bool (*compare)(const int &o1, const int &o2);

  int (*push_back)(Deque_int *, int);
  int (*push_front)(Deque_int *, int);
  int (*pop_back)(Deque_int *);
  int (*pop_front)(Deque_int *);

  //##t
  int (*back)(Deque_int *);
  int (*front)(Deque_int *);
  int (*at)(Deque_int *, int);
  Deque_int_Iterator (*begin)(Deque_int *);
  Deque_int_Iterator (*end)(Deque_int *);

  void (*clear)(Deque_int *);
  void (*dtor)(Deque_int *);  
}; 

int int_push_back(Deque_int *deq, int i){
  if(deq->length >= deq->capacity){

    deq->capacity = deq->capacity * 2;

    if(deq->capacity <= 0){
      deq->capacity = 1;
    }

    int *newDeque = (int *)realloc(deq->data, sizeof(deq->data) * deq->capacity);
    if(!newDeque){
      free(newDeque);
      return -1;
    }else{
      deq->data = newDeque;
    }
  }
  deq->data[deq->length] = i;
  deq->length++;
}

int int_push_front(Deque_int *deq, int i){
  if(deq->length >= deq->capacity){

    deq->capacity = deq->capacity * 2;

    if(deq->capacity == 0){
      deq->capacity = 1;
      return -1;
    }

    int *newDeque = (int *)realloc(deq->data, sizeof(deq->data) * deq->capacity);
    if(!newDeque){
      free(newDeque);
    }else{
      deq->data = newDeque;
    }
  }
  memmove(&(deq->data[1]), &(deq->data[0]), sizeof(int) * deq->length);
  deq->data[0] = i;
  deq->length++;
}

int int_pop_back(Deque_int *deq){
  memset(&(deq->data[deq->length]), 0, sizeof(deq->data[deq->length]));
  deq->length--;
  return 0;
}

int int_pop_front(Deque_int *deq){
  deq->length--;
  memmove(&(deq->data[0]), &(deq->data[1]), sizeof(deq->data[0]) * deq->length);
  return 0;
}

//##t
int int_back(Deque_int *deq){
  return deq->data[(deq->length)-1];
}

//##t
int int_front(Deque_int *deq){
  return deq->data[0];
}

//##t
int int_at(Deque_int *deq, int i){
  return deq->data[i];
}

//##t
Deque_int_Iterator int_begin(Deque_int *deq){
  Deque_int_Iterator it;
  it.iterator = deq->data;
  
  return it;
}

//##t
Deque_int_Iterator int_end(Deque_int *deq){
  Deque_int_Iterator it;
  it.iterator = &deq->data[deq->length];
  return it;
}

void int_clear(Deque_int *deq){
  memset(&(deq->data[0]), 0, deq->length * sizeof(deq->data[0]));
  deq->length = 0;
}

void int_dtor(Deque_int *deq){
  free(deq->data);
}

void Deque_int_ctor(Deque_int *deq, bool(*cmp)(const int &o1, const int &o2)){
  Deque_int *temp_deq = (Deque_int *)malloc(sizeof(Deque_int));
  
  temp_deq->length = 0;
  temp_deq->capacity = 0;
  temp_deq->data = (int *)malloc(sizeof(*(deq->data)) * temp_deq->capacity);
  strncpy(temp_deq->type_name, "Deque_int", sizeof("Deque_int"));

  temp_deq->compare = cmp;
  temp_deq->push_back = int_push_back;
  temp_deq->push_front = &int_push_front;
  temp_deq->pop_back = &int_pop_back;
  temp_deq->pop_front = &int_pop_front;
  temp_deq->back = &int_back;
  temp_deq->front = &int_front;
  temp_deq->at = &int_at;
  temp_deq->begin = &int_begin;
  temp_deq->end = &int_end;
  temp_deq->clear = &int_clear;
  temp_deq->dtor = &int_dtor;

  *deq = *temp_deq;
  free(temp_deq);
}

bool Deque_int_equal(Deque_int deq, Deque_int deq2){
  if(deq.size(&deq) == deq2.size(&deq2)){
    bool isEqual = true;
    for(unsigned int pos = 0; pos < deq.size(&deq); pos++){
       if(deq1.less(deq1.data[pos], deq2.data[pos]) == true ||
	 deq1.less(deq2.data[pos], deq1.data[pos]) == true){
	isEqual = false;
	break;
      }
    }
    return isEqual;
  }else{
    return 0;
  }
}

bool Deque_int_Iterator_equal(Deque_int_Iterator it, Deque_int_Iterator it2){
  return (it.iterator == it2.iterator);
}

#endif

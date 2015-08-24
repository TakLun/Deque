#ifndef DEQUE_HPP__
#define DEQUE_HPP__

#include <string.h>
#include <stdio.h>

#define Deque_DEFINE(t)                                                                   \
struct Deque_##t##_Iterator{                                                              \
  t *iterator;                                                                            \
  void inc(Deque_##t##_Iterator *deq_it){                                                 \
    deq_it->iterator++;                                                                   \
  }                                                                                       \
  void dec(Deque_##t##_Iterator *deq_it){                                                 \
    deq_it->iterator--;                                                                   \
  }                                                                                       \
  t &deref(Deque_##t##_Iterator *deq_it){                                                 \
    return *(deq_it->iterator);                                                           \
  }                                                                                       \
};                                                                                        \
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it, Deque_##t##_Iterator it2){       \
  return (it.iterator == it2.iterator);                                                   \
}                                                                                         \
struct Deque_##t{                                                                         \
  size_t length;                                                                          \
  size_t capacity;                                                                        \
  t *data;                                                                                \
  char type_name[sizeof("Deque_" #t)];                                                    \
  size_t size(Deque_##t *deq){                                                            \
    return deq->length;                                                                   \
  }                                                                                       \
  bool empty(Deque_##t *deq){                                                             \
    return size(deq) == 0;                                                                \
  }                                                                                       \
  bool (*less)(const t &o1, const t &o2);                                                 \
  int (*push_back)(Deque_##t *, t);                                                       \
  int (*push_front)(Deque_##t *, t);                                                      \
  int (*pop_back)(Deque_##t *);                                                           \
  int (*pop_front)(Deque_##t *);                                                          \
  t &(*back)(Deque_##t *);                                                                \
  t &(*front)(Deque_##t *);                                                               \
  t &(*at)(Deque_##t *, int);                                                             \
  Deque_##t##_Iterator (*begin)(Deque_##t *);                                             \
  Deque_##t##_Iterator (*end)(Deque_##t *);                                               \
  void (*clear)(Deque_##t *);                                                             \
  void (*dtor)(Deque_##t *);                                                              \
};                                                                                        \
int t##_push_back(Deque_##t *deq, t dat){                                                 \
  if(deq->length >= deq->capacity){                                                       \
    deq->capacity = deq->capacity * 2;                                                    \
    if(deq->capacity <= 0){                                                               \
      deq->capacity = 1;                                                                  \
    }                                                                                     \
    t *newDeque = (t *)realloc(deq->data, sizeof(t) * deq->capacity);                     \
    if(!newDeque){                                                                        \
      free(newDeque);                                                                     \
      return -1;                                                                          \
    }else{                                                                                \
      deq->data = newDeque;                                                               \
    }                                                                                     \
  }                                                                                       \
  deq->data[deq->length] = dat;                                                           \
  deq->length++;                                                                          \
  return 0;                                                                               \
}                                                                                         \
int t##_push_front(Deque_##t *deq, t dat){                                                \
  if(deq->length >= deq->capacity){                                                       \
    deq->capacity = deq->capacity * 2;                                                    \
    if(deq->capacity == 0){                                                               \
      deq->capacity = 1;                                                                  \
      return -1;                                                                          \
    }                                                                                     \
    t *newDeque = (t *)realloc(deq->data, sizeof(t) * deq->capacity);                     \
    if(!newDeque){                                                                        \
      free(newDeque);                                                                     \
      return -1;                                                                          \
    }else{                                                                                \
      deq->data = newDeque;                                                               \
    }                                                                                     \
  }                                                                                       \
  memmove(&(deq->data[1]), &(deq->data[0]), sizeof(deq->data[0]) * deq->length);          \
  deq->data[0] = dat;                                                                     \
  deq->length++;                                                                          \
  return 0;                                                                               \
}                                                                                         \
int t##_pop_back(Deque_##t *deq){                                                         \
  deq->length--;                                                                          \
  memset(&(deq->data[deq->length]), 0, sizeof(deq->data[0]));                             \
  return 0;                                                                               \
}                                                                                         \
int t##_pop_front(Deque_##t *deq){                                                        \
  deq->length--;                                                                          \
  memmove(&(deq->data[0]), &(deq->data[1]), sizeof(deq->data[0]) * deq->length);          \
  return 0;                                                                               \
}                                                                                         \
t &t##_back(Deque_##t *deq){                                                              \
  return deq->data[(deq->length)-1];                                                      \
}                                                                                         \
t &t##_front(Deque_##t *deq){                                                             \
  return deq->data[0];                                                                    \
}                                                                                         \
t &t##_at(Deque_##t *deq, int i){                                                         \
  return deq->data[i%(deq->size(deq))];					                  \
}                                                                                         \
Deque_##t##_Iterator t##_begin(Deque_##t *deq){                                           \
  Deque_##t##_Iterator it;                                                                \
  it.iterator = deq->data;                                                                \
                                                                                          \
  return it;                                                                              \
}                                                                                         \
Deque_##t##_Iterator t##_end(Deque_##t *deq){                                             \
  Deque_##t##_Iterator it;                                                                \
  it.iterator = &deq->data[deq->length];                                                  \
  return it;                                                                              \
}                                                                                         \
void t##_clear(Deque_##t *deq){                                                           \
  memset(deq->data, 0, deq->length * sizeof(deq->data[0]));                               \
  deq->length = 0;                                                                        \
}                                                                                         \
void t##_dtor(Deque_##t *deq){                                                            \
  free(deq->data);                                                                        \
}                                                                                         \
void Deque_##t##_ctor(Deque_##t *deq, bool(*cmp)(const t &o1, const t &o2)){              \
  Deque_##t *temp_deq = (Deque_##t *)malloc(sizeof(Deque_##t));                           \
  temp_deq->length = 0;                                                                   \
  temp_deq->capacity = 0;                                                                 \
  temp_deq->data = (t *)malloc(sizeof(*(deq->data)) * temp_deq->capacity);                \
  strncpy(temp_deq->type_name, "Deque_" #t, sizeof("Deque_" #t));                         \
  temp_deq->less = cmp;                                                                   \
  temp_deq->push_back = t##_push_back;                                                    \
  temp_deq->push_front = &t##_push_front;                                                 \
  temp_deq->pop_back = &t##_pop_back;                                                     \
  temp_deq->pop_front = &t##_pop_front;                                                   \
  temp_deq->back = &t##_back;                                                             \
  temp_deq->front = &t##_front;                                                           \
  temp_deq->at = &t##_at;                                                                 \
  temp_deq->begin = &t##_begin;                                                           \
  temp_deq->end = &t##_end;                                                               \
  temp_deq->clear = &t##_clear;                                                           \
  temp_deq->dtor = &t##_dtor;                                                             \
  *deq = *temp_deq;                                                                       \
  free(temp_deq);                                                                         \
}                                                                                         \
bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2){                                   \
  if(deq1.size(&deq1) == deq2.size(&deq2)){                                               \
    bool isEqual = true;                                                                  \
    for(unsigned int pos = 0; pos < deq1.size(&deq1); pos++){			          \
      if(deq1.less(deq1.data[pos], deq2.data[pos]) == true ||		                  \
	 deq1.less(deq2.data[pos], deq1.data[pos]) == true){			          \
        isEqual = false;                                                                  \
        break;                                                                            \
      }                                                                                   \
    }                                                                                     \
    return isEqual;                                                                       \
  }else{                                                                                  \
    return 0;                                                                             \
  }                                                                                       \
}

#endif

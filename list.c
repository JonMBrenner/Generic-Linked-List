#include "list.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Node {
  void* data;
  struct Node* next;
};

struct List {
  struct Node* head;
  struct Node* tail;
  Display display;
  Copy copy;
  Free free;
};

struct Node* new_node(void* elem) {
  struct Node* node = malloc(sizeof *node);
  node->data = elem;
  node->next = NULL;
  return node;
}

struct List* new_list(Display display_elem, Copy copy_elem, Free free_elem) {
  struct List* list = malloc(sizeof *list);
  list->head = NULL;
  list->tail = NULL;
  list->display = display_elem;
  list->copy = copy_elem;
  list->free = free_elem;
  return list;
}

struct List* copy_list(struct List* self) {
  struct List* self_copy = new_list(self->display, self->copy, self->free);
  struct Node* cur_self = self->head;
  self_copy->head = new_node(self->copy(cur_self->data));
  struct Node* cur_copy = self_copy->head;
  while (cur_self != self->tail) {
    cur_self = cur_self->next;
    cur_copy->next = new_node(self->copy(cur_self->data));
    cur_copy = cur_copy->next;
  }
  self_copy->tail = cur_copy;
  return self_copy;
}

void free_list(struct List* self) {
  struct Node* cur = self->head;
  struct Node* next;
  while (cur) {
    next = cur->next;
    self->free(cur->data);
    free(cur);
    cur = next;
  }
  free(self);
}

void display_list(struct List* self) {
  struct Node* cur = self->head;
  if (!cur) {
    puts("[]");
    return;
  }
  printf("[");
  while (cur->next) {
    self->display(cur->data);
    printf(", ");
    cur = cur->next;
  }
  self->display(cur->data);
  puts("]");
}

void append_front(struct List* self, void* elem) {
  struct Node* elem_node = new_node(elem);
  if (!self->head) {
    self->head = elem_node;
    self->tail = elem_node;
  } else {
    elem_node->next = self->head;
    self->head = elem_node;
  }
}

void append_back(struct List* self, void* elem) {
  struct Node* elem_node = new_node(elem);
  if (!self->head) {
    self->head = elem_node;
    self->tail = elem_node;
  } else {
    self->tail->next = elem_node;
    self->tail = elem_node;
  }
}

void remove_at(struct List* self, int index) {
  struct Node* cur = self->head;
  if (!index) {
    self->head = cur->next;
  } else {
    for (int i = 0; i < index-1; ++i) {
      cur = cur->next;
    }
    struct Node* prev = cur;
    cur = cur->next;
    prev->next = cur->next;
  }
  self->free(cur->data);
  free(cur);
}


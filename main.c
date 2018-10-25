#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void free_int(void* vp) {
  free(vp);
}

static void* copy_int(const void* vp) {
  const int* ip = vp;
  int* ret = malloc(sizeof *ret);
  *ret = *ip;
  return ret;
}

static void display_int(const void* vp) {
  const int* ip = vp;
  printf("%d", *ip);
}

static int* make_int(int val) {
  int* ret = malloc(sizeof *ret);
  *ret = val;
  return ret;
}

// usage example with int:
static void int_list_example() {
  struct List* list = new_list(display_int, copy_int, free_int);
  for (int i = 5; i < 20; i += 2) {
    append_front(list, make_int(i)); // reverse order, appending to front
  }
  struct List* list2 = copy_list(list);
  append_back(list2, make_int(100));
  display_list(list);
  display_list(list2);

  free_list(list2);
  free_list(list);
}

struct Person {
  char* name;
  int age;
};

static void* make_person(const char* name, int age) {
  struct Person* p = malloc(sizeof *p);
  p->name = malloc(strlen(name) + 1);
  strcpy(p->name, name);
  p->age = age;
  return p;
}

static void display_person(const void* vp) {
  const struct Person* p = vp;
  printf("{%s, %d}", p->name, p->age);
}

static void* copy_person(const void* vp) {
  const struct Person* src = vp;
  return make_person(src->name, src->age);
}

static void free_person(void* vp) {
  struct Person* p = vp;
  free(p->name);
  free(p);
}

static void person_list_example() {
  struct List* list = new_list(display_person, copy_person, free_person);

  append_back(list, make_person("Jane", 30));
  append_back(list, make_person("Charles", 25));
  append_back(list, make_person("James", 19));
  append_back(list, make_person("Anne", 40));

  display_list(list);

  struct List* list2 = copy_list(list);
  append_front(list2, make_person("Bob", 50));

  display_list(list2);
  remove_at(list2, 1); // remove Jane (middle)
  display_list(list2);
  remove_at(list2, 0); // remove Bob (front)
  display_list(list2);
  remove_at(list2, 2); // remove Anne (back)
  display_list(list2);



  display_list(list); // display first list to make sure it's fine


  free_list(list2);
  free_list(list);
}

int main(void) {
  int_list_example();
  person_list_example();

}

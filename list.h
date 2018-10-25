#ifndef LIST_H_
#define LIST_H_

struct List;

typedef void (*Display)(const void*);
typedef void* (*Copy)(const void*);
typedef void (*Free)(void*);

struct List* new_list(Display display_elem, Copy copy_elem, Free free_elem);
struct List* copy_list(struct List* self);
void free_list(struct List* self);

void display_list(struct List* self);

void append_front(struct List* self, void* elem);
void append_back(struct List* self, void* elem);
void remove_at(struct List* self, int index);

#endif

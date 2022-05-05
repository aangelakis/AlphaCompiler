#ifndef VEKTOR_HEADER
#define VEKTOR_HEADER

#define VEKTOR_SIZE 1024

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>


typedef struct Vektor{
	int max_size;
	int cur_size;
	void **data;
} Vektor;

/* Initializes the vektor*/
Vektor* vektor_initialize();

/* Adds element inside the vektor*/
void vektor_add(Vektor *vektor, void *data);

/* Adds element at index inside the vektor*/
void vektor_set_element(Vektor *vektor, int index, void *data);

/* Pops element from inside the vektor given the index of the array*/
void* vektor_pop_element_at_index(Vektor *vektor, int index);

/* Deletes the vektor*/
void vektor_delete(Vektor *vektor);

/* Free the vektor contents	but not the vektor itself*/
void vektor_free_contents(Vektor *vektor);

/* Returns the active size of the vektor (how many cells are occupied)*/
int vektor_active_size(Vektor *vektor);

/* Clears vektor from it's content, it doesnt free the contents just removes them*/
void vektor_clear(Vektor *vektor);

/* Searches for a data inside the vektor returns index if found -1 else*/
int vektor_search(Vektor *vektor, void *data);

/* Returns the data at the index*/
void* vektor_get_element(Vektor *vektor, int index);

/* Expands the vektor */
void vektor_expand(Vektor *vektor, int size);

/* Applys function 'apply(void*)' to the content of each zarkNode of the zarkList */
void vektor_apply(Vektor *vektor, void (*apply)(void*));

#endif
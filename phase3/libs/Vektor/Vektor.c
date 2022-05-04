#include "Vektor.h"

Vektor* vektor_initialize(){
	Vektor* v = malloc(sizeof(Vektor));
	v->max_size = VEKTOR_SIZE;
	v->cur_size = 0;
	v->data = malloc(sizeof(void*) * v->max_size);
	return v;
}

void vektor_expand(Vektor* v){
	if(v->cur_size == v->max_size){
		v->max_size *= VEKTOR_SIZE_GROWTH;
		v->data = realloc(v->data, sizeof(void*) * v->max_size);
	}
}

void vektor_add(Vektor* v, void* data){
	vektor_expand(v);
	for (int i = 0; i < v->cur_size; i++)
	{
		if (v->data[i]==NULL)
		{
			v->data[i]=data;
			return;
		}
		
	}
	
	v->data[v->cur_size] = data;
	v->cur_size++;
}

void* vektor_pop_element_at_index(Vektor* v, int index){
	void* data = v->data[index];
	v->data[index] = NULL;
	return data;
}

void vektor_delete(Vektor* v){
	free(v->data);
	free(v);
}

void vektor_free_contents(Vektor* v){
	for (int i = 0; i < v->cur_size; i++)
	{
		if (v->data[i] != NULL)
		{
			free(v->data[i]);
		}
	}
	v->cur_size = 0;
}

int vektor_active_size(Vektor* v){
	int tmp = 0;
	for (int i = 0; i < v->cur_size; i++)
	{
		if (v->data[i] != NULL)
		{
			tmp++;
		}
	}
	return tmp;
}

void vektor_clear(Vektor* v){
	for (int i = 0; i < v->cur_size; i++)
	{
		v->data[i] = NULL;
	}
	v->cur_size = 0;
}

int vektor_search(Vektor* v, void* data){
	for (int i = 0; i < v->cur_size; i++)
	{
		if (v->data[i] == data)
		{
			return i;
		}
	}
	return -1;
}

void* vektor_get_element(Vektor *vektor, int index){
	if (index < vektor->cur_size)
	{
		return vektor->data[index];
	}
	return NULL;
}
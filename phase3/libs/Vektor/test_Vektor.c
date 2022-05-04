#include "Vektor.h"

int main(){
  Vektor* v = vektor_initialize();
  printf("active size is : %d\n", vektor_active_size(v));
  printf("max_size is : %d\n\n", v->max_size);
  printf("entering 6 elements\n\n");
  for (int i = 0; i < 6; i++)
  {
    vektor_add(v, i-1);
  }
  
  
  
  printf("active size is : %d\n", vektor_active_size(v));
  printf("max_size is : %d\n\n", v->max_size);

  printf("popping one element at index 0\n");
  vektor_pop_element_at_index(v, 0);
  printf("active size is : %d\n", vektor_active_size(v));
  printf("max_size is : %d\n\n", v->max_size);

  printf("printing elements\n\n");
  
  for (int i = 0; i < v->cur_size; i++)
  {
    if (vektor_get_element(v, i) == NULL)
    {
      printf("NULL at index %d\n", i);
      continue;
    }
    
    printf("%d\n",(int)vektor_get_element(v, i));
  }
  

  printf("\nadding one more element that will go at the null spot in 0 index \n\n");

  vektor_add(v, 100);

  printf("printing elements\n\n");
  for (int i = 0; i < v->cur_size; i++)
  {
    if (vektor_get_element(v, i) == NULL)
    {
      printf("NULL at index %d\n", i);
      continue;
    }
    
    printf("%d\n",(int)vektor_get_element(v, i));
  }

  printf("Clearing the vector\n\n");
  vektor_clear(v);
  printf("current size %d\n", v->cur_size);
  
  
  vektor_delete(v);

  return 0;
}
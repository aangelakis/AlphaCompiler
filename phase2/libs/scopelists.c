#include"scopelists.h"


/*hides the elements of the given scope */
void soft_hide(scopeArray* array, int scope){
  if (array->size<scope+1)
  {
    printf("ERROR scope given to hide is bigger than the maximum of the given scopeArray\n");
    return;
  }
  zarkNode* itter = array->scopes[scope].head;

  while (itter != NULL)
  {
    ((SymTableEntry*)itter->content)->isActive = 0;
    itter = itter->next;
  }
}

/*hides the elements of the given scope and removes the list from the scope list*/
void hard_hide(scopeArray* array, int scope){
  if (array->size<scope+1)
  {
    printf("ERROR scope given to hide is bigger than the maximum of the given scopeArray\n");
    return;
  }
  zarkNode* head = array->scopes[scope].head;

  while (head != NULL)
  {
    ((SymTableEntry*)itter->content)->isActive = 0;
    head = head->next;
  }
  array->scopes[scope].head = NULL;
  array->scopes[scope].tail = NULL;
  array->scopes[scope].size = 0;
  array->scopes[scope].isContentFreeable = 0;
}

/*unhides every element of the given scope*/
void unhide(scopeArray* array, int scope){
  if (array->size<scope+1)
  {
    printf("ERROR scope given to hide is bigger than the maximum of the given scopeArray\n");
    return;
  }
  zarkNode* head = array->scopes[scope].head;

  while (head != NULL)
  {
    ((SymTableEntry*)itter->content)->isActive = 1;
    head = head->next;
  }
}

/*initializes the scope array to hold 5 scopelists*/
scopeArray scope_initialize()
{
    scopeArray* new_arr = malloc(sizeof(scopeArray));
    new_arr->scopes = malloc(5 * sizeof(scopelist));
    new_arr->size = 5;
    
    for (int i = 0; i < 5; i++){
        new_arr->scopes[i] = zarklist_initialize(1);
    }
}

/*expands the scope array to hold 5 more scopelists*/
scopeArray* expand_scopeArr(scopeArray* array);

/*frees the given scopeArray*/
void free_scopeArr(scopeArray* array);










#include"scopelists.h"

/*hides the elements of the given scope */
void soft_hide(scopeArray* array, int scope){
	array = checkScopeSize(array, scope);
	zarkNode* itter = array->scopes[scope]->head;
	while (itter != NULL)
	{
		((SymTableEntry*)itter->content)->isActive = 0;
		itter = itter->next;
	}
}

/*hides the elements of the given scope and removes the list from the scope list*/
void hard_hide(scopeArray* array, int scope){
	array = checkScopeSize(array, scope);

	zarkNode* itter = array->scopes[scope]->head;

	while (itter != NULL)
	{
	((SymTableEntry*)itter->content)->isActive = 0;
	itter = itter->next;
	}
	zarklist_free_all_nodes(array->scopes[scope]);
	array->scopes[scope]->head = NULL;
	array->scopes[scope]->tail = NULL;
	array->scopes[scope]->size = 0;
	array->scopes[scope]->isContentFreeable = 0;
}

/*unhides every element of the given scope*/
void unhide(scopeArray* array, int scope){
	array = checkScopeSize(array, scope);

	zarkNode* itter = array->scopes[scope]->head;

	while (itter != NULL)
	{
		((SymTableEntry*)itter->content)->isActive = 1;
		itter = itter->next;
	}
}

/*initializes the scope array to hold 5 scopelists*/
scopeArray scope_initialize()
{
    scopeArray* new_arr = malloc(sizeof(scopeArray));
    new_arr->scopes = malloc(5 * sizeof(scopelist*));
    new_arr->size = 5;
    
    for (int i = 0; i < 5; i++){
        new_arr->scopes[i] = zarklist_initialize(0);
    }
}

/*expands the scope array to hold 5 more scopelists*/
scopeArray* expand_scopeArr(scopeArray* array){
	//determining new size
	int new_size = array->size + 5;
	//alocating memory for the new array
	scopeArray* new_array = malloc(sizeof(scopeArray));
	//giving it its new size
	new_array->size = new_size;
	//allocating memory for the array of scope lists
	new_array->scopes = malloc(new_array->size*(sizeof(scopelist*)));

	//copying the first array->size elements
	for (int i = 0; i < array->size; i++)
	{
        new_array->scopes[i] = array->scopes[i];
	}

	//initializing the rest of them
	for (int i = array->size; i < new_array->size; i++)
	{
        new_array->scopes[i] = zarklist_initialize(0);
	}
	//free the old array and the allocated memory of the array that holds the lists
	free(array->scopes);
	free(array);
    array = NULL;
	//return the new array
	return new_array;
};

/*frees the given scopeArray*/
void free_scopeArr(scopeArray* array){
    for(int i = 0; i < array->size; i++){
        zarklist_free(array->scopes[i]);
    }
    free(array->scopes);
    free(array);
}

/*puts in the scopeArray at the end of the scope list the entry*/
void insert_to_scopeArr(scopeArray* array, int scope, SymTableEntry* entry){
	array = checkScopeSize(array,scope);
	zarklist_insert(array->scopes[scope],(SymTableEntry*)entry);
}

/*checks if the given scope can exist in the given array, returns a new array if needed*/
scopeArray* checkScopeSize(scopeArray* array, int scope){
	if (array->size<scope+1)
	{
        //printf("ERROR scope given to hide is bigger than the maximum of the given scopeArray\n");
        return expand_scopeArr(array);
	}
	return array;
}

/*returns a pointer to a symtable entry if found otherwise null*/
SymTableEntry* lookup_with_scope (scopeArray* array, int scope,  char* c){
	array = checkScopeSize(array, scope);
	zarkNode* itter = array->scopes[scope]->head;
	
	//while loop
	while (itter!=NULL)
	{
		//if it is active
		if(Look_up_node->isActive==1){
			//if it is a libfunc or a userfunction
			if ((Look_up_node->type==USERFUNC) || (Look_up_node->type==LIBFUNC))
			{
				//if it is what we are looking for
				if (strcmp(Look_up_node->value.funcVal->name,c)==0)
				{
					return Look_up_node;
				}
			//else if it is a variable
			}else{
				//if it is what we are looking for
				if (strcmp(Look_up_node->value.varVal->name,c)==0)
				{
					return Look_up_node;
				}
			}
			
		}
		
		//go to next zarkNode
		itter = itter->next;
	}
	//if we reached here nothing was found
	return NULL;
}
#include"scopelists.h"

/*hides the elements of the given scope */
void soft_hide(scopeArray** array, int scope)
{
	*array = checkScopeSize(*array, scope);
	zarkNode* iter = (*array)->scopes[scope]->head;

	while (iter != NULL)
	{
		getNodeContent->isActive = 0;
		iter = iter->next;
	}
}

/*hides the elements of the given scope and removes the list from the scope list*/
void hard_hide(scopeArray** array, int scope)
{
	*array = checkScopeSize(*array, scope);
	zarkNode* iter = (*array)->scopes[scope]->head;

	while (iter != NULL)
	{
		getNodeContent->isActive = 0;
		iter = iter->next;
	}
	zarklist_delete_all_nodes((*array)->scopes[scope]);
}

/*unhides every element of the given scope*/
void unhide(scopeArray** array, int scope)
{
	*array = checkScopeSize(*array, scope);

	zarkNode* iter = (*array)->scopes[scope]->head;

	while (iter != NULL)
	{
		getNodeContent->isActive = 1;
		iter = iter->next;
	}
}

/*initializes the scope array to hold 5 scopelists*/
scopeArray* scope_initialize()
{
    scopeArray* new_arr = malloc(sizeof(scopeArray));
    new_arr->scopes = malloc(5 * sizeof(scopelist*));
    new_arr->size = 5;
    
    for (int i = 0; i < 5; i++){
        new_arr->scopes[i] = zarklist_initialize(0);
    }
		return new_arr;
}

/*expands the scope array to hold 5 more scopelists*/
scopeArray* expand_scopeArr(scopeArray* array)
{
	//determining new size
	int new_size = array->size + 5;
	//alocating memory for the new array
	scopeArray* new_array = malloc(sizeof(scopeArray));
	//giving it its new size
	new_array->size = new_size;
	//allocating memory for the array of scope lists
	new_array->scopes = malloc(new_size*(sizeof(scopelist*)));

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
void free_scopeArr(scopeArray* array)
{
    for(int i = 0; i < array->size; i++){
        zarklist_free(array->scopes[i]);
    }
    free(array->scopes);
    free(array);
}

/*puts in the scopeArray at the end of the scope list the entry*/
void insert_to_scopeArr(scopeArray** array, int scope, SymTableEntry* entry)
{
	//to save into the global scp that we will print at the end
	globalScopeArr = checkScopeSize(globalScopeArr,scope);
	zarklist_insert((globalScopeArr)->scopes[scope],(SymTableEntry*)entry);


	*array = checkScopeSize(*array,scope);
	//printf("check inside insert = > size %d\n",array->size);
	zarklist_insert((*array)->scopes[scope],(SymTableEntry*)entry);
	
}

/* checks if the given scope can exist in the given array, returns a new array if needed,
   else returns the pointer of the argument 'array' as given */
scopeArray* checkScopeSize(scopeArray* array, int scope)
{
	if (array->size<scope+1)
	{
        scopeArray * tmp = expand_scopeArr(array);
				//printf("check size %d\n",tmp->size);
        return tmp;
	}
	return array;
}

/*returns a pointer to a symtable entry if found otherwise null*/
SymTableEntry* lookup_active_with_scope (scopeArray** array, int scope,  char* c)
{

	*array = checkScopeSize(*array, scope);
	zarkNode* iter = (*array)->scopes[scope]->head;
	
	//while loop
	while (iter!=NULL)
	{
		//if it is active
		if(getNodeContent->isActive==1){
			//if it is a libfunc or a userfunction
			if ((getNodeContent->type==USERFUNC) || (getNodeContent->type==LIBFUNC))
			{
				//if it is what we are looking for
				if (strcmp(getNodeContent->value.funcVal->name,c)==0)
				{
					return getNodeContent;
				}
			//else if it is a variable
			}else{
				//if it is what we are looking for
				if (strcmp(getNodeContent->value.varVal->name,c)==0)
				{
					return getNodeContent;
				}
			}
			
		}
		
		//go to next zarkNode
		iter = iter->next;
	}
	//if we reached here nothing was found
	return NULL;
}

/*returns a pointer to any non global symtable entry that matches*/
SymTableEntry* lookup_any_with_scope(scopeArray ** array,int scope , char* c){
	*array = checkScopeSize(*array, scope);
	zarkNode* iter = (*array)->scopes[scope]->head;
	
	//while loop
	while (iter!=NULL)
	{
		
		//if it is a libfunc or a userfunction
		if ((getNodeContent->type==USERFUNC) || (getNodeContent->type==LIBFUNC))
		{
			//if it is what we are looking for
			if (strcmp(getNodeContent->value.funcVal->name,c)==0)
			{
				return getNodeContent;
			}
		//else if it is a variable
		}else{
			//if it is what we are looking for
			if (strcmp(getNodeContent->value.varVal->name,c)==0)
			{
				return getNodeContent;
			}
		}
		//go to next zarkNode
		iter = iter->next;
	}
	//if we reached here nothing was found
	return NULL;
}
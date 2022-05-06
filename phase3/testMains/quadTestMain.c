#include "../quad.h"
#include <stdio.h>
#include <string.h>

unsigned int temp_counter = 0;

char* new_temp_name(){
    char* temp_name = malloc(1024*sizeof(char));
    sprintf(temp_name, "_t%u", temp_counter++);

    // lookup(temp_name)

    return temp_name;
}

void reset_temp_counter(){
    temp_counter = 0;
}

expr* new_expr()


int main(){

    // char* tmp = new_temp_name();
    // puts(tmp);
    
    // initialization
    quads = vektor_initialize();
    expr x, n3, n5, y, z, tmp;

    quad *stmt1, *stmt2, *stmt3;
    // stmt1
    emit(assign, &x, &n3, NULL, -1, 1)
    emit(assign, &t0, &n5, )
}
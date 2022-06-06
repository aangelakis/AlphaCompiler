#include"avm.h"
#include"../libs/symtable/symtable.h"

static SymTable_T libfuncsHash;

void avm_init_libfuncs_hash(void){
    libfuncsHash = SymTable_new();
}

void avm_registerlibfunc(char* libfuncName, library_func_t libfunc) {
    SymTable_put(libfuncsHash, libfuncName, (void*) libfunc);
}

library_func_t avm_getlibraryfunc(char* libfuncName) {
    return (library_func_t) SymTable_get(libfuncsHash, libfuncName);
}

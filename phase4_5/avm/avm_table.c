#include"avm.h"

void avm_tableincrefcounter(avm_table* t){
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter > 0);
    if(!--t->refCounter){
        avm_tabledestroy(t);
    }
}

void avm_tablebucketsinit(avm_table_bucket** p,unsigned size){
    for(unsigned i = 0; i < size; ++i){
        p[i] = NULL;
    }
}

avm_table* avm_tablenew(void){
    avm_table* t = malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed, AVM_TABLE_HASHSIZE);
    avm_tablebucketsinit(t->strIndexed, AVM_TABLE_HASHSIZE);
    avm_tablebucketsinit(t->userfuncIndexed, AVM_TABLE_HASHSIZE);
    avm_tablebucketsinit(t->libfuncIndexed, 12);
    avm_tablebucketsinit(t->boolIndexed, 2);

    return t;
}

void avm_tablebucketsdestroy(avm_table_bucket** p, unsigned size){
    for(unsigned i = 0; i < size; ++i, ++p){
        for(avm_table_bucket* b = *p; b;){
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = NULL;
    }
}

void avm_tabledestroy(avm_table* t){
    avm_tablebucketsdestroy(t->strIndexed, AVM_TABLE_HASHSIZE);
    avm_tablebucketsdestroy(t->numIndexed, AVM_TABLE_HASHSIZE);
    avm_tablebucketsdestroy(t->userfuncIndexed, AVM_TABLE_HASHSIZE);
    avm_tablebucketsdestroy(t->libfuncIndexed, 12);
    avm_tablebucketsdestroy(t->boolIndexed, 2);
    free(t);
}

static unsigned hash_string(const char * s){
    assert(s);
    size_t ui;
    unsigned int uiHash = 0U, size = AVM_TABLE_HASHSIZE;
    for(ui = 0U; s[ui] != '\0'; ui++)
        uiHash = uiHash * HASH_MULTIPLIER + s[ui];
    return uiHash % size;
}

static unsigned avm_tablehash(void* void_key) {
    avm_memcell* key = (avm_memcell*) void_key;
    unsigned size = AVM_TABLE_HASHSIZE;
    
    switch (key->type)
    {
    case number_m:
        return ((unsigned) key->data.numVal*HASH_MULTIPLIER) % size;
    case string_m:
        return hash_string(key->data.strVal);
    case bool_m:
        if(key->data.boolVal)
            return 1;
        else
            return 0;
        break;
    case table_m:
        avm_error("Cannot use table as key to associative array");
    case userfunc_m:
        return ((unsigned) key->data.funcVal*HASH_MULTIPLIER) % size;
    case libfunc_m:
        return hash_string(key->data.libfuncVal);
    case nil_m:
        avm_error("Cannot use nil as key to associative array");
    case undef_m:
        avm_error("Cannot have undefined key to associative array");
    default:
        assert(0);
        break;
    }
}

static avm_table_bucket** get_from_type_table(avm_table* table, int type, int index) {
    switch (type)
    {
    case number_m:
        return &table->numIndexed[index];
    case string_m:
        return &table->strIndexed[index];
    case bool_m:
        return &table->boolIndexed[index];
    case table_m:
        avm_error("Cannot use table as key to associative array");
    case userfunc_m:
        return &table->userfuncIndexed[index];
    case libfunc_m:
        return &table->libfuncIndexed[index];
    case nil_m:
        avm_error("Cannot use nil as key to associative array");
    case undef_m:
        avm_error("Cannot have undefined key to associative array");
    default:
        assert(0);
        break;
    } 
}

void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content) { 
    assert(table);
    assert(index);
    unsigned num_ind = avm_tablehash(index);
    avm_table_bucket **iter = get_from_type_table(table, index->type, num_ind), *new_bucket;

    new_bucket = malloc(sizeof(avm_table_bucket));
    new_bucket->key = *index;       // in C structs are copied automatically
    new_bucket->value = *content;   // the only "expensive" operation C supports built-in

    new_bucket->next = *iter;
    *iter = new_bucket;
    table->total++;

    return;
}

static int compare_from_type_table(avm_table* table, int type, avm_memcell* b1, avm_memcell* b2) {
    switch (type)
    {
    case number_m:
        return b1->data.numVal == b2->data.numVal;
    case string_m:
        return !strcmp(b1->data.strVal, b2->data.strVal);
    case bool_m:
        return b1->data.boolVal == b2->data.boolVal;
    case table_m:
        avm_error("Cannot use table as key to associative array");
    case userfunc_m:
        return b1->data.funcVal == b2->data.funcVal;
    case libfunc_m:
        return !strcmp(b1->data.libfuncVal, b2->data.libfuncVal);
    case nil_m:
        avm_error("Cannot use nil as key to associative array");
    case undef_m:
        avm_error("Cannot have undefined key to associative array");
    default:
        assert(0);
        break;
    } 
}

avm_memcell * avm_tablegetelem(avm_table* table , avm_memcell* index) {
    assert(table);
    assert(index);
    unsigned num_ind = avm_tablehash(index);
    avm_table_bucket *iter = *get_from_type_table(table, index->type, num_ind);

    while(iter) {
        if(compare_from_type_table(table, index->type, &iter->key, index))
            return &iter->value;
        iter = iter->next;
    }

    return NULL;
}
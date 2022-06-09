#include "avm.h"
#include "read_binary/read_binary.h"

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
    avm_tablebucketsinit(t->libfuncIndexed, AVM_TABLE_HASHSIZE);
    avm_tablebucketsinit(t->tableIndexed, AVM_TABLE_HASHSIZE);
    avm_tablebucketsinit(t->boolIndexed, 2);

    return t;
}

void avm_tablebucketsdestroy(avm_table_bucket** p, unsigned size){
    for(unsigned i = 0; i < size; ++i){
        avm_table_bucket* b = p[i];
        while(b){
            //puts("edw");
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
    avm_tablebucketsdestroy(t->libfuncIndexed, AVM_TABLE_HASHSIZE);
    avm_tablebucketsdestroy(t->tableIndexed, AVM_TABLE_HASHSIZE);
    avm_tablebucketsdestroy(t->boolIndexed, 2);
    assert(t);
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
        return (((unsigned long) key->data.tableVal) * HASH_MULTIPLIER) % size;
        //avm_error("Cannot use table as key to associative array", &code[pc]);
    case userfunc_m:
        return ((unsigned) userfuncs[key->data.funcVal].address*HASH_MULTIPLIER) % size;
    case libfunc_m:
        return hash_string(key->data.libfuncVal);
    case nil_m:
        avm_error("Cannot use nil as key to associative array", &code[pc]);
    case undef_m:
        avm_error("Cannot have undefined key to associative array", &code[pc]);
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
        return &table->tableIndexed[index];
        //avm_error("Cannot use table as key to associative array", &code[pc]);
    case userfunc_m:
        return &table->userfuncIndexed[index];
    case libfunc_m:
        return &table->libfuncIndexed[index];
    case nil_m:
        avm_error("Cannot use nil as key to associative array", &code[pc]);
    case undef_m:
        avm_error("Cannot have undefined key to associative array", &code[pc]);
    default:
        assert(0);
        break;
    } 
}

static int compare_from_type_table(avm_table* table, int type, avm_memcell* b1, avm_memcell* b2) {
    switch (type)
    {
    case number_m:
        return b1->data.numVal == b2->data.numVal;
    case string_m:
        return (strcmp(b1->data.strVal, b2->data.strVal) == 0);
    case bool_m:
        return b1->data.boolVal == b2->data.boolVal;
    case table_m:
        return b1->data.tableVal == b2->data.tableVal;
        //avm_error("Cannot use table as key to associative array", &code[pc]);
    case userfunc_m:
        return userfuncs[b1->data.funcVal].address == userfuncs[b2->data.funcVal].address;
    case libfunc_m:
        return (strcmp(b1->data.libfuncVal, b2->data.libfuncVal) == 0);
    case nil_m:
        avm_error("Cannot use nil as key to associative array", &code[pc]);
    case undef_m:
        avm_error("Cannot have undefined key to associative array", &code[pc]);
    default:
        assert(0);
        break;
    } 
}

static void transfer_memcell_data(int type, avm_memcell* b1, avm_memcell* b2) {
    switch (type)
    {
    case number_m:
        b1->data.numVal = b2->data.numVal;
        break;
    case string_m:
        b1->data.strVal = strdup(b2->data.strVal);
        break;
    case bool_m:
        b1->data.boolVal = b2->data.boolVal;
        break;
    case table_m:
        b1->data.tableVal = b2->data.tableVal;
        break;
    case userfunc_m:
        b1->data.funcVal = b2->data.funcVal;
        break;
    case libfunc_m:
        b1->data.libfuncVal = strdup(b2->data.libfuncVal);
        break;
    case nil_m:
        avm_error("Cannot assign nil to associative array cell", &code[pc]);
        // delete cell
        break;
    case undef_m:
        break;
    default:
        assert(0);
        break;
    } 

    return;
}

void avm_tableremoveelem(avm_table* table, avm_memcell* index);

void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content) { 
    assert(table);
    assert(index);
    unsigned num_ind = avm_tablehash(index);
    avm_table_bucket **table_bucket = get_from_type_table(table, index->type, num_ind), *iter, *new_bucket;
    
    iter = *table_bucket;
    
    while(iter) {
        if(compare_from_type_table(table, index->type, &iter->key, index))
            break;
        iter = iter->next;
    }

    if(iter){
        if(content->type == nil_m){
            avm_tableremoveelem(table, index);
        }
        else{
            avm_memcellclear(&iter->value);
            //iter->value = *content;
            iter->value.type = content->type;
            transfer_memcell_data(content->type, &iter->value, content);
            if(content->type == table_m)
                avm_tableincrefcounter(content->data.tableVal);
        }
    }
    else if(content->type != nil_m){
        new_bucket = malloc(sizeof(avm_table_bucket));
        new_bucket->key.type = index->type;
        //puts("I AM HERE1");
        //printf("type = %d\n", index->type);
        transfer_memcell_data(index->type, &new_bucket->key, index);
        //puts("I AM HERE2");
        new_bucket->value.type = content->type;
        transfer_memcell_data(content->type, &new_bucket->value, content);
        //puts("I AM HERE3");

        new_bucket->next = *table_bucket;
        *table_bucket = new_bucket;
        assert(table_bucket == get_from_type_table(table, index->type, num_ind));
        //printf("I AM HERE WITH TYPE = %d\n", index->type);
        table->total++;
        if(index->type == table_m)
            avm_tableincrefcounter(index->data.tableVal);
        if(content->type == table_m)
            avm_tableincrefcounter(content->data.tableVal);
    }
    else {
        char tmp[1024];
        char *tmp_s = avm_tostring(index);
        sprintf(tmp, "Cannot create table cell with nil contents. Table cell with key: \'%s\' will not be created", tmp_s);
        avm_warning(tmp, &code[pc]);
        free(tmp_s);
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

int disable_remove_warning = 0;

void avm_tableremoveelem(avm_table* table, avm_memcell* index){
    assert(table);
    assert(index);
    unsigned num_ind = avm_tablehash(index);
    avm_table_bucket **table_bucket = get_from_type_table(table, index->type, num_ind), *iter, *prev = NULL;

    iter = *table_bucket;

    while(iter) {
        if(compare_from_type_table(table, index->type, &iter->key, index))
            break;
        prev = iter;
        iter = iter->next;
    } 

    assert(iter);


    if(prev == NULL){
        assert(table_bucket == get_from_type_table(table, index->type, num_ind));
        assert(*table_bucket == iter);
        (*table_bucket) = iter->next;
        iter->next = NULL;
        avm_memcellclear(&iter->key);
        avm_memcellclear(&iter->value);
    }
    else {
        prev->next = iter->next;
        iter->next = NULL;
        avm_memcellclear(&iter->key);
        avm_memcellclear(&iter->value);
    }

    table->total--;
    disable_remove_warning++;
}
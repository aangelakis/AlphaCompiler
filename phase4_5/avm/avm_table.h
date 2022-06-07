#define AVM_TABLE_HASHSIZE  211
#define HASH_MULTIPLIER 65599

typedef enum avm_memcell_t {
    number_m    = 0,
    string_m    = 1,
    bool_m      = 2,
    table_m     = 3,
    userfunc_m  = 4,
    libfunc_m   = 5,
    nil_m       = 6,
    undef_m     = 7
} avm_memcell_t;

typedef struct avm_table avm_table;

typedef struct avm_memcell {
    avm_memcell_t type;
    union {
        double          numVal;
        char*           strVal;
        unsigned char   boolVal;
        avm_table*      tableVal;
        unsigned        funcVal;
        char*           libfuncVal;
    } data;
} avm_memcell;

typedef struct avm_table_bucket {
    avm_memcell         key;
    avm_memcell         value;
    struct avm_table_bucket*   next;
} avm_table_bucket;

struct avm_table{
    unsigned refCounter;
    avm_table_bucket*   strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket*   numIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket*   userfuncIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket*   libfuncIndexed[12];
    avm_table_bucket*   boolIndexed[2];
    unsigned            total;
};

avm_table*      avm_tablenew(void);
void            avm_tabledestroy(avm_table* t);
avm_memcell * avm_tablegetelem(avm_table* table , avm_memcell* index);
void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content);

void avm_tableincrefcounter(avm_table* t);
void avm_tabledecrefcounter(avm_table* t);
void avm_tablebucketsinit(avm_table_bucket** p, unsigned);
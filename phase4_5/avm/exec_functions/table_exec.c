#include"../avm.h"

void execute_newtable(instruction* instr){
  avm_memcell * lv = avm_translate_operand(instr->result, (avm_memcell*) 0);
  //assert(lv && (&avm_stack[N-1] >= lv && lv > &avm_stack[top]));
  avm_memcellclear(lv);
  lv->type = table_m;
  lv->data.tableVal = avm_tablenew();
  avm_tableincrefcounter(lv->data.tableVal);

}

avm_memcell * avm_tablegetelem(avm_table* table , avm_memcell* index) { return NULL; } // TODO

void execute_tablegetelem(instruction * instr){
  avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell*) 0);
  avm_memcell *t = avm_translate_operand(instr->arg1, (avm_memcell*) 0);
  avm_memcell *i = avm_translate_operand(instr->arg2, &ax);

  //assert(lv && &avm_stack[N-1] >= lv && lv > &avm_stack[top] || lv == &retval);
  //assert(t && &avm_stack[N-1] >= t && t > &avm_stack[top]);
  assert(i);

  avm_memcellclear(lv);
  lv->type = nil_m; //default value
  if (t->type != table_m)
  {
    char tmp[1024];
    sprintf(tmp, "Illegal use of type %s as table!", typeStrings[t->type]);
    avm_error(tmp);
  }else{
    avm_memcell * content = avm_tablegetelem(t->data.tableVal, i);
    if(content){
      avm_assign(lv, content);
    }else{
      char* ts = avm_tostring(t);
      char* is = avm_tostring(i);
      char tmp[1024];
      sprintf(tmp, "%s[%s] not found!", ts, is);
      avm_warning(tmp);
      free(ts);
      free(is);
    }
  }
}

void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content) { return; } // TODO

void execute_tablesetelem(instruction* instr) {
    avm_memcell* t = avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell* i = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* c = avm_translate_operand(instr->arg2, &bx);

    // assert(t && &stack[N-1] >= t && t > stack[top]);
    assert(i && c);

    if(t->type != table_m){
        char tmp[1024];
        sprintf(tmp, "illegal use of type %s as a table!", typeStrings[t->type]);
        avm_error(tmp);
    }
    else
        avm_tablesetelem(t->data.tableVal, i, c);
}
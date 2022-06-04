#include"../avm.h"

void execute_newtable(instruction* instr){
  avm_memcell * lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
  assert(lv && (&avm_stack[N-1] >= lv && lv > &avm_stack[top]));
  avm_memcellclear(lv);
  lv->type = table_m;
  lv->data.tableVal = avm_tablenew();
  avm_tableincrefcounter(lv->data.tableVal);

}

avm_memcell * avm_tablegetelem(avm_table* table , avm_memcell* index);
void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content);

void execute_tablegetelem(instruction * instr){
  avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
  avm_memcell *t = avm_translate_operand(&instr->arg1, (avm_memcell*) 0);
  avm_memcell *i = avm_translate_operand(&instr->arg2, &ax);

  assert(lv && &avm_stack[N-1] >= lv && lv > &avm_stack[top] || lv == &retval);
  assert(t && &avm_stack[N-1] >= t && t > &avm_stack[top]);
  assert(i);

  avm_memcellclear(lv);
  lv->type = nil_m; //default value
  if (t->type != table_m)
  {
    avm_error("Illegal use of type %s as table!",typeStrings(t->type));
  }else{
    avm_memcell * content = avm_tablegetelem(t->data.tableVal, i);
    if(content){
      avm_assign(lv, content);
    }else{
      char* ts = avm_tostring(t);
      char* is = avm_tostring(i);
      avm_warning("%s[%s] not found!",ts,is);
      free(ts);
      free(is);
    }
  }
  
}
#include "quads.h"

extern FILE* quads_out;

char quad_opcode_names[26][15] = {
    "assign", "add", "sub",
    "mul", "div", "mod",
    "uminus", "and", "or",
    "not", "if_eq", "if_noteq",
    "if_lesseq", "if_greatereq", "if_less",
    "if_greater", "call", "param",
    "ret", "getretval", "funcstart",
    "funcend", "tablecreate",
    "tablegetelem", "tablesetelem","jump"
};

void const_to_string(char *arg, expr* e, expr_t t){
    switch (t) {
        case constdouble_e:
            sprintf(arg, "%f", e->content.doubleConst);
            return;
        case constint_e:
            sprintf(arg, "%d", e->content.intConst);
            return;
        case constbool_e:
            if(e->content.boolConst)
                sprintf(arg, "%s", "true");
            else
                sprintf(arg, "%s", "false");
            return;
        case conststring_e:
            sprintf(arg, "%s", e->content.strConst);
            return;
        case nil_e:
            sprintf(arg, "%s", "NULL");
            return;
    }

}


void print_quad(void* voidquad){   
    quad* q = (quad*) voidquad;
    if(q==NULL){
        return;
    }
    char *opcode = quad_opcode_names[q->op];
    //puts(opcode);
    char result[1024] = "nil", arg1[1024] = "nil", arg2[1024] = "nil";

    int line = q->line, label = q->label, source_line = q->source_code_line;
    
    if(q->op==funcend || q->op==funcstart){
        sprintf(result, "%s", q->result->content.strConst);
    }
    else if(q->op == param && q->result->type == conststring_e){
        const_to_string(result, q->result, q->result->type);
        char tmp[1024] = "\"";
        strcat(tmp, result);
        strcat(tmp, "\"");
        strcpy(result, tmp);
    }
    else if(q->op == param && q->result->type >= constdouble_e){
        const_to_string(result, q->result, q->result->type);
    }
    else if(q->result){
        expr_t type = q->result->type;
        //printf("result.type=%d\n", type);
        if(type == conststring_e){
            const_to_string(result, q->result, type);
            char tmp[1024] = "\"";
            strcat(tmp, result);
            strcat(tmp, "\"");
            strcpy(result, tmp);
        }
        else if(type == constbool_e || (type == boolexpr_e && q->result->sym == NULL)){
            type = constbool_e;
            const_to_string(result, q->result, type);
            char tmp[1024] = "\'";
            strcat(tmp, result);
            strcat(tmp, "\'");
            strcpy(result, tmp);
        }
        else if(type >= constdouble_e) {
            const_to_string(result, q->result, type);
            //result = "const";
        }
        else if(q->result->sym->type < USERFUNC)
            sprintf(result, "%s", (char*) q->result->sym->value.varVal->name);
        else
            sprintf(result, "%s", (char*) q->result->sym->value.funcVal->name);
    }
    //puts("I AM HERE0");
    
    // arg1
    if(q -> arg1){
        expr_t type = q->arg1->type;
        //printf("arg1.type=%d\n", type);
        if(type == conststring_e){
            const_to_string(arg1, q->arg1, type);
            char tmp[1024] = "\"";
            strcat(tmp, arg1);
            strcat(tmp, "\"");
            strcpy(arg1, tmp);
        }
        else if(type == constbool_e || (type == boolexpr_e && q->arg1->sym == NULL)){
            type = constbool_e;
            const_to_string(arg1, q->arg1, type);
            char tmp[1024] = "\'";
            strcat(tmp, arg1);
            strcat(tmp, "\'");
            strcpy(arg1, tmp);
        }
        else if(type >= constdouble_e) {
            const_to_string(arg1, q->arg1, type);
            //arg1 = "const";
        }
        else if(q->arg1->sym->type < USERFUNC){
            sprintf(arg1, "%s", (char*) q->arg1->sym->value.varVal->name);
        }
        else
            sprintf(arg1, "%s", (char*) q->arg1->sym->value.funcVal->name);
    }
    //puts("I AM HERE1");
    
    // arg2
    if(q -> arg2){
        expr_t type = q->arg2->type;
        //printf("arg2.type=%d\n", type);
        if(type == conststring_e){
            const_to_string(arg2, q->arg2, type);
            char tmp[1024] = "\"";
            strcat(tmp, arg2);
            strcat(tmp, "\"");
            strcpy(arg2, tmp);
        }
        else if(type == constbool_e || (type == boolexpr_e && q->arg2->sym == NULL)){
            type = constbool_e;
            const_to_string(arg2, q->arg2, type);
            char tmp[1024] = "\'";
            strcat(tmp, arg2);
            strcat(tmp, "\'");
            strcpy(arg2, tmp);
        }
        else if(type >= constdouble_e){
            const_to_string(arg2, q->arg2, type);
            //arg2 = "const";
        }
        else if(q->arg2->sym->type < USERFUNC)
            sprintf(arg2, "%s", (char*) q->arg2->sym->value.varVal->name);
        else
            sprintf(arg2, "%s", (char*) q->arg2->sym->value.funcVal->name);
    }
    //puts("I AM HERE2");
    
    if (label == -1)
       // printf("%d:\t\t\t%-12s\t\t\t%-4s\t\t\t%-4s\t\t%-4s\t\t%s\n", line, opcode, result, arg1, arg2, "nil");
       fprintf(quads_out, "%d:\t\t\t%-12s\t\t\t%-4s\t\t\t%-4s\t\t%-4s\t\t%-3s\t\t[line: %d]\n", line, opcode, result, arg1, arg2, "nil",source_line);
    else
       fprintf(quads_out, "%d:\t\t\t%-12s\t\t\t%-4s\t\t\t%-4s\t\t%-4s\t\t%-3d\t\t[line: %d]\n", line, opcode, result, arg1, arg2, label, source_line);
       // printf("%d:\t\t\t%-12s\t\t\t%-4s\t\t\t%-4s\t\t%-4s\t\t%d\n", line, opcode, result, arg1, arg2, label);
}
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
    char *result = NULL, *arg1 = NULL, *arg2 = NULL;
    
    if(q->result && q->result->type >= constdouble_e)
        result = malloc(sizeof(char)*1024);
    if(q->arg1 && q->arg1->type >= constdouble_e)
        arg1 = malloc(sizeof(char)*1024);
    if(q->arg2 && q->arg2->type >= constdouble_e)
        arg2 = malloc(sizeof(char)*1024);
    //char *result = NULL, arg1[1024], arg2[1024];
    int label , line;
    line = q->line;
    label = q->label;
    
    if(q->op==funcend || q->op==funcstart){
        result = q->result->content.strConst;
    }
    else if(q->op == param && q->result->type >= constdouble_e){
        const_to_string(result, q->result, q->result->type);
    }
    else if(q->result)
        result = (char*) q->result->sym->value.varVal->name;
    
    // arg1
    if(q -> arg1){
        expr_t type = q->arg1->type;
        if(type == conststring_e){
            const_to_string(arg1, q->arg1, type);
            char tmp[1024] = "\"";
            strcat(tmp, arg1);
            strcat(tmp, "\"");
            strcpy(arg1, tmp);
        }
        else if(type == constbool_e){
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
        else if(q->arg1->sym->type < USERFUNC)
            arg1 = (char*) q->arg1->sym->value.varVal->name;
        else
            arg1 = (char*) q->arg1->sym->value.funcVal->name;
    }
    else
        arg1 = "nil";
    
    // arg2
    if(q -> arg2){
        expr_t type = q->arg2->type;
        if(type == conststring_e){
            const_to_string(arg1, q->arg1, type);
            char tmp[1024] = "\"";
            strcat(tmp, arg2);
            strcat(tmp, "\"");
            strcpy(arg2, tmp);
        }
        else if(type == constbool_e){
            const_to_string(arg1, q->arg1, type);
            char tmp[1024] = "\'";
            strcat(tmp, arg1);
            strcat(tmp, "\'");
            strcpy(arg1, tmp);
        }
        else if(type >= constdouble_e){
            const_to_string(arg2, q->arg2, type);
            //arg2 = "const";
        }
        else if(q->arg2->sym->type < USERFUNC)
            arg2 = (char*) q->arg2->sym->value.varVal->name;
        else
            arg2 = (char*) q->arg2->sym->value.funcVal->name;
    }
    else
        arg2 = "nil";

    if (label == -1)
       // printf("%d:\t\t\t%-12s\t\t\t%-4s\t\t\t%-4s\t\t%-4s\t\t%s\n", line, opcode, result, arg1, arg2, "nil");
       fprintf(quads_out, "%d:\t\t\t%-12s\t\t\t%-4s\t\t\t%-4s\t\t%-4s\t\t%s\n", line, opcode, result, arg1, arg2, "nil");
    else
       fprintf(quads_out, "%d:\t\t\t%-12s\t\t\t%-4s\t\t\t%-4s\t\t%-4s\t\t%d\n", line, opcode, result, arg1, arg2, label);
       // printf("%d:\t\t\t%-12s\t\t\t%-4s\t\t\t%-4s\t\t%-4s\t\t%d\n", line, opcode, result, arg1, arg2, label);

 
    if(q->result && q->result->type >= constdouble_e)
        free(result);
    if(q->arg1 && q->arg1->type >= constdouble_e)
        free(arg1);
    if(q->arg2 && q->arg2->type >= constdouble_e)
        free(arg2);
}
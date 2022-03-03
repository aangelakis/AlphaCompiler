#include <stdio.h>

struct open_comment_list{
  unsigned int line;
  struct open_comment_list* previous;
};

struct close_comment_list{
  unsigned int opening_line;
  unsigned int closing_line;
  struct open_comment_list* next;
};

struct open_comment_list *last_opened_comment = NULL;

struct close_comment_list *first_closed_comment = NULL;


void open_comment(int opening_line){
  struct open_comment_list *node = malloc(sizeof(struct open_comment_list));
  node->line = opening_line;
  
  if (last_opened_comment==NULL)
  {
    node->previous = NULL;
    last_opened_comment = node;
  }else{
    node->previous = last_opened_comment;
    last_opened_comment = node;
  }
}

void close_comment(int closing_line){
  //pointer sto proteleutaio twn open
  struct open_comment_list *tmp = last_opened_comment->previous;

  //etoimazw to neo closed comment node
  struct close_comment_list *node = malloc(sizeof(struct close_comment_list));
  node->closing_line = closing_line;
  node->opening_line = last_opened_comment->line;

  //kanw free to teleutaio twn open kai allazw ton global pointer
  free(last_opened_comment);
  last_opened_comment = tmp;

  //an einai to prwto pu tha kleisei
  if(first_closed_comment==NULL){
    first_closed_comment = node;
    return;
  }

  //bazw to neo closed comment node sto telos
  struct close_comment_list *tmp2 = first_closed_comment;

  while (tmp2->next!=NULL)
  {
    tmp2 = tmp2->next;
  }
  tmp2->next = node;
}






//sf 20 einai oti exume ena /
//sf 21 line comment
//sf 22 block comment
//sf 23 / mesa se block comment
//

int inside_block=0;
int nested_comments = 0;

int sf20(char c){
  if(c=='/'&& inside_block==0)  return STATE(21);
  if(c=='*'){ nested_comments=0;return STATE(22);} //arxise block comment

  ExtendLexem(c)
  
}

int sf21(char c){
  if(c!='\n') return STATE(21);

  ExtendLexem(c);
  return TOKEN(LINE_COMMENT);
}

int sf22(char c){ //block comment
  
  if(c=='/')    return STATE(23); //pithanotita gia nested
  if(c=='*')    return STATE(24); //pithanotita kleisimatos comment

  
  return STATE(22);
}

int sf23(char c){
  if(c!='*')    return STATE(22); //oxi nested

  nested_comments++;   //brethike nested
  return STATE(22);
}

int sf24(char c){
  if(c!='/') return STATE(22);  //den ekleise to comment
  if(nested_comments==0){       //an den iparxoun nested tote ekleise to block
    ExtendLexem(c);
    return TOKEN(BLOCK_COMMENT);
  }
  nested_comments--;

}
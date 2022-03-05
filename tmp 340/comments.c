#include <stdio.h>

/* IN CASE STACKS ARE NEEDED
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

*/




//sf 20 einai oti exume ena /
//sf 21 line comment
//sf 22 block comment


int inside_block=0;
int nested_comments = 0;

// prwto / brethike
int sf20(char c){
  if(c=='/')                    return STATE(21);   //arxise line comment
  if(c=='*'){ nested_comments=0;return STATE(22);}  //arxise block comment

  ExtendLexeme(c);

  //edw mporei na einai kai to operand slash
  return STATE(?)
  
}

//mesa se line comment
int sf21(char c){
    while(c != \'n')
      c = GetNextChar();
    
    //if(c!='\n') return STATE(21);

    //ExtendLexeme(c);
    return TOKEN(LINE_COMMENT);
}



int sf22(char c){ //block comment
  
  int charIntForm=0;
  while (1)
  {
      //printf("got this -> %c == %d \n",c,c);
      if (c == '/')  //pithanotita nested comment
    {
      charIntForm = GetNextChar();  //pairnw ton epomeno
      if (charIntForm==-1)  //check an ftasame EOF
      {
        return TOKEN(UNCLOSED_BLOCK_COMMENT);
      }
      c = (char)charIntForm;  //metatropi apo ascii se char
      
      //ama den mpei stin if idi exume parei ton epomeno xaraktira 
      if (c == '*') //exoume nested comment
      {
        printf("NESTED COMMENT OPENED IN LINE %d\n",69);
        nested_comments++;

          //etoimazw ton epomeno xaraktira
        charIntForm = GetNextChar();  //pairnw ton epomeno
          if (charIntForm==-1)  //check an ftasame EOF
          {
            return TOKEN(UNCLOSED_BLOCK_COMMENT);  //ean eimaste sto eof den ekleise pote to comment
          }
          c = (char)charIntForm;  //metatropi apo ascii se char
      }
      
    }else if (c == '*') //pithanotita kleisimatos comment
    {
      charIntForm = GetNextChar();  //pairnw ton epomeno
      if (charIntForm==-1)  //check an ftasame EOF
      {
        return TOKEN(UNCLOSED_BLOCK_COMMENT);  //ean eimaste sto eof den ekleise pote to comment
      }
      c = (char)charIntForm;  //metatropi apo ascii se char

      //an den mpei stin if idi exoume parei epomeno xaraktira ara den xreiazete
      if (c=='/')   //ekleise ena comment
      {
        if (nested_comments!=0) //check an exoume nested comments
        {
          nested_comments--;  //meiwnoume kata ena ta nested comments
          printf("Ekleise nested comment stin grammi %d\n",69);
        }else{
          inside_block = 0;   //ekleise to block comment
          return TOKEN(BLOCK_COMMENT);  
        }

            //etoimazw ton epomeno xaraktira
        charIntForm = GetNextChar();  //pairnw ton epomeno
        if (charIntForm==-1)  //check an ftasame EOF
        {
          return TOKEN(UNCLOSED_BLOCK_COMMENT);  //ean eimaste sto eof den ekleise pote to comment
        }
        c = (char)charIntForm;  //metatropi apo ascii se char
        
      } //an den ekleise to comment agnooume otidipote allo
    }else{
        //etoimazw ton epomeno xaraktira
      charIntForm = GetNextChar();  //pairnw ton epomeno
        if (charIntForm==-1)  //check an ftasame EOF
        {
          return TOKEN(UNCLOSED_BLOCK_COMMENT);  //ean eimaste sto eof den ekleise pote to comment
        }
        c = (char)charIntForm;  //metatropi apo ascii se char
    }
    
    
  }

}


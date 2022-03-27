/* IDENTIFIER */
%token<strVal> IDENTIFIER
/* STRING */
%token<strVal> STRING
/* INTEGER */
%token<intVal> INT
/* DOUBLE*/
%token<realVal> DOUBLE

/* OPERATORS */
%token LE              "<="
%token LT              "<"
%token NE              "!="
%token GE              ">="
%token GT              ">"
%token EQ              "=="
%token ASSIGN          "="
%token PLUS            "+"
%token MINUS           "-"
%token PLUS_PLUS       "++"
%token MINUS_MINUS     "--"
%token MULT            "*"
%token DIV             "/"
%token MOD             "%"

/* KEYWORDS */
%token IF              "if"
%token ELSE            "else"
%token WHILE           "while"
%token FOR             "for"
%token FUNCTION        "function"
%token RETURN          "return"
%token BREAK           "break"
%token CONTINUE        "continue"
%token AND             "and"
%token NOT             "not"
%token OR              "or"
%token LOCAL           "local"
%token TRUE            "true"
%token FALSE           "false"
%token NIL             "nil"

/* PUNCTUATION */
%token LEFT_BRACE          "["
%token RIGHT_BRACE         "]"
%token LEFT_BRACKET        "{"
%token RIGHT_BRACKET       "}"
%token LEFT_PARENTHESIS    "("
%token RIGHT_PARENTHESIS   ")"
%token SEMICOLON           ";"
%token COMMA               ","
%token COLON               ":"
%token DOUBLE_COLON        "::"
%token STOP                "."
%token DOUBLE_STOP         ".."

/* Operator Associativity and Priority (Bottom-to-Top Priority)*/
%right ASSIGN
%left OR
%left AND
%nonassoc NE EQ
%nonassoc GT GE LT LE
%left PLUS 
%right MINUS
%left MULT DIV MOD
%right NOT PLUS_PLUS MINUS_MINUS MINUS
%left STOP DOUBLE_STOP
%left LEFT_BRACE RIGHT_BRACE
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS
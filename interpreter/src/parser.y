%code requires
{
  #include <string>
  #include <iostream>
  #include <cstring>

  #include "ast.h"
}

%union {
  Node * node;
  int i;
  std::string * str;
}
%define parse.error verbose
%defines "inc/parser.h"
%output "src/parser.cpp"

%type <node> testScript Test TestList Routine RoutineList ReadMsgCall 
%type <node> ReadPinCall SendMsgCall SetAnalogTail SetPinCall Statement 
%type <node> StatementList VariableAssign Exp ExpectCall LoopCall
%type <node> PromptCall PrintCall DelayCall VarList Index CanManip

%token <node> routine test loop delay read_pin set_pin perrint perrintln expect 
%token <node> exit_tok prompt read_msg send_msg call forever dout din aout ain 
%token <node> ';' '(' ')' '{' '}' '|' serialRx serialTx assert If Else length
%token <str> stringLiteral identifier can_msg add mult  
%token <str> comparison andToken orToken NE EQ
%token <i> integerLiteral hexLiteral dstate
%token plusplus minusminus

%left '(' ')' orToken andToken NE EQ '[' ']'
%right plusplus minusminus
%nonassoc comparison If
%nonassoc Else
%left add
%left mult
%right '='

%locations


%{
  #include <string>
  #include <iostream>
  #include <cstdio>

  #include "symbol-table.h"
  #include "object.h"
  #include "ast.h"

  extern FILE *yyin;
  extern int yylineno;  

  int yylex(void);
  void yyerror(const char * err);

  Node * root;
  std::string infilename;
  int errors = 0;
  int perform_math_op(Node * lhs, Node * rhs, std::string * op);
  std::string stringifyNode(Node * node);


%}

%%
goal: 
  testScript;


testScript:
  VarList RoutineList TestList  {
      $$ = new Node("Script", 0);
      if (!$1->children.empty())
      {
        $$->addChild($1);
      }
      else
      {
        delete $1;
      }

      if (!$2->children.empty())
      {
        $$->addChild($2);
      }
      else
      {
        delete $2;
      }

      if (!$3->children.empty())
      {
        $$->addChild($3);
      }
      else
      {
        delete $3;
      }

      root = $$;
      if (errors == 0)
        $$->print();
  };



VarList:
  %empty {
      $$ = new Node(vardecl_list_node, yylineno);
  }
  | VarList VariableAssign {
      $$ = $1;
      $$->addChild($2);
  };


RoutineList:
  RoutineList Routine {
      $$ = $1;
      $$->addChild($2);
  }
  | %empty {
      $$ = new Node(routine_list_node, yylineno);
    };


/* will not allow empty routines / tests, there must be at least 1 expression
   otherwise they would be pointless */

Routine:
  routine stringLiteral '{' StatementList '}' {
    int lineno = @1.first_line - $4->line_no;
    $$ = new Node(routine_node, lineno);
    $$->setString($2);
    $$->addChild($4);
  };



TestList:
  TestList Test { 
    $$ = $1;
    $$->addChild($2);
  }
  | %empty { $$ = new Node(test_list_node, yylineno); };


Test:
  test stringLiteral '{' StatementList '}' {
    int lineno = @1.first_line - $4->line_no;
    $$ = new Node(test_node, lineno);
    $$->setString($2);
    $$->addChild($4);
  };
 
  

StatementList:
    %empty {
      $$ = new Node(statement_list, yylineno);
  }
  | StatementList Statement {
      $$ = $1;
      $$->addChild($2);
  }


ExpectCall: 
  expect Exp {
      $$ = new Node(expect_node, @1.first_line);
      $$->addChild($2);
  }
  | assert Exp {
      $$ = new Node(assert_node, @1.first_line);
      $$->addChild($2);
  };


PromptCall:
  prompt Exp {
    $$ = new Node(prompt_node, @1.first_line);
    $$->addChild($2);
  };




PrintCall:
  perrint Exp {
      $$ = new Node(print, @1.first_line);
      $$->addChild($2);
  };
  | perrintln Exp {
      $$ = new Node(println, @1.first_line);
      $$->addChild($2);
  };


Index:
  '[' Exp ']' {
    $$ = new Node(index_node, @2.first_line);
    $$->addChild($2);
    $$->setString("[]");
  }
;



CanManip:
  identifier Index {
    $$ = new Node(identifier_node, @1.first_line);
    $$->setString($1);
    $$->addChild($2);
  }
  | identifier '.' length{
    $$ = new Node(identifier_node, @1.first_line);
    $$->setString($1);
    $$->addChild(new Node(length_node, @1.first_line));
  }


Exp:
   CanManip {
      $$ = $1;
  }
  | Exp add Exp  {
      if ($1->isLiteral() && $3->isLiteral())
      {
        node_type_t lhst = $1->node_type; 
        node_type_t rhst = $3->node_type; 
        if ((lhst == integerLiteral_node || lhst == hexLiteral_node) 
            && (rhst == integerLiteral_node || rhst == hexLiteral_node))
        {
          perform_math_op($1, $3, $2);
        }
        else if ($1->node_type == stringLiteral_node 
                 || $3->node_type == stringLiteral_node)
        {
          // TODO string concatenation
          Node * str = new Node(stringLiteral_node, $1->line_no);
          std::cout << "node 1: " << stringifyNode($1) << " | node 2: " << stringifyNode($3) << "\n";
          std::string val = stringifyNode($1) + stringifyNode($3);
          str->setString(val);
          delete $1;
          delete $2;
          delete $3;
          $$ = str;
        }
        else 
        {
          $$ = new Node(binary_math_node, @1.first_line);
          $$->setString($2);
          $$->addChild($1);
          $$->addChild($3);
        }
      }
  
      else 
      {
        $$ = new Node(binary_math_node, @1.first_line);
        $$->setString($2);
        $$->addChild($1);
        $$->addChild($3);
      }
  }
  | Exp mult Exp {
      if ($1->isLiteral() && $3->isLiteral())
      {
        node_type_t lhst = $1->node_type; 
        node_type_t rhst = $3->node_type; 
        if ((lhst == integerLiteral_node || lhst == hexLiteral_node) 
            && (rhst == integerLiteral_node || rhst == hexLiteral_node))
        {
          perform_math_op($1, $3, $2);
        }
         else 
        {
          $$ = new Node(binary_math_node, @1.first_line);
          $$->setString($2);
          $$->addChild($1);
          delete $2;
          $$->addChild($3);
        }
      }
      else
      {
        $$ = new Node(binary_math_node, @1.first_line);
        $$->setString($2);
        $$->addChild($1);
        $$->addChild($3);
      }

  }
  | Exp NE Exp {

      $$ = new Node(comparison_node, @1.first_line);
      $$->setString($2);
      $$->addChild($1);
      $$->addChild($3);
  }
  | Exp EQ Exp {

      $$ = new Node(comparison_node, @1.first_line);
      $$->setString($2);
      $$->addChild($1);
      $$->addChild($3);
  }
  | Exp comparison Exp {
      $$ = new Node(comparison_node, @1.first_line);
      $$->setString($2);
      $$->addChild($1);
      $$->addChild($3);
  }
  | Exp andToken Exp {
      $$ = new Node(and_node, @1.first_line);
      $$->setString($2);
      $$->addChild($1);
      $$->addChild($3);
  }
  | Exp orToken Exp {
      $$ = new Node(or_node, @1.first_line);
      $$->setString($2);
      $$->addChild($1);
      $$->addChild($3);
  }
  | identifier {
    $$ = new Node(identifier_node, @1.first_line);
    $$->setString($1);
  }
  | stringLiteral {
    $$ = new Node(stringLiteral_node, @1.first_line);
    $$->setString($1);
  }
  | integerLiteral {
    $$ = new Node(integerLiteral_node, @1.first_line);
    $$->setInt($1);
  }
  | hexLiteral {
    $$ = new Node(hexLiteral_node, @1.first_line);
    $$->setInt($1);
  }
  | can_msg {
    $$ = new Node(can_msg_node, @1.first_line);
    $$->setCanMsg($1);
  }

  | add Exp {
      node_type_t type = $2->node_type;

      if ($2->isLiteral() && (type == integerLiteral_node 
                                || type == hexLiteral_node))
      {
        if (*$1 == "+")
        {
          $2->setInt(+$2->data.intval);
        }
        else if (*$1 == "-")
        {
          $2->setInt(-$2->data.intval);
        }
      }
      else
      {
        $$ = new Node(binary_math_node, @1.first_line);
        $$->setString($1);
        $$->addChild($2);
      }
  }
  | '(' Exp ')' {
    $$ = $2;
  };


VariableAssign:
  identifier '=' Exp ';'{
      $$ = new Node(vardecl_node, @1.first_line);
      $$->setString($1);
      $$->addChild($3);
  }
  | identifier Index '=' Exp ';' {
      $$ = new Node(vardecl_node, @1.first_line);
      $$->setString($1);
      $$->addChild($4);
      $$->addChild($2);
  }
  | identifier '.' length '=' Exp ';' {
      $$ = new Node(vardecl_node, @1.first_line);
      Node * l = new Node(length_node, @1.first_line);
      l->setString("length");
      $$->setString($1);
      $$->addChild($5);
      $$->addChild(l);
  }
  ;

SendMsgCall:
  send_msg hexLiteral Exp {
      $$ = new Node(send_msg_node, @1.first_line);
      Node * id = new Node(hexLiteral_node, @1.first_line);

      id->setInt($2);

      $$->addChild(id);
      $$->addChild($3);
  }
  | send_msg identifier Exp {
      $$ = new Node(send_msg_node, @1.first_line);
      Node * var = new Node (identifier_node, @1.first_line);
      var->setString($2);

      $$->addChild(var);
      $$->addChild($3);
  };




ReadMsgCall:
  read_msg hexLiteral  {
      $$ = new Node(read_msg_node, @1.first_line);
      Node * id = new Node(hexLiteral_node, @1.first_line);
      id->setInt($2);
      $$->addChild(id);
  }
  | read_msg identifier {
      $$ = new Node(read_msg_node, @1.first_line);
      Node * var = new Node(identifier_node, @1.first_line);
      var->setString($2);
      $$->addChild(var);
  };



ReadPinCall:
  read_pin ain integerLiteral {
      $$ = new Node(analog_read, @1.first_line);
      Node * pin = new Node(integerLiteral_node, @1.first_line);
      pin->setInt($3);
      $$->addChild(pin);
  }
  | read_pin ain identifier {
      $$ = new Node(analog_read, @1.first_line);
      Node * var = new Node(identifier_node, @1.first_line);
      var->setString($3);
      $$->addChild(var);
  }
  | read_pin din integerLiteral {
      $$ = new Node(digital_read, @1.first_line);
      Node * pin = new Node(integerLiteral_node, @1.first_line);
      pin->setInt($3);
      $$->addChild(pin);
  }
  | read_pin din identifier {
      $$ = new Node(digital_read, @1.first_line);
      Node * var = new Node(identifier_node, @1.first_line);
      var->setString($3);

      $$->addChild(var);
  };

SetAnalogTail:
  integerLiteral identifier { 
      $$ = new Node(analog_write, @1.first_line);
      Node * pin = new Node(integerLiteral_node, @1.first_line);
      Node * var = new Node(identifier_node, @1.first_line);
      var->setString($2);
      pin->setInt($1);

      $$->addChild(pin);
      $$->addChild(var);
  }
  | identifier identifier  {
      $$ = new Node(analog_write, @1.first_line);
      Node * var = new Node(identifier_node, @1.first_line);
      Node * var1 = new Node(identifier_node, @1.first_line);
      
      var->setString($1);
      var->setString($2);

      $$->addChild(var);
      $$->addChild(var1);
  }
  | identifier integerLiteral {
      $$ = new Node(analog_write, @1.first_line);
      Node * value = new Node(integerLiteral_node, @1.first_line);
      Node * var = new Node(identifier_node, @1.first_line);
      var->setString($1);
      value->setInt($2);

      $$->addChild(var);
      $$->addChild(value);
  }
  | integerLiteral integerLiteral {
      $$ = new Node(analog_write, @1.first_line);
      Node * pin = new Node(integerLiteral_node, @1.first_line);
      Node * value = new Node(integerLiteral_node, @1.first_line);
      pin->setInt($1);
      value->setInt($2);

      $$->addChild(pin);
      $$->addChild(value);
  };


SetPinCall:
  set_pin aout SetAnalogTail {
      $$ = $3;
 }
  | set_pin dout integerLiteral dstate {
      $$ = new Node(digital_write, @1.first_line);
      Node * pin = new Node(integerLiteral_node, @1.first_line);
      pin->setInt($3);
      $$->setInt($4);
      $$->addChild(pin);
  }
  | set_pin dout identifier dstate {
      $$ = new Node(digital_write, @1.first_line);
      Node * var = new Node(identifier_node, @1.first_line);
      var->setString($3);
      $$->setInt($4);
      $$->addChild(var);
  } ;



DelayCall:
  delay Exp {
      $$ = new Node(delay_node, @1.first_line);
      $$->addChild($2);
  };


LoopCall:
  loop Exp '{' StatementList '}' {
      $$ = new Node(loop_node, @1.first_line);
      $$->addChild($2);
      $$->addChild($4);
  }
  | loop forever '{' StatementList '}' {
      $$ = new Node(loop_node, @1.first_line);
      Node * times = new Node(forever_node, @1.first_line);
      $$->addChild(times);
      $$->addChild($4);
  };

Statement: error ';' {
    errors++;
    yyerrok;
    yyclearin;
  }
  | If '(' Exp ')' '{' StatementList '}' {
      $$ = new Node(if_node, @1.first_line);
      $$->addChild($3);
      $$->addChild($6);
  }
  | If '(' Exp ')' '{' StatementList '}' Else '{' StatementList '}' {
      $$ = new Node(if_node, @1.first_line);
      $$->addChild($3);
      $$->addChild($6);

      Node * elsenode = new Node(else_node, @1.first_line);
      elsenode->addChild($10);

      $$->addChild(elsenode);

  }
  | VariableAssign{
      $$ = $1;
  }
  | call stringLiteral ';' {
      $$ = new Node(call_node, @1.first_line);
      $$->setString($2);
  }
  | LoopCall {
      $$ = $1;
  }
  | SetPinCall ';' {
      $$ = $1;
  }
  | ReadPinCall ';' {
      $$ = $1;
  }
  | ExpectCall ';' {
      $$ = $1;
  }
  | PrintCall ';' {
      $$ = $1;
  }
  | SendMsgCall ';' {
      $$ = $1;
  }
  | ReadMsgCall ';' {
      $$ = $1;
  }
  | DelayCall ';' {
      $$ = $1;
  }
  | PromptCall ';' {
      $$ = $1;
  }
  | serialTx Exp ';' {
      $$ = new Node(serial_tx, @1.first_line);
      $$->addChild($2);
  }
  | serialRx ';' {
      $$ = new Node(serial_rx, @1.first_line);
  }
  | exit_tok ';' {
      $$ = new Node(exit_node, @1.first_line);
  }
  | exit_tok stringLiteral ';' {
      $$ = new Node(exit_node, @1.first_line);
      $$->setString($2);
  }
  | Exp plusplus ';'{
      node_type_t type = $1->node_type;

      if ($1->isLiteral() && (type == integerLiteral_node 
                              || type == hexLiteral_node))
      {
        $1->data.intval++;
      }
      else
      {
        $$ = new Node(unary_math_node, @1.first_line);
        $$->setString("++");
        $$->addChild($1);
      }

  }
  | Exp minusminus ';'{
      node_type_t type = $1->node_type;

      if ($1->isLiteral() && (type == integerLiteral_node 
                              || type == hexLiteral_node))
      {
        $1->data.intval--;
      }
      else
      {
        $$ = new Node(unary_math_node, @1.first_line);
        $$->setString("--");
        $$->addChild($1);
      }
  };


%%


void yyerror(const char * err)
{
  printf("\n%s on line %d", err, yylloc.first_line);
}



int perform_math_op(Node * lhs, Node * rhs, std::string * op)
{
  std::string oper = *op;
  int lhs_val = lhs->data.intval;
  int rhs_val = rhs->data.intval;

  if (oper == "+")
  {
    lhs->setInt(lhs_val + rhs_val);
  } 
  else if (oper == "-")
  {
    lhs->setInt(lhs_val - rhs_val);
  } 
  else if (oper == "*")
  {
    lhs->setInt(lhs_val * rhs_val);
  } 
  else if (oper == "/")
  {
    lhs->setInt(lhs_val / rhs_val);
  }
  delete rhs;
  delete op;
  return lhs->data.intval;
}



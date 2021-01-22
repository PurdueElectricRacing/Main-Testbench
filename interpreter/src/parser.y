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

%type <node> testScript Test TestList Routine RoutineList ReadMsgCall 
%type <node> ReadPinCall SendMsgCall SetAnalogTail SetPinCall Statement 
%type <node> StatementList VariableDecl Exp ExpectCall ExpectList LoopCall
%type <node> PromptCall PrintCall DelayCall VarList

%token <node> routine test loop delay read_pin set_pin perrint perrintln expect 
%token <node> exit_tok prompt read_msg send_msg call forever dout din aout ain 
%token <node> ';' '(' ')' '{' '}' '|' serialRx serialTx assert
%token <str> stringLiteral identifier can_msg add mult plusplus 
%token <str> minusminus comparison andToken orToken
%token <i> integerLiteral hexLiteral dstate


%left '(' ')' orToken andToken 
%right plusplus minusminus
%left add
%left mult
%right '='



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
  | VarList VariableDecl {
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
    int lineno = yylineno - $4->line_no;
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
    int lineno = yylineno - $4->line_no;
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


ExpectList:
  ExpectList andToken ExpectList {
      $$ = new Node(and_node, yylineno);
      $$->addChild($1);
      $$->addChild($3);
  }
  | ExpectList orToken ExpectList {
      $$ = new Node(or_node, yylineno);
      $$->addChild($1);
      $$->addChild($3);
  }
  | comparison Exp {
      $$ = new Node(comparison_node, yylineno);
      $$->setString($1);
      $$->addChild($2);
  };

ExpectCall: 
  expect ExpectList {
      $$ = new Node(expect_node, yylineno);
      $$->addChild($2);
  }
  | assert ExpectList {
      $$ = new Node(assert_node, yylineno);
      $$->addChild($2);
  };


PromptCall:
  prompt Exp {
    $$ = new Node(prompt_node, yylineno);
    $$->addChild($2);
  };




PrintCall:
  perrint Exp {
      $$ = new Node(print, yylineno);
      $$->addChild($2);
  };
  | perrintln Exp {
      $$ = new Node(println, yylineno);
      $$->addChild($2);
  };



Exp:
  Exp add Exp  {
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
          std::string val = stringifyNode($1) + stringifyNode($3);
          str->setString(val);
          delete $1;
          delete $3;
          $$ = str;
        }
        else 
        {
          $$ = new Node($2, yylineno);
          $$->addChild($1);
          $$->addChild($3);
        }
      }
  
      else 
      {
        $$ = new Node($2, yylineno);
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
          $$ = new Node($2, yylineno);
          $$->addChild($1);
          $$->addChild($3);
        }
      }
      else
      {
        $$ = new Node($2, yylineno);
        $$->addChild($1);
        $$->addChild($3);
      }

  }
  | Exp plusplus {
      node_type_t type = $1->node_type;

      if ($1->isLiteral() && (type == integerLiteral_node 
                              || type == hexLiteral_node))
      {
        $1->data.intval++;
      }
      else
      {
        $$ = new Node($2, yylineno);
        $$->addChild($1);
      }

  }
  | Exp minusminus {
      node_type_t type = $1->node_type;

      if ($1->isLiteral() && (type == integerLiteral_node 
                              || type == hexLiteral_node))
      {
        $1->data.intval--;
      }
      else
      {
        $$ = new Node($2, yylineno);
        $$->addChild($1);
      }
  }
  | identifier {
    $$ = new Node(identifier_node, yylineno);
    $$->setString($1);
  }
  | stringLiteral {
    $$ = new Node(stringLiteral_node, yylineno);
    $$->setString($1);
  }
  | integerLiteral {
    $$ = new Node(integerLiteral_node, yylineno);
    $$->setInt($1);
  }
  | hexLiteral {
    $$ = new Node(hexLiteral_node, yylineno);
    $$->setInt($1);
  }
  | can_msg {
    $$ = new Node(can_msg_node, yylineno);
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
        $$ = new Node($1, yylineno);
        $$->addChild($2);
      }
  }
  | '(' Exp ')' {
    $$ = $2;
  };



VariableDecl:
  identifier '=' Exp ';'{
      $$ = new Node(vardecl_node, yylineno);
      $$->setString($1);
      $$->addChild($3);
  };

SendMsgCall:
  send_msg hexLiteral can_msg {
      $$ = new Node(send_msg_node, yylineno);
      Node * id = new Node(hexLiteral_node, yylineno);
      Node * msg = new Node(can_msg_node, yylineno);

      id->setInt($2);
      msg->setCanMsg($3);

      $$->addChild(id);
      $$->addChild(msg);
  }
  | send_msg identifier can_msg {
      $$ = new Node(send_msg_node, yylineno);
      Node * msg = new Node(can_msg_node, yylineno);
      Node * var = new Node (identifier_node, yylineno);
      var->setString($2);
      msg->setCanMsg($3);

      $$->addChild(var);
      $$->addChild(msg);
  }
  | send_msg hexLiteral identifier {
      $$ = new Node(send_msg_node, yylineno);
      Node * id = new Node(hexLiteral_node, yylineno);
      Node * var = new Node (identifier_node, yylineno);
      var->setString($3);

      id->setInt($2);

      $$->addChild(id);
      $$->addChild(var);
  }
  | send_msg identifier identifier {
      $$ = new Node(send_msg_node, yylineno);
      Node * var = new Node (identifier_node, yylineno);
      Node * var1 = new Node (identifier_node, yylineno);
      var->setString($2);
      var1->setString($3);

      $$->addChild(var);
      $$->addChild(var1);
  };


ReadMsgCall:
  read_msg hexLiteral  {
      $$ = new Node(read_msg_node, yylineno);
      Node * id = new Node(hexLiteral_node, yylineno);
      id->setInt($2);
      $$->addChild(id);
  }
  | read_msg identifier {
      $$ = new Node(read_msg_node, yylineno);
      Node * var = new Node(identifier_node, yylineno);
      var->setString($2);
      $$->addChild(var);
  };



ReadPinCall:
  read_pin ain integerLiteral {
      $$ = new Node(analog_read, yylineno);
      Node * pin = new Node(integerLiteral_node, yylineno);
      pin->setInt($3);
      $$->addChild(pin);
  }
  | read_pin ain identifier {
      $$ = new Node(analog_read, yylineno);
      Node * var = new Node(identifier_node, yylineno);
      var->setString($3);
      $$->addChild(var);
  }
  | read_pin din integerLiteral {
      $$ = new Node(digital_read, yylineno);
      Node * pin = new Node(integerLiteral_node, yylineno);
      pin->setInt($3);
      $$->addChild(pin);
  }
  | read_pin din identifier {
      $$ = new Node(digital_read, yylineno);
      Node * var = new Node(identifier_node, yylineno);
      var->setString($3);

      $$->addChild(var);
  };

SetAnalogTail:
  integerLiteral identifier { 
      $$ = new Node(analog_write, yylineno);
      Node * pin = new Node(integerLiteral_node, yylineno);
      Node * var = new Node(identifier_node, yylineno);
      var->setString($2);
      pin->setInt($1);

      $$->addChild(pin);
      $$->addChild(var);
  }
  | identifier identifier  {
      $$ = new Node(analog_write, yylineno);
      Node * var = new Node(identifier_node, yylineno);
      Node * var1 = new Node(identifier_node, yylineno);
      
      var->setString($1);
      var->setString($2);

      $$->addChild(var);
      $$->addChild(var1);
  }
  | identifier integerLiteral {
      $$ = new Node(analog_write, yylineno);
      Node * value = new Node(integerLiteral_node, yylineno);
      Node * var = new Node(identifier_node, yylineno);
      var->setString($1);
      value->setInt($2);

      $$->addChild(var);
      $$->addChild(value);
  }
  | integerLiteral integerLiteral {
      $$ = new Node(analog_write, yylineno);
      Node * pin = new Node(integerLiteral_node, yylineno);
      Node * value = new Node(integerLiteral_node, yylineno);
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
      $$ = new Node(digital_write, yylineno);
      Node * pin = new Node(integerLiteral_node, yylineno);
      pin->setInt($4);
      $$->addChild(pin);
  }
  | set_pin dout identifier dstate {
      $$ = new Node(digital_write, yylineno);
      Node * var = new Node(identifier_node, yylineno);
      var->setString($3);

      $$->setInt($4);
      
      $$->addChild(var);
  } ;



DelayCall:
  delay Exp {
      $$ = new Node(delay_node, yylineno);
      $$->addChild($2);
  };


LoopCall:
  loop identifier '{' StatementList '}' {
      $$ = new Node(loop_node, yylineno);
      Node * var = new Node(identifier_node, yylineno);

      var->setString($2);

      $$->addChild(var);
      $$->addChild($4);
  }
  | loop integerLiteral '{' StatementList '}' {
      $$ = new Node(loop_node, yylineno);
      Node * times = new Node(integerLiteral_node, yylineno);
      times->setInt($2);
      $$->addChild(times);
      $$->addChild($4);
  }
  | loop forever '{' StatementList '}' {
      $$ = new Node(loop_node, yylineno);
      Node * times = new Node(forever_node, yylineno);
      $$->addChild(times);
      $$->addChild($4);
  };

Statement: error ';' {
    errors++;
    yyerrok;
    yyclearin;
  }
  |
  VariableDecl{
      $$ = $1;
  }
  | call stringLiteral ';' {
      $$ = new Node(call_node, yylineno);
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
      $$ = new Node(serial_tx, yylineno);
      $$->addChild($2);
  }
  | serialRx ';' {
      $$ = new Node(serial_rx, yylineno);
  }
  | exit_tok ';' {
      $$ = new Node(exit_node, yylineno);
  }
  | exit_tok stringLiteral ';' {
      $$ = new Node(exit_node, yylineno);
      $$->setString($2);
  };


%%


void yyerror(const char * err)
{
  printf( "%s on line %d\n", err, yylineno);
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



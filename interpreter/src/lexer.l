%{
  #include "parser.h"
  #include <stdio.h>
  #include <string>
  #include <iostream>
  #define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}

%option noyywrap
%option yylineno

%%

[\n] {}
[\t] {}

"//"[^\n]* {
  // double slash comment
}  
"#"[^\n]*  {
  // # comment
}

prompt { // this syntax allows for case insensitivity
  return prompt;
}

perrint|print {
  return perrint;
}

perrintln|println {
  return perrintln;
}

expect {
  return expect;
}

assert {
  return assert;
}

exit {
  return exit_tok;
}

read\-msg {
  return read_msg;
}

send\-msg {
  return send_msg;
}

read\-pin {
  return read_pin;
}

set\-pin {
  return set_pin;
}


delay {
  return delay;
}

routine {
  return routine;
}

test {
  return test;
}

loop {
  return loop;
}

call {
  return call;
}

forever {
  return forever;
}

AOUT {
  return aout;
}

AIN {
  return ain;
}

DOUT {
  return dout;
}

DIN {
  return din;
}

serial\-tx {
  return serialTx;
}

serial\-rx {
  return serialRx;
}

and|"&&" {
  yylval.str = new std::string(yytext);
  return andToken;
}

or|"||" {
  yylval.str = new std::string(yytext);
  return orToken;
}

HIGH {
  yylval.i = 1;
  return dstate;
}

LOW { 
  yylval.i = 0;
  return dstate;
}


(NE)|"!=" {
  yylval.str = new std::string("NE");
  return NE;
}

(EQ)|"==" {
  yylval.str = new std::string("EQ");
  return EQ;
}

"if" {
  return If;
}

"else" {
  return Else;
}

(GT)|(LT)|(GE)|(LE)|">="|"<"|"<="|">" {
  yylval.str = new std::string(yytext);
  return comparison;
}

"--" {
  return minusminus;
}

"++" {
  return plusplus;
}

length {
  return length;
}

(\"([^"\\]|\\.)*\")|(\'([^'\\]|\\.)*\')   {
  /* quoted string */
  std::string s = yytext;
  if (s.find("\"") == 0)
  {
    while (s.find("\"") != std::string::npos)
    {
      s.erase(s.find("\""), 1);
    }
  }
  else if (s.find("'") == 0)
  {
    while (s.find("'") != std::string::npos)
    {
      s.erase(s.find("'"), 1);
    }
  }


  yylval.str = new std::string(s);

  return stringLiteral;
}

[0-9]+ {
  yylval.i = std::stoi(yytext);
  return integerLiteral;
}

0[Xx]([0-9AaBbCcDdEeFf])+ {
  yylval.i = std::stoul(yytext, 0, 16);
  return hexLiteral;
}

([0-9AaBbCcDdEeFf][0-9AaBbCcDdEeFf]?)(\|[0-9AaBbCcDdEeFf][0-9AaBbCcDdEeFf]?){0,7} {
  yylval.str = new std::string(yytext);
  return can_msg;
}

[\*/] {
  yylval.str = new std::string(yytext);
  return mult;
}

[+-] {
  yylval.str = new std::string(yytext);
  return add;
}

[a-zA-Z_][0-9a-zA-Z_]*+ { 
  /* capture any grouping of alpha numeric characters and assume 
                   it to be an Identifier */
  yylval.str = new std::string(yytext);
  return identifier;
}

[={}\[\]()!\.,;\|] {
  return *yytext;
}


%%
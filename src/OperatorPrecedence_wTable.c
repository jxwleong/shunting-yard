#include "OperatorPrecedence_wTable.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"

#define STRONGEST 2
#define WEAKEST   1

OperatorPrecedence bindingPower[50] = {
  ['+'] = {.bindingPower = WEAKEST},
  ['-'] = {.bindingPower = WEAKEST},
  ['*'] = {.bindingPower = STRONGEST},
  ['/'] = {.bindingPower = STRONGEST}
};

OperatorPrecedence *getTokenPrecedence(Token *token){
  char operatorSymbol;
  operatorSymbol = *((OperatorToken*)token)->str;

  if(operatorSymbol == '+'){
    return &bindingPower['+'];
  }
  else if(operatorSymbol == '-'){
    return &bindingPower['-'];
  }
  else if(operatorSymbol == '*'){
    return &bindingPower['*'];
  }
  else if(operatorSymbol == '/'){
    return &bindingPower['/'];
  }
  else{
    throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator detected");
  }
}

// Example
//
//     operatorStack
//            +-----+
//  tail-->   +  *  + <---
//            +-----+    | next
//            +  -  +  __|
//            +-----+
//      head----^
//   *For this example expect return '0'
//   i) next(tail) operator precedence is higher return 0
//  ii) current(head) operator precedence is higer return 1
// iii) both operator precedence are same return 2
int comparePrevTokenAndNextTokenPrecedence(Tokenizer *tokenizer, Token *prevToken){
  Token *nextToken;

  OperatorPrecedence *precedenceOfprevToken;
  OperatorPrecedence *precedenceOfnextToken;

  nextToken = getToken(tokenizer);

  precedenceOfprevToken = getTokenPrecedence(prevToken);
  precedenceOfnextToken = getTokenPrecedence(nextToken);

  pushBackToken(tokenizer, nextToken);

  if((precedenceOfprevToken->bindingPower) > (precedenceOfnextToken)->bindingPower){
    return 1;
  }
  else if ((precedenceOfprevToken->bindingPower) < (precedenceOfnextToken)->bindingPower){
    return 0;
  }
  else{
    return 2;
  }
}

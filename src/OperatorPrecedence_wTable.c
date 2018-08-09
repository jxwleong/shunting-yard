#include "OperatorPrecedence_wTable.h"
#include "TokenInfo_AffixTable_wEvaluation.h"
#include "Token.h"
#include "Tokenizer.h"
#include "TokenAffix.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"

#define STRONG 3
#define MEDIUM 2
#define WEAK   1

OperatorPrecedence bindingPower[50] = {
  [INFIX_PLUS] = {.bindingPower = WEAK},
  [INFIX_MINUS] = {.bindingPower = WEAK},
  [INFIX_MULTIPLY] = {.bindingPower = MEDIUM},
  [INFIX_DIVIDE] = {.bindingPower = MEDIUM},
  [PREFIX_PLUS] = {.bindingPower = STRONG},
  [PREFIX_MINUS] = {.bindingPower = STRONG},
  [OPEN_BRACKET] = {.bindingPower = WEAK},
  [CLOSE_BRACKET] = {.bindingPower = WEAK},
};

OperatorPrecedence *getTokenPrecedence(Token *token){
  Affix tokenAffix;
  tokenAffix = getAffix(token);
  char operatorSymbol;
  operatorSymbol = *((OperatorToken*)token)->str;

  switch(tokenAffix){
    case PREFIX :    if(operatorSymbol == '+'){
                      return &bindingPower[PREFIX_PLUS];
                     }
                     else if(operatorSymbol == '-'){
                      return &bindingPower[PREFIX_MINUS];
                     }

    case SUFFIX :
    case INFIX  :    if(operatorSymbol == '+'){
                      return &bindingPower[INFIX_PLUS];
                     }
                     else if(operatorSymbol == '-'){
                      return &bindingPower[INFIX_MINUS];
                     }
                     else if(operatorSymbol == '*'){
                      return &bindingPower[INFIX_MULTIPLY];
                     }
                     else if(operatorSymbol == '/'){
                      return &bindingPower[INFIX_DIVIDE];
                     }

      default:  throwException(ERR_INVALID_OPERATOR, token, "Invalid affix of '%c' operator", operatorSymbol);

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
int comparePrevTokenAndNextTokenPrecedence(Token *currToken, Token *prevToken){
  int compareAffixPossibilities;

  compareAffixPossibilities = checkOperatorTokensAffixPossibilities(prevToken, currToken);

  if(compareAffixPossibilities){
    OperatorPrecedence *precedenceOfprevToken;
    OperatorPrecedence *precedenceOfcurrToken;

    precedenceOfprevToken = getTokenPrecedence(prevToken);
    precedenceOfcurrToken = getTokenPrecedence(currToken);

    // operator->addtoHead > token
    if((precedenceOfprevToken->bindingPower) > (precedenceOfcurrToken)->bindingPower){
      return 1;
    } // operator->addtoHead < token
    else if ((precedenceOfprevToken->bindingPower) < (precedenceOfcurrToken)->bindingPower){
      return 0;
    }
    else{
      return 2;
    }
  }
  else{
    throwException(ERR_INVALID_OPERATOR, currToken ,"'%s' is not an operator", currToken->str);
  }

}

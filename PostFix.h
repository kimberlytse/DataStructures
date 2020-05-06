#ifndef POSTFIX_H_INCLUDED
#define POSTFIX_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define SIZE 200

/*
 *
 *  Two Stacks: StackNode   --> change inFix to postFix expression
 *                              --> uses array
 *                              --> cannot hold value >= 128 == 2^7
 *
 *                  PostNode    --> evaluate postFix expression
 *                              --> uses self-referential
 *                              --> can hold value >= 128 (very useful for evaluation)
 */

struct stackNode{
    char* expression;
    int top;

};

struct postNode{
    int data;
    struct postNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode* StackNodePtr;

typedef struct postNode PostNode;
typedef PostNode* PostNodePtr;

StackNodePtr CreateStack();
void push(StackNodePtr stk, char info);
char pop(StackNodePtr stk);
int isEmpty(StackNodePtr stk);
char peek(StackNodePtr stk);

void pushPost(PostNodePtr *topPtr, int info);
int popPost(PostNodePtr *topPtr);
int isPostEmpty(PostNodePtr topPtr);
void printPost(PostNodePtr currentPtr);

int isOperator(char c);
int precedence(char c);

char* Convert(char* inFix);
int EvaluatePost(char* postFix);


/*
 * StackNode Functions --> for conversion to postfix expression
 *      CreateStack    --> creates stack char array with set size constant of 200
 *      push           --> push the given character into the stack char array, top of stack goes up
 *      pop            --> pops the top of the stack char array, top of stack goes down
 *      isEmpty        --> sees if the stack char array is empty
 *      peek           --> returns top character of stack char array - useful for comparing precedence
 *
 */

StackNodePtr CreateStack(){

    StackNode* stk = malloc(sizeof(StackNode));

    if (stk == NULL){
        printf("No memory available.");
        return NULL;
    }

    stk->top = -1;                                          // "starting" point, the psuh function will start array at 0
    stk->expression = (char*)malloc(SIZE * sizeof(char));   // allocates memory inside expression for characters

    if (stk->expression == NULL){
        printf("No memory available.");
        return NULL;
    }

    return stk;
}

void push(StackNodePtr stk, char info){
    stk->expression[++(stk->top)] = info;

}

char pop(StackNodePtr stk){
    if(!isEmpty(stk)){
        return stk->expression[(stk->top)--];
    }
    return '_'; // pick any random character

}

int isEmpty(StackNodePtr stk){
    return stk->top == -1;
}

char peek(StackNodePtr stk){
    return stk->expression[stk->top];
}


/*
 * PostNode Functions  --> for evaluation (this is the normal stack)
 *      pushPost       --> push the given INTEGER into the stack, moves on to nextPtr
 *      popPost        --> pops the top INTEGER of the stack
 *      isPostEmpty    --> sees if the stack is empty
 *      printPost      --> prints out stack - for my reference to see if it stacks properly
 *
 */

void pushPost(PostNodePtr *topPtr, int info){
    PostNodePtr newPtr; // pointer to new node
    newPtr = malloc(sizeof(PostNodePtr));

    if(newPtr != NULL){
        newPtr->data = info;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    } else {
        printf("%d not inserted. No memory available.\n", info);

    }
}

int isPostEmpty(PostNodePtr topPtr){
    return topPtr == NULL;
}

int popPost(PostNodePtr *topPtr){

    PostNodePtr tempPtr; // temporary node pointer
    int popValue;

    tempPtr = *topPtr;
    popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);

    return popValue;
}

void printPost(PostNodePtr currentPtr){
    if(currentPtr == NULL){

        printf("The stack is empty.\n\n");

    } else {

        printf("The stack is:\n");
        while(currentPtr != NULL){
            printf("%d --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;

        }
    }
}

/*
 *      isOperator     --> determines whether the character is an operator or not
 *      precedence     --> determines precedence of operator (not including unary)
 *                          --> unary is a special case and will be addressed in
 *                              the Convert and Evaluate functions
 */

int isOperator(char c){
   if (c == '+' || c == '-' || c == '*' || c == '/'){
        return 1;

   }
   else{
        return 0;

   }
}


int precedence(char c){
   if(c == '+' || c == '-'){
        return 1;

   }
   else if(c == '*' || c == '/'){
        return 2;

   }
   else{
        return -1;

   }
}

/*
 *      Convert     --> converts the infix expression to postfix
 */

char* Convert(char* inFix){

    StackNodePtr stk = CreateStack();
    char* postFix = (char*)malloc((strlen(inFix)) * sizeof(char));

    char current;
    char next;
    int par = 0;    // if left parenthesis is present
    char c;         // temp holder for current
    int j = -1;

    for(int i = 0; i < strlen(inFix); i++){
        current = inFix[i];

        if(isdigit(current)){ // if current is operand
            postFix[++j] = current;

        } else if (current == '('){
            push(stk, current);
            par = 1;

        } else if(isOperator(current)){ // if current is operator

            if(current == '-' && isdigit(inFix[++i])){
                postFix[++j] = current;
                postFix[++j] = inFix[i];
            }

            else if(isEmpty(stk) || par == 1){ // if there is NOTHING in the stack OR if there is a left parentheses
                push(stk, current);
                postFix[++j] = ' ';

            } else{   // if there are no left parentheses and the stack is not empty

                while(!isEmpty(stk) && (precedence(peek(stk)) >= precedence(current))){
                    c = peek(stk);
                    pop(stk);
                    postFix[++j] = ' ';
                    postFix[++j] = c;

                }
                postFix[++j] = ' ';
                push(stk, current);
            }

        } else if (current == ')'){
            while(!isEmpty(stk) && peek(stk) != '('){
                c = peek(stk);
                pop(stk);
                postFix[++j] = ' ';
                postFix[++j] = c;

            }

            if(!isEmpty(stk) && peek(stk) == '('){
                pop(stk);
                par = 0;

            }
        }

    }

    while(!isEmpty(stk)){ // Emptying remaining of stack

        c = peek(stk);
        pop(stk);
        postFix[++j] = ' ';
        postFix[++j] = c;

    }

    postFix[++j] = '\0';
    return postFix;

}

/*
 *      Evaluate     --> evaluates the expression
 */

int EvaluatePost(char* postFix){

    PostNodePtr stk = NULL;
    char current;

    int num1;
    int num2;
    int num3;
    int sum;

    int x, y;
    /*
     * Iterative way of dealing with single / multi-digit values (this was a bit complicated to think of)
     */
    for(int i = 0; i < strlen(postFix); i++){
        current = postFix[i];
        if(isdigit(current)){
            num1 = atoi(&current);
            sum = num1;

            if(isdigit(postFix[++i])){ // Already moves to next as we put the ++i
                num2 = atoi(&(postFix[i]));
                sum = (10*num1) + num2;

                if(isdigit(postFix[++i])){ // Already moves to next as we put the ++i
                    num3 = atoi(&(postFix[i]));
                    sum = (100*num1) + (10*num2) + num3;

                }
            }
            //printf("\nSum: %d\n", sum);
            pushPost(&stk, sum);
           // printPost(stk);

        } else if(current == '-' && isdigit(postFix[++i])){ // special case of unary negation
            pushPost(&stk, (-1 * atoi(&(postFix[i]))));
            //printPost(stk);

        } else if (isOperator(current)){        // when we encounter a operator

            x = popPost(&stk);
            y = popPost(&stk);
          //  printPost(stk);

            switch(current){
                case '+':
                    pushPost(&stk, (y + x));
                   // printPost(stk);
                    break;

                case '-':
                    pushPost(&stk, (y - x));
                  //  printPost(stk);
                    break;

                case '*':
                    pushPost(&stk, (y * x));
                  //  printPost(stk);
                    break;

                case '/':
                    pushPost(&stk, (y / x));
                 //   printPost(stk);
                    break;

            }

        } else{                 // this part is not important, but I kept changing which ones were else / else-ifs in the code, so I left it alone.
            printf("");
        }
    }

    return popPost(&stk);
}


#endif // POSTFIX_H_INCLUDED

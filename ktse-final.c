/*
Kimberly Tse
Data Structures
Final Project
*/

#include "PostFix.h"

int main(){

    char inFixExpression[100];
    char *postFixExpression;
    int result;

    printf("Enter your expression: ");
    scanf("%[^\n]%*c", &inFixExpression); // "%[^\n]%*c" means it will take in anything until ENTER is inputted

    postFixExpression = Convert(inFixExpression);

    printf("\nInfix expression:\n%s\n\n", inFixExpression);
    printf("Postfix expression:\n%s\n\n", postFixExpression);

    result = EvaluatePost(postFixExpression);
    printf("Result =  %d\n", result);


    return 0;
}

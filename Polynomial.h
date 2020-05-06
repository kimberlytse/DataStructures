#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

struct polynomial{

    int coefficient;
    int power;
    struct polynomial *nextPtr;

};

typedef struct polynomial Polynomial;
typedef Polynomial *PolynomialPtr;

void instructions(void);

void Create(PolynomialPtr *eqPtr, int c, int p);
void PrintPolynomial(PolynomialPtr eqPtr);

double Evaluate(PolynomialPtr eqPtr, double x);
PolynomialPtr Add(PolynomialPtr p1, PolynomialPtr p2);
PolynomialPtr Subtract(PolynomialPtr p1, PolynomialPtr p2);
PolynomialPtr Multiply(PolynomialPtr p1, PolynomialPtr p2);
PolynomialPtr Differentiate(PolynomialPtr p);

void Create(PolynomialPtr *eqPtr, int c, int p){

    PolynomialPtr newPtr;
    PolynomialPtr previousPtr;
    PolynomialPtr currentPtr;

    newPtr = malloc(sizeof(Polynomial));

    if(newPtr != NULL){
        newPtr->coefficient = c;
        newPtr->power = p;
        newPtr->nextPtr = NULL;

        previousPtr = NULL;
        currentPtr = *eqPtr;

        while(currentPtr != NULL && p < currentPtr->power){ // loops till currentPtr hits NULL
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if(previousPtr == NULL){
            newPtr->nextPtr = *eqPtr;
            *eqPtr = newPtr;
        } else {
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }

    } else {

        printf("No memory available.\n");

    }

}

void PrintPolynomial(PolynomialPtr eqPtr){

    printf("Polynomial: ");
    while(eqPtr!=NULL){

        printf("(%d)x^%d + ", eqPtr->coefficient, eqPtr->power);
        eqPtr = eqPtr->nextPtr;

    }

    printf("0 \n");

}

double Evaluate(PolynomialPtr eqPtr, double x){

    double sum = 0;

    if(eqPtr == NULL){
        return sum;

    } else{

        while(eqPtr != NULL){
            sum += (eqPtr->coefficient)*pow(x, (eqPtr->power));
            eqPtr = eqPtr->nextPtr;
        }
        return sum;
    }


}

PolynomialPtr append(PolynomialPtr thead,int c,int e)
{
    PolynomialPtr newnode = (PolynomialPtr)malloc(sizeof(Polynomial));
    newnode->coefficient=c;
    newnode->power=e;

    if(thead==NULL){// Corner Case to handle if the list is empty...
        newnode->nextPtr=NULL;
        return newnode;
    }

    PolynomialPtr trav = thead;

    while(trav->nextPtr !=NULL) // Traversing to point to the last node...
        trav = trav->nextPtr;
        trav->nextPtr=newnode;
        newnode->nextPtr=NULL;
        return thead;
}

PolynomialPtr Add(PolynomialPtr p1, PolynomialPtr p2){

    PolynomialPtr head = NULL;
    PolynomialPtr t1, t2;
    t1 = p1;
    t2 = p2;

    while(t1!=NULL && t2!=NULL){
        if(t1->power > t2->power){
            head = append(head, t1->coefficient, t1->power);
            t1=t1->nextPtr;
        }
        else if(t1->power < t2->power){
            head = append(head, t2->coefficient, t2->power);
            t2=t2->nextPtr;
        }
        else{
            head = append(head,(t1->coefficient)+(t2->coefficient),t1->power);
            t1=t1->nextPtr;
            t2=t2->nextPtr;
        }
    }

    while(t1!=NULL){
        head = append(head, t1->coefficient, t1->power);
        t1=t1->nextPtr;
    }

    while(t2!=NULL){
        head = append(head, t2->coefficient, t2->power);
        t2=t2->nextPtr;
    }
    return head;

}

PolynomialPtr Subtract(PolynomialPtr p1, PolynomialPtr p2){

    PolynomialPtr head = NULL;
    PolynomialPtr t1, t2;
    t1 = p1;
    t2 = p2;

    while(t1!=NULL && t2!=NULL){
        if(t1->power > t2->power){
            head = append(head, t1->coefficient, t1->power);
            t1=t1->nextPtr;
        }
        else if(t1->power < t2->power){
            head = append(head,(-1) * (t2->coefficient), t2->power);
            t2=t2->nextPtr;
        }
        else{
            head = append(head,(t1->coefficient)-(t2->coefficient),t1->power);
            t1=t1->nextPtr;
            t2=t2->nextPtr;
        }
    }

    while(t1!=NULL){
        head = append(head, t1->coefficient, t1->power);
        t1=t1->nextPtr;
    }

    while(t2!=NULL){
        head = append(head, t2->coefficient, t2->power);
        t2=t2->nextPtr;
    }
    return head;


}

PolynomialPtr Multiply(PolynomialPtr p1, PolynomialPtr p2){

    PolynomialPtr head = NULL;
    PolynomialPtr t1, t2;
    t1 = p1;
    t2 = p2;

    while(t1!=NULL){
        while(t2 != NULL){
            head = append(head, (t1->coefficient) * (t2->coefficient), (t1->power) * (t2->power));
            t2 = t2->nextPtr;

        }
        t2 = p2;
        t1 = t1->nextPtr;
    }

    return head;

}

PolynomialPtr Differentiate(PolynomialPtr p){

    PolynomialPtr head = NULL;
    PolynomialPtr t1 = p;

    while(t1 != NULL){
        head = append(head, t1->coefficient * t1->power, t1->power - 1);
        t1 = t1->nextPtr;
    }

    return head;

}

void instructions(void){
    printf("Project Polynomial:\n"
        "\n\t1 to insert a polynomial into the equation"
        "\n\t2 to print current polynomial equation"
        "\n\t3 to end.\n\n");
}




#endif // POLYNOMIAL_H_INCLUDED

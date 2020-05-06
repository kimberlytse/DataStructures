/*
Kimberly Tse
Data Structures
Project 2
*/

#include "Polynomial.h"

int main(){

    PolynomialPtr m_Ptr = NULL;
    PolynomialPtr n_Ptr = NULL;
    PolynomialPtr newton_Ptr = NULL;
    PolynomialPtr newtonPrime_Ptr = NULL;

    PolynomialPtr sum_Ptr;
    PolynomialPtr subtract_Ptr;
    PolynomialPtr product_Ptr;
    PolynomialPtr dif_Ptr;

    int choice;
    int coef;
    int pwr;

    double x;

    /*************************************************************/
                        /*Testing Functions*/
    printf("***Testing Functions***\n\n");
    instructions();

    printf("\tTestPtr 1: What would you like to do (1, 2, or 3)? ");
    scanf("\n%d", &choice);

    while(choice != 3){ // first testPtr

        switch(choice){

            case 1:
                printf("\tEnter coefficient: ");
                scanf("%d", &coef);
                printf("\tEnter power of polynomial: ");
                scanf("%d", &pwr);
                Create(&m_Ptr, coef, pwr);
                break;

            case 2:
                printf("\t");
                PrintPolynomial(m_Ptr);
                break;

            default:
                printf("\tInvalid option.\n");
                break;

        }

            printf("\tWhat would you like to do (1 or 2 or 3)?");
            scanf("\n%d", &choice);

    }

    printf("\n\tTestPtr 2: What would you like to do (1, 2, or 3)? ");
    scanf("\n%d", &choice);

    while(choice != 3){ // second testPtr

        switch(choice){

            case 1:
                printf("\tEnter coefficient: ");
                scanf("%d", &coef);
                printf("\tEnter power of polynomial: ");
                scanf("%d", &pwr);
                Create(&n_Ptr, coef, pwr);
                break;

            case 2:
                printf("\t");
                PrintPolynomial(n_Ptr);
                break;

            default:
                printf("\tInvalid option.\n");
                break;

        }

            printf("\tWhat would you like to do (1 or 2 or 3)?");
            scanf("\n%d", &choice);

    }

    printf("\tYour two polynomials are...\n");
    printf("\t");
    PrintPolynomial(m_Ptr);
    printf("\t");
    PrintPolynomial(n_Ptr);

    printf("\n");
    PrintPolynomial(m_Ptr);
    printf("\tGiven this equation, what is 'x'? ");
    scanf("\n%lf", &x);

    printf("\tAt %.1lf, the polynomial solution is: %.5lf\n\n", x, Evaluate(m_Ptr, x));

    sum_Ptr = Add(m_Ptr, n_Ptr);
    printf("\tAdding the two polynomials: \n");
    PrintPolynomial(sum_Ptr);

    subtract_Ptr = Subtract(m_Ptr, n_Ptr);
    printf("\n\tSubtracting TestPtr 2 from TestPtr 1: \n");
    PrintPolynomial(subtract_Ptr);

    printf("\n\tMultiplying both polynomials: \n");
    product_Ptr = Multiply(m_Ptr, n_Ptr);
    PrintPolynomial(product_Ptr);

    printf("\n\tDifferentiating TestPtr 1: \n");
    dif_Ptr = Differentiate(m_Ptr);
    PrintPolynomial(dif_Ptr);

    /*************************************************************/
    /*Polynomial to be tested: x^5 - 6x^4 + 8x^3 + 8x^2 + 4x - 4 */
    /*Root: 0.455555555.....*/

    printf("\n\n***Application: Newton-Rhapson Method***\n");

    Create(&newton_Ptr, 1, 5);
    Create(&newton_Ptr, -6, 4);
    Create(&newton_Ptr, 8, 3);
    Create(&newton_Ptr, 8, 2);
    Create(&newton_Ptr, 4, 1);
    Create(&newton_Ptr, -4, 0);
    newtonPrime_Ptr = Differentiate(newton_Ptr);

    printf("\t");
    PrintPolynomial(newton_Ptr);

    double start;
    double prev;
    double soln;

    printf("\n\tWe will find the root of this equation using the Newton-Rhapson Method."
           "\n\tChoose a starting number: ");
    scanf("%lf",  &start);

    do{
        prev = start;
        soln = start - (Evaluate(newton_Ptr, start) / Evaluate(newtonPrime_Ptr, start));
        start = soln;
        printf("Num: %lf\n", start);

    } while (fabs(soln - prev) >= .001);

    printf("\tSolution to this polynomial is: %lf\n", start);

    return 0;

}

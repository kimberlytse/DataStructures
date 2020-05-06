/*
Kimberly Tse
Data Structures
Project 1
*/

#include "String.h"

char a[] = "hello";
char b[] = "hi!";


int main(){

    printf("** Begin implementation of each function. **\n\n");

    printf("\nCreate and print strings...\n");
    string_type st1 = Create(a, 5);
    string_type st2 = Create(b, 3);

    Print(st1);
    Print(st2);

    printf("\nComparing strings...\n");
    Compare(st1, st2);
    Compare(st2, st1);

    printf("\nFinding strings lengths...\n");
    printf("Length: %d\n", Length(st1));
    printf("Length: %d\n", Length(st2));

    printf("\nConcatenate strings...\n");
    Print(Concatenate(st2, st1));
    Print(Concatenate(st1, st2));

    printf("\nRetrieving the element of strings given index number...\n");
    printf("Character: %c\n", Retrieve(1, st1));
    printf("Character: %c\n", Retrieve(2, st2));

    Destroy(&st2);
    Print(st2);

    printf("\n** End implementation of each function. **\n\n");

    /*********************************************************/

    printf("** Sorting numerous strings lexicographically. **\n\n");

    string_type str[17];
    string_type temp;

    int a, b;

    str[0] = Create("defunct", sizeof("defunct"));
    str[1] = Create("abeyance", sizeof("abeyance"));
    str[2] = Create("irrelevant", sizeof("irrelevant"));
    str[3] = Create("acquiesce", sizeof("acquiesce"));
    str[4] = Create("western", sizeof("western"));
    str[5] = Create("zealous", sizeof("zealous"));
    str[6] = Create("electric", sizeof("electric"));
    str[7] = Create("trihedral", sizeof("trihedral"));
    str[8] = Create("unimodal", sizeof("unimodal"));
    str[9] = Create("vanquish", sizeof("vanquish"));
    str[10] = Create("ambient", sizeof("ambient"));
    str[11] = Create("abbreviate", sizeof("abbreviate"));
    str[12] = Create("edifice", sizeof("edifice"));
    str[13] = Create("genre", sizeof("genre"));
    str[14] = Create("ferrous", sizeof("ferrous"));
    str[15] = Create("breve", sizeof("breve"));
    str[16] = Create("brocade", sizeof("brocade"));

    printf("BEFORE sorting...\n");
    for(a = 0; a < 17; a++){

        Print(str[a]);

    }

    printf("\n\n");

    for(a = 0; a < 17; a++){
        for(b = a + 1; b < 17; b++){

            if(Compare(str[a], str[b]) == 0){

                (&temp)->element = (&str[a])->element;
                (&str[a])->element = (&str[b])->element;
                (&str[b])->element = (&temp)->element;

            }

        }
    }

    printf("\n\n");
    printf("AFTER sorting...\n");

    for(a = 0; a < 17; a++){

        Print(str[a]);

    }

    printf("\n** End sorting of numerous strings Exit Program. **\n\n");

    //return 0;
}

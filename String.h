#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>


typedef struct {

    char *element;
    int length;
    int capacity;

} string_type;


string_type Create(char *arr, int strLength);//
string_type Concatenate(string_type s1, string_type s2);//

char Retrieve(int i, string_type str);//
void Print(string_type str);//
void Copy(string_type s1, string_type s2);//

int Compare(string_type s1, string_type s2);
int Length(string_type s1);//
int Capacity(string_type s1);//

void Destroy(string_type *str); //

string_type Create(char *arr, int strLength){

    string_type *newStr = NULL;
    newStr = malloc(sizeof(string_type));

    if(newStr != NULL){

        newStr->length = strLength;
        newStr->element = arr;
        newStr->capacity = strLength;

    } else{

        printf("No memory available.\n");

    }

    return *newStr;
}

void Print(string_type str){

    if((&str == NULL) || (&str)->element == NULL){

        printf("String is empty.\n");

    } else {

        printf("String: %s\n", (&str)->element);

    }
}

string_type Concatenate(string_type s1, string_type s2){

    char newArray[] = "";
    int newLength;
    string_type newStr;


    strcat(newArray, (&s1)->element);
    strcat(newArray, (&s2)->element);

    newStr = Create(newArray, (&s1)->length + (&s2)->length);

    return newStr;

}

int Compare(string_type s1, string_type s2){

    int determine = strcmp((&s1)->element, (&s2)->element);


    if(determine < 0){

        printf("First string is less than or equal to second string.\n");
        return 1;

    } else {

        printf("First string is more than second string.\n");
        return 0;

    }

}

void Copy(string_type s1, string_type s2){

    strcpy((&s2)->element, (&s1)->element);

}

char Retrieve(int i, string_type str){

    char *index = (&str)->element + i;
    char elementL = *index;

    return elementL;

}

int Length(string_type s1){

    return (&s1)->length;

}

int Capacity(string_type s1){

    return (&s1)->capacity;

}

void Destroy(string_type *str){
    printf("Destroying string...\n");
    str->element = '\0';
}

#endif // STRING_H_INCLUDED

//NODE_PROGRAM
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){
//NODE_DECLARATION
int var9;
//NODE_DECLARATION
int var11;
//NODE_DECLARATION
float var13;
//NODE_DECLARATION
int var15[2];
//NODE_COMPOUND_STATEMENT
//NODE_ASSIGNMENT
//NODE_IVALUE
int t0 = 1;
var9 = t0;
//NODE_ASSIGNMENT
//NODE_RVALUE
float t1 = 3.140000;
var11 = t1;
//NODE_ASSIGNMENT
//NODE_EXPRESSION
//NODE_VARIABLE
int t2 = var9;
//NODE_EXPRESSION
//NODE_IVALUE
int t3 = 2;
//NODE_VARIABLE
int t4 = var11;
float t5 = t3 * t4;
float t6 = t2 - t5;
var11 = t6;
//NODE_ASSIGNMENT
//NODE_IVALUE
int t7 = 1;
//NODE_VARIABLE
int t8 = var9;
var15[t8] = t7;
//NODE_IVALUE
int t9 = 2;
var15[t9] = t7;
//NODE_IVALUE
int t10 = 3;
var15[t10] = t7;
//NODE_ASSIGNMENT
//NODE_ARRAY
//NODE_VARIABLE
int t11 = var9;
int t12 = var15[t11];
var13 = t12;
//NODE_WRITELN
//NODE_IVALUE
int t13 = 1;
printf("%d\n", t13);
//NODE_VARIABLE
float t14 = var13;
printf("%.2f\n", t14);
//NODE_READLN
float t15;
scanf("%f", &t15);
var13 = t15;
//NODE_WRITELN
//NODE_VARIABLE
float t16 = var13;
printf("%.2f\n", t16);
return 1;
}
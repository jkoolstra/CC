#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){
	int var12;
	int var14;
	int var16;
	int var19;
	float var23;
	float var25[2];
	float t0 = 25.299999;
	int t1 = 2;
	int t2 = t1 - 1;//Update idx
	var25[t2] = t0;
	int t3 = 3;
	int t4 = t3 - 1;//Update idx
	var25[t4] = t0;
	int t5 = 42;
	var12 = t5;
	int t6 = 1;
	int t7 = 1;
	int t8 = t6 * t7;
	var14 = t8;
	int t9 = var12;
	int t10 = var14;
	float t11 = t9 * t10;
	var16 = t11;
	int t12 = 1;
	int t13 = 1;
	int t14 = var12;
	float t15 = t13 * t14;
	int t16 = t12 * t15;
	int t17 = 1;
	int t18 = var16;
	int t19 = t17 * t18;
	int t20 = t16 + t19;
	var19 = t20;
	int t21 = 1;
	int t22 = var12;
	int t23 = t21 * t22;
	int t24 = var12;
	int t25 = t23 - t24;
	var12 = t25;
	int t26 = 2;
	int t27 = t26 - 1;//Update idx
	float t28 = var25[t27];
	var23 = t28;
	float t29 = var23;
	printf("%.2f\n", t29);
	float t30;
	scanf("%f", &t30);
	int t31 = 1;
	int t32 = t31 - 1;//Update idx
	var25[t32] = t30;
	float t33;
	scanf("%f", &t33);
	int t34 = 2;
	int t35 = t34 - 1;//Update idx
	var25[t35] = t33;
	int t36 = 1;
	int t37 = t36 - 1;//Update idx
	float t38 = var25[t37];
	printf("%.2f\n", t38);
	int t39 = 2;
	int t40 = t39 - 1;//Update idx
	float t41 = var25[t40];
	printf("%.2f\n", t41);
	return 1;
}
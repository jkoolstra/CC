#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){
	int var18;
	int var20;
	int var22;
	int var24;
	int t0;
	scanf("%d", &t0);
	var18 = t0;
	int t1;
	scanf("%d", &t1);
	var20 = t1;
	int t2;
	scanf("%d", &t2);
	var22 = t2;
lb0: ;
	int t3 = var18;
	int t4 = var20;
	int t5 = t3 > t4;
	if(!t5) goto lb1;
	int t6 = var18;
	var24 = t6;
	int t7 = var20;
	var18 = t7;
	int t8 = var24;
	var20 = t8;
	goto lb0;
lb1: ;
lb2: ;
	int t9 = var18;
	int t10 = var22;
	int t11 = t9 > t10;
	if(!t11) goto lb3;
	int t12 = var18;
	var24 = t12;
	int t13 = var22;
	var18 = t13;
	int t14 = var24;
	var22 = t14;
	goto lb2;
lb3: ;
lb4: ;
	int t15 = var20;
	int t16 = var22;
	int t17 = t15 > t16;
	if(!t17) goto lb5;
	int t18 = var20;
	var24 = t18;
	int t19 = var22;
	var20 = t19;
	int t20 = var24;
	var22 = t20;
	goto lb4;
lb5: ;
	int t21 = var18;
	int t22 = var20;
	int t23 = t21 + t22;
	int t24 = var22;
	int t25 = t23 <= t24;
	if(!t25) goto lb6;
	int t26 = 0;
	printf("%d\n", t26);
	goto lb7;
lb6: ;
	int t27 = var18;
	int t28 = var18;
	float t29 = t27 * t28;
	int t30 = var20;
	int t31 = var20;
	float t32 = t30 * t31;
	float t33 = t29 + t32;
	int t34 = var22;
	int t35 = var22;
	float t36 = t34 * t35;
	int t37 = t33 < t36;
	if(!t37) goto lb7;
	int t38 = 2;
	printf("%d\n", t38);
	goto lb8;
lb7: ;
	int t39 = var18;
	int t40 = var18;
	float t41 = t39 * t40;
	int t42 = var20;
	int t43 = var20;
	float t44 = t42 * t43;
	float t45 = t41 + t44;
	int t46 = var22;
	int t47 = var22;
	float t48 = t46 * t47;
	int t49 = t45 > t48;
	if(!t49) goto lb8;
	int t50 = 3;
	printf("%d\n", t50);
	goto lb9;
lb8: ;
	int t51 = 1;
	printf("%d\n", t51);
lb9: ;
lb10: ;
lb11: ;
	return 1;
}
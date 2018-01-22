#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){
	int var0;
	int t0 = 0;
	var0 = t0;
lb0: ;
	int t1 = var0;
	int t2 = 10;
	int t3 = t1 < t2;
	if(!t3) goto lb1;
	int t4 = var0;
	int t5 = 1;
	int t6 = t4 + t5;
	var0 = t6;
	goto lb0;
lb1: ;
	int t7 = var0;
	printf("%d\n", t7);
	return 1;
}

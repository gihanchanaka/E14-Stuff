#include <stdio.h>

int main(){
	int a=10;
	void *p=&a;
	printf("%f \n",*((float*)(p)));
	printf("%.100f ",*((float*)(p)));



	return 0;
}

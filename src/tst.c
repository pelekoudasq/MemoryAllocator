#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"


int main(void){
	int *ptr, *ptr1, *ptr2, *ptr3, *ptr4;
	int x;
	x=32000;
	ptr = (int *)mymalloc(x);
	printf("Address returned = %p\n", ptr);
	x=4096;
	ptr1 = (int *)mymalloc(x);
	printf("Address returned = %p\n", ptr1);
	x=4095;
	ptr2 = (int *)mymalloc(x);
	printf("Address returned = %p\n", ptr2);
	x=4000;
	ptr3 = (int *)mymalloc(x);
	printf("Address returned = %p\n", ptr3);
	/*x=64;
	ptr = (int *)mymalloc(x);
	printf("Address returned= %p\n", ptr);
	x=128;
	ptr = (int *)mymalloc(x);
	printf("Address returned= %p\n", ptr);
	x=2000;
	ptr = (int *)mymalloc(x);
	printf("Address returned= %p\n", ptr);
	x=1000;
	ptr2 = (int *)mymalloc(x);
	printf("Address returned= %p\n", ptr);
	x=1003;
	ptr3 = (int *)mymalloc(x);
	printf("Address returned= %p\n", ptr3);
	x=1022;
	ptr = (int *)mymalloc(x);
	printf("Address returned= %p\n", ptr2);
	int x1=5000;
	ptr1 = (int *)mymalloc(x1);
	printf("Address returned= %p\n", ptr1);*/
	myfree(ptr);
	myfree(ptr1);
	myfree(ptr2);
	myfree(ptr3);
	ptr4 = (int *)mymalloc(x);
	printf("Address returned = %p\n", ptr4);
	myfree(ptr4);
	return 0;
}

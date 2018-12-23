//#include "fns.c"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


//Domi gia bitmpa klp
typedef struct list {
	
	char *bitmap;
	void *selida;
	struct list *next;
	
} Domi;

//Hash table/ hash list

typedef struct hashlist{
	
	Domi * NodeDomis;
	int klasi;
	struct hashlist *next;

}hashlist;

typedef hashlist **hashtable;

void *mymalloc(size_t cbytes);

void newNodeDomis(Domi **L, int bit_vector_size, int klasi);

void allocateOneMegabyte();

void *lookForZero(Domi **L, int bit_vector_size, int klasi);

void myfree(void* ad);

int ipow(int base, int exp);

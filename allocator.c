#include "allocator.h"


//global variables
static void *arxi=NULL;
static void *telos=NULL;
static Domi *evretirio[7];



hashtable htable=NULL; 

int ipow(int base, int exp)			//taken from:	https://stackoverflow.com/a/101613
{									//integer based power function, that math.h library doesn't offer
    int result = 1;					//give credit where credit's due
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

//function to allocate one megabyte, using the global variables arxi, telos
void allocateOneMegabyte(){
	
	void *extra=NULL;
	void *num=NULL;
	
	arxi=malloc(1024*1024);
	telos=arxi+(1024*1024);
	//nea arxi
	num=(void*)((long)arxi%4096);
	extra=(void*)(4096-(long)num);
	arxi=(void*)((long)arxi+(long)extra);
	//neo telos
	num=(void*)(4096-(long)extra);
	telos=(void*)((long)telos-(long)num);
	//printf("Address arxi = %p\n", arxi);
	//printf("Address telos = %p\n", telos);
	return;

}


void newNodeDomis(Domi **L, int bit_vector_size, int klasi){

	Domi *N;
	
	if (bit_vector_size<1){
		bit_vector_size=1;
	}
	
	//allocate node Domis
	N=(Domi *)malloc(sizeof(Domi));
	N->next=NULL;
	
	//if whole pool is empty (or no pool==first call of mymalloc)
	if (arxi==telos){
		allocateOneMegabyte();
	}
	
	N->selida=arxi;
	arxi=(void*)((long)arxi+4096);
	//printf("Address nea arxi (new node Domis)= %p\n", arxi);
	
	//malloc array accordingly to the class
	N->bitmap=(char *)malloc(bit_vector_size);
	for (int i=0; i<bit_vector_size; i++){
		N->bitmap[i]=0;
	}
	
	//first bit 1
	char temp;
	temp=1;
	temp=temp<<7;
	N->bitmap[0]=N->bitmap[0]|temp;
	
	*L=N;
	
	//position for hash table
	int thesi=((unsigned int)(N->selida)/4096)%8093;
	
	//assign in hash
	if(htable==NULL)
	{
		htable = calloc(8093,sizeof(hashlist*));
	}
	
	//calloc(all nulls), create hlist node 
	hashlist* newhnode  = calloc(1,sizeof(hashlist));
	newhnode->klasi=klasi;
	newhnode->NodeDomis=N;
	//newhnode->next=NULL;
	
	//link new node in the beggining of list
	newhnode->next=htable[thesi];
	htable[thesi]=newhnode;
	
}


//bitmap search function
void *lookForZero(Domi **L, int bit_vector_size, int klasi){
	
	if (bit_vector_size<1){
		bit_vector_size=1;
	}
	
	int counter=0;
	//gia kathe char sto array
	if (*L==NULL){

		newNodeDomis(&(*L), bit_vector_size, klasi);
		return (*L)->selida;
	}
	
	//gia kathe char sto array
	for(int j=0; j<bit_vector_size; j++){
		 
		//krataw to char
		char temp1;
		temp1=(*L)->bitmap[j];
		//printf("char am checkin: %c\n",temp1);
		
		//gia kathe bit sto char
		for (int i=7; i>=0; i--){
			
			//krataw thn arxikh morfh char
			char temp2;
			temp2=temp1;
			temp2=temp2>>i;
			temp2=temp2&1;
			 
			if (temp2==0){
				
				//printf("ep: %d\n", i);
				char c=ipow(2,i);
				
				//printf("HERE: char(128): %d\n",(int)(c));
				//printf("HERE: char: %d\n",(int)((*L)->bitmap[j]));
				//printf("char am checkin: %c\n",c);
				(*L)->bitmap[j]=(*L)->bitmap[j]|c;
				//printf("HERE: char: %d\n",(int)((*L)->bitmap[j]));
				//return (((*L)->selida) + (void*)(counter*bit_vector_size));
				return (char*)((*L)->selida) + counter*klasi;
			}
			if (klasi==1024 && counter==3){// thelw mono ta 4 prwta bit tou desmevmenou char
				break;
			}
			else if (klasi==2048 && counter==1){ //thelw mono ta prwta dyo bit tou desmeumenou char
				break;
			}
			else if (klasi==4096){	//thelw mono to prwto bit tou desmeumenou char
				break;
			}
			counter++;
		}
	}
	
	//if (counter>=(bit_vector_size*8)){}
	return lookForZero(&((*L)->next), bit_vector_size, klasi);

	
}


void *mymalloc(size_t cbytes){
	
	void *ptr;
	
	if (cbytes>4096){
		//call traditional malloc
		printf("classic malloc called,  ");
		ptr=malloc(cbytes);
		return ptr;
		}
		
	else{
		int klasi;
		int bit_vector_size;
			
		if (cbytes<=32){
			klasi=32;
			bit_vector_size=4096/klasi/8;
			
			// ama den exw ksanavalei stin taksi megethous 32
			if (evretirio[0]==NULL){
				
				newNodeDomis(&evretirio[0], bit_vector_size, klasi);
				
				//gyrnaw arxi selidas
				return evretirio[0]->selida;	
			}
			else{
				ptr=lookForZero(&evretirio[0], bit_vector_size, klasi);
				
				return ptr;
			}
		}

		else if (cbytes<=64){
			klasi=64;
			bit_vector_size=4096/klasi/8;
			
			// ama den exw ksanavalei stin taksi megethous 64
			if (evretirio[1]==NULL){
				
				newNodeDomis(&evretirio[1], bit_vector_size, klasi);
				
				//gyrnaw arxi selidas
				return evretirio[1]->selida;
			}
			else{
				ptr=lookForZero(&evretirio[1], bit_vector_size, klasi);
				
				return ptr;
			}
		}
		
		else if (cbytes<=128){
			klasi=128;
			bit_vector_size=4096/klasi/8;
			
			// ama den exw ksanavalei stin taksi megethous 128
			if (evretirio[2]==NULL){
				
				newNodeDomis(&evretirio[2], bit_vector_size,klasi);
				
				//gyrnaw arxi selidas
				return evretirio[2]->selida;
			}
			else{
				ptr=lookForZero(&evretirio[2], bit_vector_size,klasi);
				
				return ptr;
			}
		}
		else if (cbytes<=256){
			klasi=256;
			bit_vector_size=4096/klasi/8;
			
			// ama den exw ksanavalei stin taksi megethous 256
			if (evretirio[3]==NULL){
				
				newNodeDomis(&evretirio[3], bit_vector_size,klasi);
				
				//gyrnaw arxi selidas
				return evretirio[3]->selida;
			}
			else{
				ptr=lookForZero(&evretirio[3], bit_vector_size,klasi);
				
				return ptr;
			}
		}
		else if (cbytes<=512){
			klasi=512;
			bit_vector_size=4096/klasi/8;
			
			// ama den exw ksanavalei stin taksi megethous 512
			if (evretirio[4]==NULL){
				
				newNodeDomis(&evretirio[4], bit_vector_size,klasi);
				
				//gyrnaw arxi selidas
				return evretirio[4]->selida;
			}
			else{
				ptr=lookForZero(&evretirio[4], bit_vector_size,klasi);
				
				return ptr;
			}
		}
		else if (cbytes<=1024){
			klasi=1024;
			bit_vector_size=4096/klasi/8;
			
			// ama den exw ksanavalei stin taksi megethous 1024
			if (evretirio[5]==NULL){
				
				newNodeDomis(&evretirio[5], bit_vector_size,klasi);
				
				//gyrnaw arxi selidas
				return evretirio[5]->selida;
			}
			else{
				ptr=lookForZero(&evretirio[5], bit_vector_size,klasi);
				
				return ptr;
			}
		}
		else if (cbytes<=2048){
			klasi=2048;
			bit_vector_size=4096/klasi/8;
			
			// ama den exw ksanavalei stin taksi megethous 2048
			if (evretirio[6]==NULL){
				
				newNodeDomis(&evretirio[6], bit_vector_size,klasi);
				
				//gyrnaw arxi selidas
				return evretirio[6]->selida;
			}
			else{
				ptr=lookForZero(&evretirio[6], bit_vector_size,klasi);
				
				return ptr;
			}
		}
		else if (cbytes<=4096){
			klasi=4096;
			bit_vector_size=4096/klasi/8;
			
			// ama den exw ksanavalei stin taksi megethous 4096
			if (evretirio[7]==NULL){
				
				newNodeDomis(&evretirio[7], bit_vector_size,klasi);
				
				//gyrnaw arxi selidas
				return evretirio[7]->selida;
			}
			else{
				ptr=lookForZero(&evretirio[7], bit_vector_size,klasi);
				
				return ptr;
			}
		}
	}	
}

void myfree(void* ad ){
	
	printf("Address to free = %p,  ", ad);
	unsigned int newad;
	newad= (unsigned int)(ad)-((unsigned int)(ad)%4096);
	//round down address to 4096(selida)
	int thesi= (newad/4096)%8093;
	//printf("Address rounded down to 4096 = %u\n", newad);
	
	hashlist* node = htable[thesi];
	int found=0;
	while(node!=NULL)
	{
		Domi *temp;
		temp=node->NodeDomis;
		if((unsigned int)(temp->selida)==newad)
		{
			found=1;
			printf("found\n");
			break;
			
		}
		node=node->next;
	}
	if(found==0)
	{
		//not created with myallocator
		printf("classic free called\n");
		free(ad);
		return;
	}
	//sto node einai ta stoixeia gia tin selida, metrwntas apo ta aristera
	int bittochange = ((unsigned int)ad - newad) / node->klasi;
	
	//free, change bit to 0
	int charNo = bittochange/8;
	//if (charNo<1) charNo=1;
	
	char mask = (int)(255 - ipow(2,(8-(bittochange%8)-1)));	//anathesi 11111111 meiwn thn apostash big-endian etsi wste na prokupsei arithmos thn morfis 11110111
	
	Domi *tempDomi = node->NodeDomis;
	tempDomi->bitmap[charNo]=tempDomi->bitmap[charNo]&mask;
	
	return;
}

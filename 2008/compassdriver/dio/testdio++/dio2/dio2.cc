#include "dio2.hh"

#include<unistd.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

//  * base + 0x40: free-running microseconds counter (RO)//could be useful for a busy loop

#define WAIT usleep(100000)

int main(void){
	DIO_basic diodriver;

	while(true){
		diodriver.dioblock_out->greenled = 1;
		WAIT;
		diodriver.dioblock_out->greenled = 0;
		WAIT;
	}


//	for(int i = 0; i < 1000; i++){
/*
	//diodriver.dioblock_in->pin13 = 1;//set as output
	while(1){
		diodriver.dioblock_out->pin13 = 1;
		//diodriver.dioblock_out->greenled = 1;
		WAIT;
		diodriver.dioblock_out->pin13 = 0;
		WAIT;
	}
*/
/*
	while(1){
		diodriver.*dio_out = 1 << 13;
		WAIT;
		diodriver.*dio_out = 0;
		WAIT;
	}
*/
	return(0);
}
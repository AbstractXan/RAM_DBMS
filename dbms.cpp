#include <stdio.h>
#include <stdlib.h>
#include "handle.h"

using namespace std;

//you implemnet your own code here
result_t* myexec(char *query) {
	result_t* const res = (result_t*)malloc(sizeof(result_t));
	//your code runs here
	printf("inside myexec query=%s\n",query);
	return res;
}

handle_t* get_handle() {
	handle_t* const myhandle = (handle_t*)malloc(sizeof(handle_t));
	myhandle->exec = myexec;
	printf("inside get_handle\n");
	return myhandle;
}

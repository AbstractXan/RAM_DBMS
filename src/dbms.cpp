#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "handle.h"

using namespace std;

//bool findTable

//result_t* createTable(char *tablename, int colNum, col_t* colList){

//}

void handle_t::clear(){
	delete currentDB;
}

//you implemnet your own code here
result_t* handle_t::exec(string query) {
	result_t* const res = (result_t*)malloc(sizeof(result_t));
	cout<<this->currentDB<<endl;
	//your code runs here
	cout<<"Inside exec, query = "<<query<<endl;
	return res;
}

handle_t* get_handle() {
	handle_t* const myhandle = (handle_t*)malloc(sizeof(handle_t));
	myhandle->currentDB = new database_t;
	myhandle->currentDB->firstTable = NULL;
	printf("inside get_handle\n");
	return myhandle;
}

void delete_handle(handle_t *handle){
	free(handle);
}

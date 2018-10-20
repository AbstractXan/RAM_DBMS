#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "handle.h"

using namespace std;

table_t *database_t::findTable(string tableName){
	table_t* temp = this->firstTable;
	while(temp != NULL && !temp->tableName.compare(tableName)){
		temp = temp->nextTable;
	}
	return temp;
}

result_t* database_t::createTable(string tablename, int colNum, col_t* colList){
	if(this->findTable(tablename)){
		//error();
	}

	table_t* newTab = new table_t;

	newTab->nextTable = this->firstTable;
	this->firstTable = newTab;
	newTab->rows = 0;
	newTab->cols = colNum;
	newTab->tableName = tablename;
	newTab->attributeList = new attr_t[colNum];
	for(int i = 0; i < colNum ; i++){

	}
}

void handle_t::clear(){
	delete currentDB;
}

//you implemnet your own code here
result_t* handle_t::exec(string query) {
	result_t* const res = (result_t*)malloc(sizeof(result_t));
	cout<<this->currentDB<<endl;
	//your code runs here
	printf("%s\n",query);
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

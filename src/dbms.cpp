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
		newTab->attributeList[i].attr_name = colList[i].name;
		newTab->attributeList[i].attr_type = colList[i].type;
		newTab->attributeList[i].cell = NULL;
		newTab->attributeList[i].isPK = colList[i].isPK;
		newTab->attributeList[i].isFK = colList[i].isFK;
		newTab->attributeList[i].isNotNull = colList[i].isNotNull;
		newTab->attributeList[i].hasDefault = colList[i].isNotNull;
		newTab->attributeList[i].defaultVal = colList[i].defaultVal;
		newTab->attributeList[i].onDelete = colList[i].onDelete;
	}
	//return done();
}

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

// ERROR HANDLING //
void Error(string str){
	printf("\n [!] Error: %s",str);
}
// DEBUGGING FUNCTIONS //
/* DISPLAY TABLE FOR DEBUGGING */
void printTable(table_t *table){
	
	attr_t attr = table->attributeList;
	int colnum = table->cols;
	int rownum = table->rows;
	
	//Check if attr_list exists
	if(attr==NULL){
		Error("Table not initialized!");
		return;
	}

	//Pointer to first cell of every col
	cell_t *cells[colnum];
	
	// Table stats
	cout << "\nTable: " << table_t->tableName;
	cout << "\nRows: " << rownum << " Cols: " << colnum;

	//Print all attr names
	//Initialize 'cells' pointer array
	for(int i=0 ; i<colnum ; i++){
		cout << attr[i]->attr_name << "\t";
		cells[i] = attr[i]->cell;
	}
	
	cout<<"\n";
	
	//Print table data
	//Col-wise print
	for(int i=0; i<rownum ; i++){
		// Row-wise print
		for(int j=0; j<colnum;j++){
			cout << cells[j]->value << "\t";
			cells[j] = cells[j]->next;
		}
		cout << "\n";
	}
}

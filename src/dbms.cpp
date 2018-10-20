#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include "handle.h"

using namespace std;

table_t *database_t::findTable(string tableName){
	table_t* temp = this->firstTable;
	while(temp != NULL && temp->tableName.compare(tableName)){
		temp = temp->nextTable;
	}
	return temp;
}

void database_t::displayData(){
	cout<<"\nDatabase:"<<endl<<endl;
	table_t *table = this->firstTable;
	while(table != NULL){
		table->printTable();
		cout<<endl;
		table = table->nextTable;
	}
}

result_t* database_t::createTable(string tablename, int colNum, col_t* colList){
	if(this->findTable(tablename)){
		Error("Table Already Exists");
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
		newTab->attributeList[i].hasDefault = colList[i].hasDefault;
		newTab->attributeList[i].defaultVal = colList[i].defaultVal;
		newTab->attributeList[i].onDelete = colList[i].onDelete;
	}
	cout<<"Table created"<<endl;
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
	col_t *attrs = new col_t[3];
	attrs[0].name = "Name";
	attrs[0].type = STR;
	attrs[0].isPK = true;
	attrs[0].isFK = false;
	attrs[0].isNotNull = false;
	attrs[0].hasDefault = false;
	strcpy(attrs[0].defaultVal.str,"name");
	attrs[0].onDelete = SETNULL;

	attrs[1].name = "Year";
	attrs[1].type = VAL;
	attrs[1].isPK = false;
	attrs[1].isFK = false;
	attrs[1].isNotNull = true;
	attrs[1].hasDefault = true;
	attrs[1].defaultVal.value = 1998;
	attrs[1].onDelete = CASCADE;

	attrs[2].name = "Salary";
	attrs[2].type = VAL;
	attrs[2].isPK = false;
	attrs[2].isFK = false;
	attrs[2].isNotNull = false;
	attrs[2].hasDefault = false;
	attrs[2].defaultVal.value = 1;
	attrs[2].onDelete = SETNULL;

	this->currentDB->createTable("SampleTable", 3, attrs);

	attrs[0].name = "Cool";
	attrs[0].type = STR;
	attrs[0].isPK = true;
	attrs[0].isFK = false;
	attrs[0].isNotNull = false;
	attrs[0].hasDefault = false;
	strcpy(attrs[0].defaultVal.str,"name");
	attrs[0].onDelete = SETNULL;

	attrs[1].name = "ULe";
	attrs[1].type = VAL;
	attrs[1].isPK = false;
	attrs[1].isFK = false;
	attrs[1].isNotNull = true;
	attrs[1].hasDefault = true;
	attrs[1].defaultVal.value = 1998;
	attrs[1].onDelete = CASCADE;

	attrs[2].name = "Ssdry";
	attrs[2].type = VAL;
	attrs[2].isPK = false;
	attrs[2].isFK = false;
	attrs[2].isNotNull = false;
	attrs[2].hasDefault = false;
	attrs[2].defaultVal.value = 1;
	attrs[2].onDelete = SETNULL;

	this->currentDB->createTable("ExtraTable", 3, attrs);
	this->currentDB->displayData();
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
	cout<<"Error : "<<str<<endl;
}
// DEBUGGING FUNCTIONS //
/* DISPLAY TABLE FOR DEBUGGING */
void table_t::printTable(){

	attr_t *attr = attributeList;
	int colnum = cols;
	int rownum = rows;

	//Check if attr_list exists
	if(attr == NULL){
		Error("Table not initialized!");
		return;
	}

	//Pointer to first cell of every col
	cell_t *cells[colnum];

	// Table stats
	cout << "\nTable: " << tableName;
	cout << "\nRows: " << rownum << " Cols: " << colnum;
	cout<<endl;

	//Print all attr names
	//Initialize 'cells' pointer array
	for(int i=0 ; i<colnum ; i++){
		cout << attr[i].attr_name << "\t";
		cells[i] = attr[i].cell;
	}

	cout<<endl;

	//Print table data
	//Col-wise print
	for(int i=0; i<rownum ; i++){
		// Row-wise print
		for(int j=0; j<colnum;j++){
			if(attr[j].attr_type == STR){
				cout << cells[j]->value.str << "\t";
			}
			else{
				cout << cells[j]->value.value << "\t";
			}
			cells[j] = cells[j]->next;
		}
		cout << "\n";
	}
}

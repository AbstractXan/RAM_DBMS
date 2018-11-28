#include "handle.h"
#include <iostream>

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

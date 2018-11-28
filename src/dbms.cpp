#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "handle.h"

using namespace std;

void handle_t::clear(){
	delete currentDB;
}

bool createTableFromTok(database_t *db, tokenList query){
	query.next();
	if(query.front() != "table"){
		return false;
	}
	query.next();
	string tableNameTemp = query.front();
	query.next();
	string lookahead, current;
	vector<col_t> columns;
	int colnum = 0;
	while(query.front().compare(";")){
		lookahead = query.list[1];
		current = query.front();
		if(!lookahead.compare(";") || !lookahead.compare(",")){
			return false;
		}

		col_t temp;
		temp.isPK = false;
		temp.isFK = false;
		temp.isNotNull = false;

		if(!current.compare("fk")){
			temp.isFK = true;
			query.next();
			current = query.front();
		}
		else if(!current.compare("pk")){
			temp.isPK = true;
			temp.isNotNull = true;
			query.next();
			current = query.front();
		}

		temp.name = current;
		query.next();
		current = query.front();
		temp.type = !current.compare("varchar") ? STR : VAL;
		query.next();
		temp.onDelete = SETNULL;
		temp.hasDefault = false;

		columns.push_back(temp);
		colnum++;
		cout<<temp.isPK<<" "<<temp.name<<" "<<temp.type<<endl;
	}
	db->createTable(tableNameTemp, colnum, columns);
	return true;
}

void selectFromTable(tokenList query, handle_t *handle){

	query.next();
	vector<string>col_id;
	if(query.front() == "*"){
		query.next();
		query.next();
		string tablename = query.front();
		table_t *tab;
		if(tab = handle->currentDB->findTable(tablename)){
			tab->printTable();
		}
		else{
			cout<<"Table does not exist"<<endl;
		}
	}
	else{
		
		while(query.front().compare("from") && query.front()!=";")
		{
			col_id.push_back(query.front());
			query.next();
		}
		if(!query.front().compare("from"))
		{
			query.next();
			string tablename=query.front();
			table_t *tab;
			if(tab = handle->currentDB->findTable(tablename))
			{
				
				tab->printTable(col_id);
				query.next();
				if(!query.front().compare("where"))
				{
				}
					
			}
			else
			{
				cout<<"Table does not exist"<<endl;
			}
		}
	}
}

//you implemnet your own code here
result_t* handle_t::exec(tokenList query) {
	result_t* const res = (result_t*)malloc(sizeof(result_t));
	cout<<this->currentDB<<endl;

	if(!query.front().compare("create")){
		cout<<"CREATE"<<endl;
		if(!createTableFromTok(this->currentDB, query)){
			cout<<"Table not created"<<endl;
		}
	}
	else if(!query.front().compare("select")){
		cout<<"Select\n";
		selectFromTable(query, this);
	}
	
		//your code runs here
		//cout<<"Inside exec, query = "<<query<<endl;

		//this->currentDB->displayData();


	return res;
}

handle_t* get_handle() {
	handle_t* const myhandle = (handle_t*)malloc(sizeof(handle_t));
	myhandle->currentDB = new database_t;
	myhandle->currentDB->firstTable = NULL;
	printf("inside get_handle\n");
	vector<col_t> attrs(3);
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

	myhandle->currentDB->createTable("SampleTable", 3, attrs);

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
	attrs[2].isPK = true;
	attrs[2].isFK = false;
	attrs[2].isNotNull = false;
	attrs[2].hasDefault = false;
	attrs[2].defaultVal.value = 1;
	attrs[2].onDelete = SETNULL;

	myhandle->currentDB->createTable("ExtraTable", 3, attrs);


	//Filling test data
	cell_t **insertCells = new cell_t*[3];
	for(int i = 0; i < 3 ; i++){
		insertCells[i] = new cell_t;
	}
	strcpy( insertCells[0]->value.str, "Roh.it");
	insertCells[1]->value.value = 1998;
	insertCells[2]->value.value = 5000;
	myhandle->currentDB->findTable("SampleTable")->insertValue(insertCells);

	for(int i = 0 ; i < 3 ; i++){
		insertCells[i] = new cell_t;
	}
	strcpy( insertCells[0]->value.str, "Priyanshu");
	insertCells[1]->value.value = 1997;
	insertCells[2]->value.value = 5053;
	myhandle->currentDB->findTable("SampleTable")->insertValue(insertCells);

	for(int i = 0 ; i < 3 ; i++){
		insertCells[i] = new cell_t;
	}
	strcpy( insertCells[0]->value.str, "Roh.it");
	insertCells[1]->value.value = 1998;
	insertCells[2]->value.value = 6000;
	myhandle->currentDB->findTable("SampleTable")->insertValue(insertCells);

	for(int i = 0 ; i < 3 ; i++){
		insertCells[i] = new cell_t;
	}
	strcpy( insertCells[0]->value.str, "Rohith");
	insertCells[1]->value.value = 1998;
	insertCells[2]->value.value = 6000;
	myhandle->currentDB->findTable("ExtraTable")->insertValue(insertCells);
	return myhandle;
}


void delete_handle(handle_t *handle){
	free(handle);
}

// ERROR HANDLING //
void Error(string str){
	cout<<"Error : "<<str<<endl;
}

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

bool createTableFromTok(database_t *db, tokenList &query){
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
		//cout<<temp.isPK<<" "<<temp.name<<" "<<temp.type<<endl;
	}
	db->createTable(tableNameTemp, colnum, columns);
	return true;
}

void insertIntoTable(tokenList &query, handle_t *handle){
	query.next();
	if(query.front().compare("into")){ cout<<"Syntax Error. Expected 'INTO' keyword"<<endl; }
	
	else{
		//Get TableName
		query.next();
		string tablename = query.front(); query.next();
		table_t *tab;
		if(tab = handle->currentDB->findTable(tablename)){ //TABLE

			int num = 1; //NUMBER OF VALUES HARD CODED AS 1
			cell_t **insertCells = new cell_t* [tab->cols];

			//FOR EACH SET OF VALUES 
			for(int j = 0; j < tab->cols  ; j++){
				insertCells[j] = new cell_t;
			}
			//FOR EACH VALUE
			for(int i=0; i < tab->cols ; i++){

				//cout << i<<endl;
				//cout << query.front() << endl;
				if(query.front().compare(";")==0){ cout<<"UNEXPECTED END OF INSERT. Check number of values."<<endl;return;}
				
				if(tab->attributeList[i].attr_type == STR){
					strcpy(insertCells[i]->value.str, query.front().substr(1,query.front().size()-2).c_str());
					//cout<<"S: "<<insertCells[i]->value.str<<"-"<<query.front().substr(1,query.front().size()-2).c_str()<<endl;
					query.next();
				}
				else{
					insertCells[i]->value.value = atoi(query.front().c_str());
					//cout<<"N: "<<insertCells[i]->value.value<<"-"<<atoi(query.front().c_str())<<endl;
					query.next();
				}
				
			}	
			cout<<endl;

			if(query.front().compare(";")==0){
				tab->insertValue(insertCells);
				cout << "Inserted " << num << " rows." << endl; 
			}

		}
		else{
			cout<<"Table does not exist"<<endl; return;
		}
	}
}

void selectFromTable(tokenList &query, handle_t *handle){

	query.next();
	vector<string>col_id;
	if(query.front() == "*"){
		query.next();
		query.next();
		string tablename = query.front();
		table_t *tab = handle->currentDB->findTable(tablename);
		query.next();
		if(query.front() == ";"){
			if(tab){
				tab->printTable();
			}
			else{
				cout<<"Table does not exist"<<endl;
			}
		}
		else if(!query.front().compare("where"))
		{
			int f = -1;
			query.next();
			vector<constraint> expr;
			while(query.front().compare(";"))
			{
				if(query.front().compare("and") && query.front().compare("or")){
					struct constraint e;
					e.operand1=query.front();
					if(e.operand1[0] == '"' && e.operand1[e.operand1.size()-1] == '"'){
						e.opt1 = STRING;
					}
					else if(e.operand1[0] >= '0' && e.operand1[0] <= '9'){
						e.opt1 = INTEGER;
					}
					else{
						e.opt1 = COLUMN;
					}
					query.next();
					e.op=query.front();
					query.next();
					e.operand2=query.front();
					query.next();
					if(e.operand2[0] == '"' && e.operand2[e.operand2.size()-1] == '"'){
						e.opt2 = STRING;
					}
					else if(e.operand2[0] >= '0' && e.operand2[0] <= '9'){
						e.opt2 = INTEGER;
					}
					else{
						e.opt2 = COLUMN;
					}
					expr.push_back(e);
				}
				if(!query.front().compare("and")){
					f = 0;
					query.next();
				}
				else if(!query.front().compare("or")){
					f = 1;
					query.next();
				}
			}
			tab->printTable(expr, f);
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
				query.next();
				if(!query.front().compare(";"))
				{
					tab->printTable(col_id);
				}
				else if(!query.front().compare("where"))
				{
					int f = -1;
					query.next();
					vector<constraint> expr;
					while(query.front().compare(";"))
					{
						if(query.front().compare("and") && query.front().compare("or")){
							struct constraint e;
							e.operand1=query.front();
							if(e.operand1[0] == '"' && e.operand1[e.operand1.size()-1] == '"'){
								e.opt1 = STRING;
							}
							else if(e.operand1[0] >= '0' && e.operand1[0] <= '9'){
								e.opt1 = INTEGER;
							}
							else{
								e.opt1 = COLUMN;
							}
							query.next();
							e.op=query.front();
							query.next();
							e.operand2=query.front();
							query.next();
							if(e.operand2[0] == '"' && e.operand2[e.operand2.size()-1] == '"'){
								e.opt2 = STRING;
							}
							else if(e.operand2[0] >= '0' && e.operand2[0] <= '9'){
								e.opt2 = INTEGER;
							}
							else{
								e.opt2 = COLUMN;
							}
							expr.push_back(e);
						}
						if(!query.front().compare("and")){
							f = 0;
							query.next();
						}
						else if(!query.front().compare("or")){
							f = 1;
							query.next();
						}
					}
					tab->printTable(col_id,expr, f);
				}	
			}
			else
			{
				cout<<"Table does not exist"<<endl;
			}	
	}
	}
}

void deleteFromTable(tokenList query, handle_t *handle){
	query.next();
	if(!query.front().compare("from")){
		query.next();
		string tablename = query.front();
		query.next();
		table_t *tab;
		if(tab = handle->currentDB->findTable(tablename)){
			if(!query.front().compare(";")){
				for(int i=0; i<tab->cols; i++){
					tab->rows = 0;
					tab->attributeList[i].cell = NULL;
				}
			}
			if(!query.front().compare("where")){
				int f = -1;
				query.next();
				vector<constraint> expr;
				while(query.front().compare(";")){
					if(query.front().compare("and") && query.front().compare("or")){
						struct constraint e;
						e.operand1=query.front();
						if(e.operand1[0] == '"' && e.operand1[e.operand1.size()-1] == '"'){
							e.opt1 = STRING;
						}
						else if(e.operand1[0] >= '0' && e.operand1[0] <= '9'){
							e.opt1 = INTEGER;
						}
						else{
							e.opt1 = COLUMN;
						}
						query.next();
						e.op=query.front();
						query.next();
						e.operand2=query.front();
						query.next();
						if(e.operand2[0] == '"' && e.operand2[e.operand2.size()-1] == '"'){
							e.opt2 = STRING;
						}
						else if(e.operand2[0] >= '0' && e.operand2[0] <= '9'){
							e.opt2 = INTEGER;
						}
						else{
							e.opt2 = COLUMN;
						}
						expr.push_back(e);
					}
					if(!query.front().compare("and")){
						f = 0;
						query.next();
					}
					else if(!query.front().compare("or")){
						f = 1;
						query.next();
					}
				}
				tab->deleteAttr(expr,f);
			}
		}
	}
}

//you implemnet your own code here
result_t* handle_t::exec(tokenList query) {
	result_t* const res = (result_t*)malloc(sizeof(result_t));
	//cout<<this->currentDB<<endl;

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
	else if(!query.front().compare("delete")){
		cout<<"DELETE\n";
		deleteFromTable(query, this);
	}
	else if (!query.front().compare("insert")){
		cout<<"Insert" << endl;
		insertIntoTable(query, this);
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
	// vector<col_t> attrs(3);
	// attrs[0].name = "Name";
	// attrs[0].type = STR;
	// attrs[0].isPK = true;
	// attrs[0].isFK = false;
	// attrs[0].isNotNull = false;
	// attrs[0].hasDefault = false;
	// strcpy(attrs[0].defaultVal.str,"name");
	// attrs[0].onDelete = SETNULL;

	// attrs[1].name = "Year";
	// attrs[1].type = VAL;
	// attrs[1].isPK = false;
	// attrs[1].isFK = false;
	// attrs[1].isNotNull = true;
	// attrs[1].hasDefault = true;
	// attrs[1].defaultVal.value = 1998;
	// attrs[1].onDelete = CASCADE;

	// attrs[2].name = "Salary";
	// attrs[2].type = VAL;
	// attrs[2].isPK = false;
	// attrs[2].isFK = false;
	// attrs[2].isNotNull = false;
	// attrs[2].hasDefault = false;
	// attrs[2].defaultVal.value = 1;
	// attrs[2].onDelete = SETNULL;

	// myhandle->currentDB->createTable("SampleTable", 3, attrs);

	// attrs[0].name = "Cool";
	// attrs[0].type = STR;
	// attrs[0].isPK = true;
	// attrs[0].isFK = false;
	// attrs[0].isNotNull = false;
	// attrs[0].hasDefault = false;
	// strcpy(attrs[0].defaultVal.str,"name");
	// attrs[0].onDelete = SETNULL;

	// attrs[1].name = "ULe";
	// attrs[1].type = VAL;
	// attrs[1].isPK = false;
	// attrs[1].isFK = false;
	// attrs[1].isNotNull = true;
	// attrs[1].hasDefault = true;
	// attrs[1].defaultVal.value = 1998;
	// attrs[1].onDelete = CASCADE;

	// attrs[2].name = "Ssdry";
	// attrs[2].type = VAL;
	// attrs[2].isPK = true;
	// attrs[2].isFK = false;
	// attrs[2].isNotNull = false;
	// attrs[2].hasDefault = false;
	// attrs[2].defaultVal.value = 1;
	// attrs[2].onDelete = SETNULL;

	// myhandle->currentDB->createTable("ExtraTable", 3, attrs);


	// //Filling test data
	// cell_t **insertCells = new cell_t*[3];
	// for(int i = 0; i < 3 ; i++){
	// 	insertCells[i] = new cell_t;
	// }
	// strcpy( insertCells[0]->value.str, "Roh.it");
	// insertCells[1]->value.value = 1998;
	// insertCells[2]->value.value = 5000;
	// myhandle->currentDB->findTable("SampleTable")->insertValue(insertCells);

	// for(int i = 0 ; i < 3 ; i++){
	// 	insertCells[i] = new cell_t;
	// }
	// strcpy( insertCells[0]->value.str, "Priyanshu");
	// insertCells[1]->value.value = 1997;
	// insertCells[2]->value.value = 5053;
	// myhandle->currentDB->findTable("SampleTable")->insertValue(insertCells);

	// for(int i = 0 ; i < 3 ; i++){
	// 	insertCells[i] = new cell_t;
	// }
	// strcpy( insertCells[0]->value.str, "Roh.it");
	// insertCells[1]->value.value = 1998;
	// insertCells[2]->value.value = 6000;
	// myhandle->currentDB->findTable("SampleTable")->insertValue(insertCells);

	// for(int i = 0 ; i < 3 ; i++){
	// 	insertCells[i] = new cell_t;
	// }
	// strcpy( insertCells[0]->value.str, "Rohith");
	// insertCells[1]->value.value = 1998;
	// insertCells[2]->value.value = 6000;
	// myhandle->currentDB->findTable("ExtraTable")->insertValue(insertCells);
	return myhandle;
}


void delete_handle(handle_t *handle){
	free(handle);
}

// ERROR HANDLING //
void Error(string str){
	cout<<"Error : "<<str<<endl;
}

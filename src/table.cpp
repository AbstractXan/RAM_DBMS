// DEBUGGING FUNCTIONS //
/* DISPLAY TABLE FOR DEBUGGING */
#include "handle.h"
#include<iostream>

using namespace std;

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

void table_t::insertValue(){
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

	//Print all attr names
	//Initialize 'cells' pointer array
	for(int i=0 ; i<colnum ; i++){
		cout << attr[i].attr_name << "\t";
		cells[i] = attr[i].cell;
	}


}

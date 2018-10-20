// DEBUGGING FUNCTIONS //
/* DISPLAY TABLE FOR DEBUGGING */
#include "handle.h"
#include<iostream>
#include<cstring>

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


//------------------------ //

//Check if there exis a duplicate attribute for that column
bool checkIfDuplicate(attrtype_t type, cell_t *cell, attrval_t attr){
	while(cell!=NULL){
		if(type == STR){
			if(strcmp(cell->value.str,attr.str)==0){
				return true;
			}
		}
		else{
			if(cell->value.value==attr.value){
				return true;
			}
		}
		cell = cell->next;
	}
	return false;
}
// insertvalue of tuples based on PK / Not null
//return true if success
bool table_t::insertValue(cell_t *insertCells){ //Takes in array of cell pointers aka 'insertCells'
    attr_t *attr = attributeList;
	int colnum = cols;
	int rownum = rows;

	//Check if attr_list exists
	if(attr == NULL){
		Error("Table not initialized!");
		return false;
	}

	//Pointer to first cell of every col
	cell_t *cells[colnum];

		//Initialize 'cells' pointer array
	for(int i=0 ; i<colnum ; i++){
		cells[i] = attr[i].cell;
	}

	//Traverse throught attributes of table
	for(int i=0; i<colnum;i++){

		//If attribute is PK
		if(attributeList[i].isPK){

			//And while cell is not null
			//Check for all cells in that column for duplicacy
			if(checkIfDuplicate(attributeList[i].attr_type, cells[i], insertCells[i].value)){
				return false; //Insertion failed
			}

			//Main insertion here
		}
	}


}



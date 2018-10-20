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
bool checkIfDuplicate(attr_t *attributes, int colnum, cell_t *cell[], cell_t *attr[]){
	for(int i = 0; i < colnum; i++){
		if(attributes[i].isPK){
			cout<<attributes[i].attr_name<<" ";
			if(attributes[i].attr_type == STR){
				cout<<cell[i]->value.str<<" "<<attr[i]->value.str<<endl;
				if(!(strcmp(cell[i]->value.str, attr[i]->value.str)==0)){
					return false;
				}
			}
			else{
				cout<<cell[i]->value.value<<" "<<attr[i]->value.value<<endl;
				if(cell[i]->value.value != attr[i]->value.value){
					return false;
				}
			}
		}
	}
	return true;
}
// insertvalue of tuples based on PK / Not null
//return true if success
bool table_t::insertValue(cell_t *insertCells[]){ //Takes in array of cell pointers aka 'insertCells'
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
	for(int i=0; i < rownum;i++){

		//And while cell is not null
		//Check for all cells in that column for duplicacy
		if(checkIfDuplicate(attributeList, colnum, cells, insertCells)){
			cout<<"Inserted failed"<<endl;
			return false; //Insertion failed
		}

		for(int j = 0; j < colnum; j++){
			cells[j] = cells[j]->next;
		}
	}

	for(int i = 0; i < colnum ; i++){
		insertCells[i]->next = attributeList[i].cell;
		attributeList[i].cell = insertCells[i];
	}
	this->rows++;
	cout<<"Inserted row into table"<<endl;
}
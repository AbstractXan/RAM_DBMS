#include <stdio.h>
#include <stdlib.h>
#include "handle.h"

using namespace std;

//you implemnet your own code here
result_t* myexec(char *query) {
	result_t* const res = (result_t*)malloc(sizeof(result_t));
	//your code runs here
	printf("inside myexec query=%s\n",query);
	return res;
}

handle_t* get_handle() {
	handle_t* const myhandle = (handle_t*)malloc(sizeof(handle_t));
	myhandle->exec = myexec;
	printf("inside get_handle\n");
	return myhandle;
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
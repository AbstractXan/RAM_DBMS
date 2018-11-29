// DEBUGGING FUNCTIONS //
/* DISPLAY TABLE FOR DEBUGGING */
#include "handle.h"
#include <bits/stdc++.h>

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
	cout<<endl<<endl;

	//Print all attr names
	//Initialize 'cells' pointer array
	for(int i=0 ; i<colnum ; i++){
		//cout << attr[i].attr_name << "\t";
		printf("%12s\t",attr[i].attr_name.c_str());
		cells[i] = attr[i].cell;
	}

	cout<<endl;

	//Print table data
	//Col-wise print
	for(int i=0; i<rownum ; i++){
		// Row-wise print
		for(int j=0; j<colnum;j++){
			if(attr[j].attr_type == STR){
				//cout << cells[j]->value.str << "\t";
				printf("%12s\t",cells[j]->value.str);
			}
			else{
				//cout << cells[j]->value.value << "\t";
				printf("%12d\t",cells[j]->value.value);
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
			//cout<<attributes[i].attr_name<<" ";
			if(attributes[i].attr_type == STR){
				//cout<<cell[i]->value.str<<" "<<attr[i]->value.str<<endl;
				if(!(strcmp(cell[i]->value.str, attr[i]->value.str)==0)){
					return false;
				}
			}
			else{
				//cout<<cell[i]->value.value<<" "<<attr[i]->value.value<<endl;
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
			//cout<<"Inserted failed"<<endl;
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
	//cout<<"Inserted row into table"<<endl;
}

bool Find(string name, vector<string> col_id){
	for(int i=0;i<col_id.size();i++)
	{
		if(!col_id[i].compare(name))
		{
			return true;
		}
	}
	return false;
}


void table_t::printTable(vector<string> col_id)
{
	
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
	cout<<endl<<endl;

	//Print all attr names
	//Initialize 'cells' pointer array
	for(int i=0 ; i<colnum ; i++){
		if(Find(attr[i].attr_name,col_id)){
			printf("%12s\t",attr[i].attr_name.c_str());
		}
		cells[i] = attr[i].cell;
	}

	cout<<endl;

	//Print table data
	//Col-wise print
	for(int i=0; i<rownum ; i++){
		// Row-wise print
		for(int j=0; j<colnum;j++){
			if(attr[j].attr_type == STR && Find(attr[j].attr_name,col_id)){
				printf("%12s\t",cells[j]->value.str);
			}
			else{
				if(Find(attr[j].attr_name,col_id))
				{
					printf("%12d\t",cells[j]->value.value);
				}
			}
			cells[j] = cells[j]->next;
		}
		cout << "\n";
	}
}

bool table_t::getColNum(string colName){
    for(int i = 0 ; i < cols ; i++){
        if(!colName.compare(attributeList[i].attr_name)){
            return i;
        }
    }
    return -1;
}

bool table_t::checkCol(cell_t* cell, string arg, string op, int type){
    if(type == VAL){
        int temp = atoi(arg.c_str());
		//cout<<temp<<" "<<cell->value.value<<" "<<op<<endl;
        if(op == "="){
            return temp == cell->value.value;
        }
        if(op == "<"){
            return temp > cell->value.value;
        }
        if(op == ">"){
			//cout<<"@#$@#$";
            return temp < cell->value.value;
        }
        if(op == "<="){
            return temp >= cell->value.value;
        }
        if(op == ">="){
            return temp <= cell->value.value;
        }
        if(op == "!="){
            return temp != cell->value.value;
        }
    }
    if(type == STR){
		arg = arg.substr(1,arg.size()-2);
		//cout<<arg<<endl;
        if(op == "="){
            return arg.compare(cell->value.str) == 0;
        }
        if(op == ">"){
            return arg.compare(cell->value.str) < 0;
        }
        if(op == "<"){
            return arg.compare(cell->value.str) > 0;
        }
        if(op == ">="){
            return arg.compare(cell->value.str) <= 0;
        }
        if(op == "<="){
            return arg.compare(cell->value.str) >= 0;
        }
        if(op == "!="){
            return arg.compare(cell->value.str) != 0;
        }
    }
}

string flip(string op){
    if(op == ">")
        return "<";
    if(op == "<")
        return ">";
    if(op == ">=")
        return "<=";
    if(op == "<=")
        return ">=";
    return op;
}

bool table_t::eval1(vector<constraint> expr, int flag, cell_t *cells[]){

    bool result = true;
	
    for(int i = 0 ; i < expr.size() ; i++){
        constraint t = expr[i];
		//cout<<t.opt1<<" "<<t.opt2<<endl;
        bool current = true;
		
        switch(t.opt1){
            case COLUMN : 
                if(t.opt2 != COLUMN){
                    int t1 = getColNum(t.operand1);
                    if(t1 == -1){
                        return false;
                    }
                    if(attributeList[t1].attr_type == t.opt2){
                        current = checkCol(cells[t1],t.operand2,t.op,attributeList[t1].attr_type);
					}
                    else
                        return false;
                }
				break;
            case INTEGER :
            case STRING : 
                if(t.opt2 == t.opt1){
                    //current = simpleComp(t.operand1,t.operand2,t.op);
                    current = true;
                }
                else if(t.opt2 == COLUMN){
                    int t1 = getColNum(t.operand2);
                    current = checkCol(cells[t1],t.operand1,flip(t.op),attributeList[t1].attr_type);
                }
                else{
                    current = false;
                }
                break;
        }
		//cout<<current<<endl;
		if(i == 0){
			result = current;
		}
        else if(flag){
            result = result || current;
        }
        else{
            result = result && current;
        }
    }
	return result;
}

void table_t::printTable(vector<string> col_id ,vector<constraint> expr, int flag)
{
	
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
		if(Find(attr[i].attr_name,col_id)){
			printf("%12s\t",attr[i].attr_name.c_str());
			
		}
		cells[i] = attr[i].cell;
	}

	cout<<endl;

	//Print table data
	//Col-wise print
	for(int i=0; i<rownum ; i++){
		// Row-wise print
        if(eval1(expr,flag,cells)){
            for(int j=0; j<colnum;j++){
                if(attr[j].attr_type == STR && Find(attr[j].attr_name,col_id)){
                    printf("%12s\t",cells[j]->value.str);
                }
                else{
                    if(Find(attr[j].attr_name,col_id))
                    {
                        printf("%12d\t",cells[j]->value.value);
                    }
                }
                cells[j] = cells[j]->next;
            }
            cout << "\n";
        }
		else{
			for(int j = 0 ; j < colnum ;j++){
				cells[j] = cells[j]->next;
			}
		}
	}
}

void table_t::printTable(vector<constraint> constr, int flag){

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
	cout<<endl<<endl;

	//Print all attr names
	//Initialize 'cells' pointer array
	for(int i=0 ; i<colnum ; i++){
		//cout << attr[i].attr_name << "\t";
		printf("%12s\t",attr[i].attr_name.c_str());
		cells[i] = attr[i].cell;
	}

	cout<<endl;

	//Print table data
	//Col-wise print
	for(int i=0; i<rownum ; i++){
		// Row-wise print
		if(eval1(constr,flag,cells)){
			for(int j=0; j<colnum;j++){
				if(attr[j].attr_type == STR){
					//cout << cells[j]->value.str << "\t";
					printf("%12s\t",cells[j]->value.str);
				}
				else{
					//cout << cells[j]->value.value << "\t";
					printf("%12d\t",cells[j]->value.value);
				}
				cells[j] = cells[j]->next;
			}
			cout << "\n";
		}
		else{
			for(int j = 0 ; j < colnum ; j++){
				cells[j] = cells[j]->next;
			}
		}
	}
}


//------------------------ //

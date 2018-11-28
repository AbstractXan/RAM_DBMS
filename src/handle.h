#ifndef __HANDLE_H__
#define __HANDLE_H__

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

#ifndef MAXMSG
#define MAXMSG 100
#endif

#ifndef MAXSTR
#define MAXSTR 100
#endif

typedef enum { STR, VAL } attrtype_t;
typedef enum { SUCC, FAIL } resmsg_t;
typedef enum { CASCADE, SETDEFAULT, SETNULL } ondelete_t;
typedef struct cell_t cell_t;
typedef struct attr_t attr_t;
typedef struct table_t table_t;
typedef struct database_t database_t;
typedef struct col_t col_t;
typedef struct result_t result_t;

class tokenList{

    public:
	vector<string> list;
    string front();
    int listLength();
    void append(string);
    void next();
};

/* Union for storing attribute values. Either string or integer */
typedef union {
	char str[MAXSTR];
	float value;
}attrval_t;

/* Each cell in the table */
struct cell_t {
	attrval_t value;
	cell_t *next;
};

/* Stores the attribute and corresponding information */
struct attr_t {
	string attr_name;
	cell_t *cell;
	attrtype_t attr_type;
	bool isPK;
	bool isFK;
	bool isNotNull;
	bool hasDefault;
	attrval_t defaultVal;
	ondelete_t onDelete;
};

struct col_t {
	string name;
	attrtype_t type;
	bool isPK;
	bool isFK;
	bool isNotNull;
	bool hasDefault;
	attrval_t defaultVal;
	ondelete_t onDelete;
};

/* Stores the table */
struct table_t{
	int rows;
	int cols;
	string tableName;
	attr_t *attributeList;
	table_t *nextTable;
	void printTable();
	bool insertValue(cell_t *row[]);
	void insertValues();
};

/* Stores the database. Only one global instance is required */
struct database_t {
	table_t *firstTable;
	table_t *findTable(string tableName);
	result_t *createTable(string tablename, int colNum, col_t* colList);
	void displayData();
};

/* Result type returned after query */
struct result_t{
	resmsg_t status;
	char msg[MAXMSG]; //carries any message
	int rows;
	int cols;
	string attr_names;
	attrtype_t *attr_types;
	attrval_t **cell;
};

/* Database handle */
typedef struct {
	result_t* exec(tokenList query);
	database_t *currentDB;
	void clear();
}handle_t;

extern handle_t* get_handle();
extern void delete_handle(handle_t *handle);


// Input //
tokenList getInput();

void selectFromTable(tokenList tokens, handle_t *handle);

// ERROR HANDLING //
void Error(string str);

#endif

#include <stdio.h>

#ifndef MAXMSG
#define MAXMSG 100
#endif

#ifndef MAXSTR
#define MAXSTR 100
#endif

typedef enum { STR, VAL } attrtype_t;
typedef enum { SUCC, FAIL } resmsg_t;
typedef struct cell_t cell_t;
typedef struct attr_t attr_t;
typedef struct table_t table_t;
typedef struct database_t database_t;

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
	char *attr_names;
	cell_t *cell;
	int attr_type;
	bool isPK;
	bool isFK;
	bool isNotNull;
	bool hasDefault;
	attrval_t defaultVal;
};

/* Stores the table */
struct table_t{
	int rows;
	int cols;
	attr_t *attributeList;
	table_t *nextTable;
};

/* Stores the database. Only one global instance is required */
struct database_t {
	table_t *firstTable;
};

/* Result type returned after query */
typedef struct {
	resmsg_t status;
	char msg[MAXMSG]; //carries any message
	int rows;
	int cols;
	char *attr_names;
	attrtype_t *attr_types;
	attrval_t **cell;
}result_t;

/* Database handle */
typedef struct {
	result_t*  (*exec)(char *query);
}handle_t;

extern handle_t* get_handle();

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

typedef union {
	char str[MAXSTR];
	float value;
}attrval_t;

struct cell_t {
	attrval_t value;
	cell_t *next;
};

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

struct table_t{
	int rows;
	int cols;
	attr_t *attributeList;
	table_t *nextTable;
};

struct database_t {
	table_t *firstTable;
};

typedef struct {
	resmsg_t status;
	char msg[MAXMSG]; //carries any message
	int rows;
	int cols;
	char *attr_names;
	attrtype_t *attr_types;
	attrval_t **cell;
}result_t;

typedef struct {
	result_t*  (*exec)(char *query);
}handle_t;

extern handle_t* get_handle();

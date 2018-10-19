#include <stdio.h>

#ifndef MAXMSG
#define MAXMSG 100
#endif

#ifndef MAXSTR
#define MAXSTR 100
#endif

typedef enum { STR, VAL } attrtype_t;
typedef enum { SUCC, FAIL } resmsg_t;

typedef union {
	char str[MAXSTR];
	float value;
}attrval_t;


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





/*
*Authorship statement 
*Zhe FU
*2462592f
*SP Exercise 1a 
*This is my own work as defined in the Academic Ethics agreement I have signed
*/
#define _XOPEN_SOURCE
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "date.h"


struct date
{
	time_t t;
};


Date *date_create(char *datestr)
{
	struct tm tt;
	memset(&tt, 0, sizeof(tt));
	if(!strptime(datestr, "%d/%m/%Y", &tt)) {
		return NULL;
	}
	
	Date* res = (Date*)malloc(sizeof(Date));
	if(!res) return NULL;
	
	res->t = mktime(&tt);
	return res;
}


Date *date_duplicate(Date *d)
{
	Date* res = (Date*)malloc(sizeof(Date));
	if(!res) return NULL;
	
	res->t = d->t;
	return res;
}


int date_compare(Date *date1, Date *date2)
{
	//printf("%d %d\n", (int)date1->t, (int)date2->t);
	if(date1->t < date2->t) return -1;
	if(date1->t > date2->t) return 1;
	return 0;
}


void date_destroy(Date *d)
{
	free(d);
}
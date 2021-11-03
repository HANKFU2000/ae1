/*
*Authorship statement 
*Zhe FU
*2462592f
*SP Exercise 1a 
*This is my own work as defined in the Academic Ethics agreement I have signed
*/
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tldlist.h"
#include "date.h"


struct tldnode
{
	char* tld;
	long count;
	struct tldnode* left;
	struct tldnode* right;
	struct tldnode* parent;
	int type;
};


struct tldlist
{
	struct tldnode* root;
	long count;
	Date* s;
	Date* e;
};


struct tlditerator
{
	struct tldnode* curr;
};



TLDList *tldlist_create(Date *begin, Date *end)
{
	TLDList *res = (TLDList *)malloc(sizeof(TLDList));
	if(!res) return NULL;
	res->root = NULL;
	res->count = 0;
	res->s = begin;
	res->e = end;
	return res;
}


TLDNode* tldnode_create(char* tld, TLDNode* p, int type)
{
	TLDNode* res = (TLDNode*)malloc(sizeof(TLDNode));
	if(!res) return NULL;
	
	res->tld = strdup(tld);
	if(!res->tld) {
		free(res);
		return NULL;
	}
	
	res->count = 1;
	res->left = NULL;
	res->right = NULL;
	res->parent = p;
	res->type = type;
	return res;
}


void tldnode_destroy(TLDNode* node)
{
	if(!node) return;
	
	tldnode_destroy(node->left);
	tldnode_destroy(node->right);
	free(node->tld);
	free(node);
}


int tldnode_insert(TLDNode* node, char* hostname)
{
	int ret = strcmp(node->tld, hostname);
	if(!ret) {
		node->count++;
		return 1;
	}
	if(ret < 0) {
		if(!node->left) {
			node->left = tldnode_create(hostname, node, 0);
			if(!node->left) {
				return 0;
			}
			return 1;
		}
		return tldnode_insert(node->left, hostname);
	}
	else {
		if(!node->right) {
			node->right = tldnode_create(hostname, node, 1);
			if(!node->right) {
				return 0;
			}
			return 1;
		}
		return tldnode_insert(node->right, hostname);
	}
}


TLDNode* tldnode_next(TLDNode* node)
{
	if(!node) {
		return NULL;
	}
	if(node->left) {
		return node->left;
	}
	if(node->right) {
		return node->right;
	}
	
	while(true) {
		int type = node->type;
		node = node->parent;
		if(!node) {
			return NULL;
		}
		if(!type && node->right) {
			return node->right;
		}
	}
	return NULL;
}



void tldlist_destroy(TLDList *tld)
{
	tldnode_destroy(tld->root);
	free(tld);
}


int tldlist_add(TLDList *tld, char *hostname, Date *d)
{
	if(date_compare(d, tld->s) < 0 || date_compare(d, tld->e) > 0) {
		return 0;
	}
	
	int pos = strlen(hostname);
	for(; pos >= 0; --pos) {
		if(hostname[pos] == '.') {
			break;
		}
	}
	++pos;
	
	if(!tld->root) {
		tld->root = tldnode_create(&hostname[pos], NULL, 0);
		if(!tld->root) {
			return 0;
		}
		tld->count++;
		return 1;
	}
	
	if(tldnode_insert(tld->root, &hostname[pos])) {
		tld->count++;
		return 1;
	}
	return 0;
}


long tldlist_count(TLDList *tld)
{
	return tld->count;
}


TLDIterator *tldlist_iter_create(TLDList *tld)
{
	TLDIterator *it = (TLDIterator *)malloc(sizeof(TLDIterator));
	it->curr = tld->root;
	return it;
}


TLDNode *tldlist_iter_next(TLDIterator *iter)
{
	TLDNode* res = iter->curr;
	iter->curr = tldnode_next(iter->curr);
	return res;
}



void tldlist_iter_destroy(TLDIterator *iter)
{
	free(iter);
}


char *tldnode_tldname(TLDNode *node)
{
	return node->tld;
}

long tldnode_count(TLDNode *node)
{
	return node->count;
}
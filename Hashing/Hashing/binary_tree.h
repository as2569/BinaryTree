#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef struct node_s
{
	void* data;
	unsigned long hash;
	struct node_s* right;
	struct node_s* left;
}Node;

Node* create(void* new_data, unsigned long new_hash);

unsigned long hash_function(char* str);

void add(Node** head, void* data, char* key);

void removeNode(Node** head, char* key);

void printCursor(Node* node);


#endif

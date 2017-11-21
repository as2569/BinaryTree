#include <stdio.h>
#include "binary_tree.h"

int escapeCount = 0;

Node* findMinimum(Node* this_node)
{
	Node* cursor = this_node;

	while (cursor->left != NULL)
	{
		cursor = cursor->left;
	}

	return cursor;
}

void removeNode(Node** head, char* key)
{
	printf("\n Remove %s", key);
	int amRight;

	unsigned long keyHash = hash_function(key);

	Node* parentCursor = NULL;
	Node* thisCursor = *head;

	if (*head == NULL)
	{
		printf("\n Head is null");
		return;
	}

	while (thisCursor && escapeCount < 20)
	{
		escapeCount++;
		//printf("\n Cursor at %p and prev %p", thisCursor, parentCursor);

		if (thisCursor->hash == keyHash)
		{
			printf("\n Found");
			if (parentCursor->left != NULL && parentCursor->left->hash == thisCursor->hash)
			{
				amRight = 0;
			}
			else
			{
				amRight = 1;
			}

			printf("\n Right %p, Left %p", thisCursor->right, thisCursor->left);
			if (thisCursor->right == NULL && thisCursor->left == NULL) // No children
			{
				if (amRight == 0)
				{
					parentCursor->left = NULL;
				}
				else
				{
					parentCursor->right = NULL;
				}
			}			
			else if (thisCursor->right != NULL && thisCursor->left != NULL) // 2 children
			{
				if (amRight == 0)
				{
					parentCursor->left = thisCursor->right;
					parentCursor->left->left = findMinimum(thisCursor->left);
					return;
				}
				else
				{
					parentCursor->right = thisCursor->right;
					parentCursor->right->left = findMinimum(thisCursor->left);
					return;
				}	
			}
			else //1 child
			{
				if (amRight == 0)
				{
					if (thisCursor->left != NULL)
					{
						parentCursor->left = thisCursor->left;
						return;
					}
					else
					{
						parentCursor->left = thisCursor->right;
						return;
					}
				}
				else
				{
					if (thisCursor->left != NULL)
					{
						parentCursor->right = thisCursor->left;
						return;
					}
					else
					{
						parentCursor->right = thisCursor->right;
						return;
					}				
				}
			}			
			return;
		}
		else if (thisCursor->hash > keyHash)
		{
			if (thisCursor->right == NULL)
			{
				//printf("\n NULL at %p", thisCursor);
				return;
			}
			parentCursor = thisCursor;
			thisCursor = thisCursor->right;
			//printf("\n going right");			
			continue;
		}
		else
		{
			if (thisCursor->left == NULL)
			{
				//printf("\n NULL at %p", thisCursor);
				return;
			}
			parentCursor = thisCursor;
			thisCursor = thisCursor->left;
			//printf("\n going left");			
			continue;
		}
	}
}

Node* create(void* new_data, unsigned long new_hash)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	memset(new_node, 0, sizeof(Node));
	new_node->data = new_data;
	new_node->hash = new_hash;
	new_node->right = NULL;
	new_node->left = NULL;
	return new_node;
}

//djb2
unsigned long hash_function(char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = ((hash << 5) + hash) + c;
	}

	return hash;	
}

void add(Node** head, void* data, char* key)
{	
	printf("\n Add %s", key);
	unsigned long tempHash = hash_function(key);

	Node* cursor = *head;

	Node* new_node = create((void*)key, tempHash); // create new node

	if (*head == NULL) // if head points to null, the head points to this node
	{
		*head = new_node;
		//printf("\n Adding at head %p", new_node);
		return;
	}

	while (cursor)
	{
		//printf("\n Cursor at %p", cursor);
		if (cursor->hash >= new_node->hash)
		{
			if (cursor->right == NULL)
			{
				cursor->right = new_node;
				//printf("\n Adding at right %p", new_node);
				return;
			}
			cursor = cursor->right;
			//printf("\n going right");
			continue;
		}
		else
		{
			if (cursor->left == NULL)
			{
				cursor->left = new_node;
				//printf("\n Adding at left %p", new_node);
				return;
			}
			cursor = cursor->left;
			//printf("\n going left");
			continue;
		}
	}
}

void printCursor(Node* node)
{
	if (node == NULL)
		return;

	printCursor(node->right);
	printf("\n %lu %s", node->hash, node->data);
	printCursor(node->left);
}

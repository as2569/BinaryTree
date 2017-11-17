#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "binary_tree.h"

Node* Head = NULL;

int main()
{
	int data = 11;
	char word1[16] = "hello";
	char word2[16] = "word";
	char word3[16] = "another";
	char word4[16] = "key";
	char word5[16] = "more";
	char word6[16] = "words";
	char word7[16] = "all";
	char word8[16] = "the";
	char word9[16] = "keys";
	char word10[16] = "long";

	add(&Head, &data, word1);
	add(&Head, &data, word2);
	add(&Head, &data, word3);
	add(&Head, &data, word4);
	add(&Head, &data, word5);
	add(&Head, &data, word6);
	add(&Head, &data, word7);
	add(&Head, &data, word8);
	add(&Head, &data, word9);
	add(&Head, &data, word10);

	printCursor(Head);

	removeNode(&Head, word10);

	printCursor(Head);

	getchar();
}
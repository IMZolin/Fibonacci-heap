#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996)
typedef struct node_t{
	int key;
	int degree;// vertex degree
	struct node_t* parent;
	struct node_t* child;
	struct node_t* left;
	struct node_t* right;
	bool marked;// was the child of this vertex deleted in the process of changing the key
	bool visited;
}node_t;

typedef struct fibonacci_heap_t {
	struct node_t* heap;
	int maxNodes;
}fibonacci_heap_t;

//Main functions
fibonacci_heap_t* Init();
void Display(fibonacci_heap_t* f_h);
node_t* findMin(fibonacci_heap_t* f_h);//O(1)
void Insert(fibonacci_heap_t* f_h, int value);//O(1)
node_t* extractMin(fibonacci_heap_t* f_h);//O(logn)
fibonacci_heap_t* Merge(fibonacci_heap_t* f_h1, fibonacci_heap_t* f_h2);//O(1)
bool decreaseKey(fibonacci_heap_t* f_h, int key, int new_key);//O(1)
void Delete(fibonacci_heap_t* f_h, int value);//O(logn)
//Support functions
node_t* newNode(int value);
void fibHeapLink(fibonacci_heap_t* f_h, node_t* y, node_t* x);
void Consolidate(fibonacci_heap_t* f_h);
void Cut(fibonacci_heap_t* f_h, node_t* node_decreased, node_t* parent_node);
void cascadingCut(fibonacci_heap_t* f_h, node_t* parent_node);
node_t* Find(node_t* heap, int value);


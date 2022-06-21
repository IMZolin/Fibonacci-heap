#include "heap.h"
fibonacci_heap_t* Init()
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	return f_h;
}

node_t* newNode(int value)
{
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->key = value;
	node->degree = 0;
	node->marked = false;
	node->visited = false;
	node->left = node;
	node->right = node;
	node->parent = NULL;
	node->child = NULL;
}

void Insert(fibonacci_heap_t* f_h, int value)
{
	node_t* new_node = newNode(value);
	if (f_h->heap == NULL)
	{
		f_h->heap = new_node;
	}
	else {
		f_h->heap->left->right = new_node;
		new_node->right = f_h->heap;
		new_node->left = f_h->heap->left;
		f_h->heap->left = new_node;
		if (new_node->key < f_h->heap->key)
			f_h->heap = new_node;
	}
	(f_h->maxNodes)++;
}

void Display(fibonacci_heap_t* f_h)
{
	node_t* node = f_h->heap;
	node_t* x;
	x = node;
	if (node == NULL)
		printf("The heap is empty\n");
	else {
		printf("The nodes of heap: \n");
		
		do {
			
			printf("(%d)", x->key);
			x = x->right;
			if (x != node)
				printf("-->");
		} while (x != node && x->right != NULL);
		printf("\n The Fibonacci heap has %d nodes\n", f_h->maxNodes);
	}
	/*for (x = node;; x = x->right)
	{
		if (x->child == NULL)
			printf("Node without child (%d) \n", x->key);
		else {
			printf("Node (%d) with child (%d)\n", x->key, x->child->key);
			Desplay(x->child);
		}
		if (x->right == node)
			break;
	}*/
}

node_t* findMin(fibonacci_heap_t* f_h)
{
	if (f_h == NULL)
	{
		printf("\nThe Fibonach heap has not been created yet\n");
		return NULL;
	}
	else
	{
		return f_h->heap;
	}
}

fibonacci_heap_t* Merge(fibonacci_heap_t* f_h1, fibonacci_heap_t* f_h2)
{
	fibonacci_heap_t* f_h3 = Init();
	f_h3->heap = f_h1 ->heap;
	node_t *tmp1, *tmp2;
	tmp1 = f_h3->heap->right;
	tmp2 = f_h2->heap->left;
	f_h3->heap->right->left = f_h2->heap->left;
	f_h3->heap->right = f_h2->heap;
	f_h2->heap->left = f_h3->heap;
	tmp2->right = tmp1;
	if ((f_h1->heap == NULL) || ((f_h2->heap != NULL) && (f_h2->heap->key < f_h1->heap->key)))
		f_h3->heap = f_h2->heap;
	f_h3->maxNodes = f_h1->maxNodes + f_h2->maxNodes;
	return f_h3;
}

int calcDegree(int n)
{
	int count = 0;
	while (n > 0)
	{
		n = n / 2;
		count++;
	}
	return count;
}

void fibHeapLink(fibonacci_heap_t* f_h, node_t* y, node_t* x)
{
	y->right->left = y->left;
	y->left->right = y->right;
	if (x->right == x)
		f_h->heap = x;
	y->left = y;
	y->right = y;
	y->parent = x;
	if (x->child == NULL)
		x->child = y;
	y->right = x->child;
	y->left = x->child->left;
	x->child->left->right = y;
	x->child->left = y;
	if ((y->key) < (x->child->key))
		x->child = y;
	(x->degree)++;
}

void Consolidate(fibonacci_heap_t* f_h)
{
	int degree, i, d;
	degree = calcDegree(f_h->maxNodes);

	node_t** A = (node_t**)malloc(sizeof(node_t*)*degree);
	node_t* x, * y, * z;
	for (int i = 0; i <= degree; i++)
	{
		A[i] = NULL;
	}
	x = f_h->heap;
	do {
		d = x->degree;
		while (A[d] != NULL)
		{
			y = A[d];
			if (x->key > y->key)
			{
				node_t* ex_help;//exchange help
				ex_help = x;
				x = y;
				y = ex_help;
			}
			if (y == f_h->heap)
				f_h->heap = x;
			fibHeapLink(f_h, y, x);
			if (y->right == x)
				f_h->heap = x;
			A[d] = NULL;
			d++;
		}
		A[d] = x;
		x = x->right;
	} while (x != f_h->heap);
	f_h->heap = NULL;
	for (int i = 0; i < degree; i++)
	{
		if (A[i] != NULL)
		{
			A[i]->left = A[i];
			A[i]->right = A[i];
			if (f_h->heap == NULL)
				f_h->heap = A[i];
			else {
				f_h->heap->left->right = A[i];
				A[i]->right = f_h->heap;
				A[i]->left = f_h->heap ->left;
				f_h->heap->left = A[i];
				if (A[i]->key < f_h->heap->key)
					f_h->heap = A[i];
			}
			if (f_h->heap == NULL)
				f_h->heap = A[i];
			else if (A[i]->key < f_h->heap->key)
				f_h->heap = A[i];
		}

	}
}

node_t* extractMin(fibonacci_heap_t* f_h)
{
	if (f_h->heap == NULL)
		printf("\n The heap is empty");
	else {
		node_t* tmp = f_h->heap;
		node_t* pntr;
		pntr = tmp;
		node_t* x = NULL;
		do {
			pntr = x ->right;
			(f_h->heap->left)->right = x;
			x->right = f_h->heap;
			x->left = f_h->heap->left;
			f_h->heap->left = x;
			if (x->key < f_h->heap->key)
				f_h->heap = x;
			x->parent = NULL;
			x = pntr;
		} while (pntr != tmp->child);
		(tmp->left)->right = tmp->right;
		(tmp->right)->left = tmp->left;
		f_h->heap = tmp->right;
		if (tmp = tmp->right && tmp->child == NULL)
			f_h->heap = NULL;
		else {
			f_h->heap = tmp->right;
			Consolidate(f_h);
		}
		(f_h->maxNodes)--;
		return tmp;
	}
	return f_h->heap;
}
void Cut(fibonacci_heap_t* f_h, node_t* node_decreased, node_t* parent_node)
{
	node_t* tmp_parent_check;
	if (node_decreased == node_decreased->right)
		parent_node->child = NULL;
	node_decreased->left->right = node_decreased->right;
	node_decreased->right->left = node_decreased->left;
	if (node_decreased == parent_node->child)
		parent_node->child = node_decreased->right;
	(parent_node->degree)--;
	node_decreased->left = node_decreased;
	node_decreased->right = node_decreased;
	f_h->heap->left = node_decreased;
	node_decreased->parent = NULL;
	node_decreased->marked = false;
}
void cascadingCut(fibonacci_heap_t* f_h, node_t* parent_node)
{
	node_t* aux;
	aux = parent_node->parent;
	if (aux != NULL)
	{
		if (parent_node->marked == false)
			parent_node->marked = true;
		else {
			Cut(f_h, parent_node, aux);
			cascadingCut(f_h, aux);
		}
	}
}

void decreaseKey(fibonacci_heap_t* f_h, node_t* node_decreased, int new_key)
{
	node_t* parent_node;
	if (f_h == NULL)
	{
		printf("\n The Fibonacci heap has not been created yet");
		return;
	}
	if (node_decreased == NULL)
		printf("Node is not in the heap");
	else {
		if (node_decreased->key < new_key)
			printf("\nInvalid new key for decrease key operation\n");
		else {
			node_decreased->key = new_key;
			parent_node = node_decreased->parent;
			if ((parent_node != NULL) && (node_decreased->key < parent_node->key)) {
				Cut(f_h, node_decreased, parent_node);
				cascadingCut(f_h, parent_node);
			}
			if (node_decreased->key < f_h->heap->key)
				f_h->heap = node_decreased;
		}
	}
}

void Find(fibonacci_heap_t* f_h, int key, int new_key)
{
	node_t* node = f_h->heap;
	node_t* f = NULL;
	node->visited = true;
	if (node->key == key)
	{
		node->visited = false;
		f = node;
		decreaseKey(f_h, f, new_key);
	}
	if (node->child != NULL)
		Find(f_h, node->child, key, new_key);
	if ((node->right->visited != true))
		Find(f_h, node->right, key, new_key);
	node->visited = false;
}

void Delete(fibonacci_heap_t* f_h, int value)
{
	node_t* node = f_h->heap;
	node_t* p = NULL;
	if (node == NULL)
		printf("The heap is empty\n");
	else {
		Find(f_h,value,-5000);
		p = extractMin(f_h);
		if (p != NULL)
			printf("\nNode was deleted");
		else
			printf("\nNode wasn't deleted");
	}
}
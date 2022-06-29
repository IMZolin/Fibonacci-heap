#pragma warning(disable : 4996)
#include "gtest/gtest.h"
extern "C" {
#include "heap.h"
}

TEST(TestInit, CreateHeap)
{
	fibonacci_heap_t* f_h = Init();
	EXPECT_TRUE(f_h != NULL);
	EXPECT_TRUE(f_h->heap == NULL);
	free(f_h);
}

TEST(TestNewNode, CreateNewNode)
{
	double value = 1;
	node_t* node  = newNode(value);
	EXPECT_TRUE(node != NULL);
	EXPECT_TRUE(node->key = 1);
	free(node);
}

TEST(TestInsert, AddNewNode)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	Insert(f_h, 1);
	EXPECT_TRUE(f_h != NULL);
	EXPECT_TRUE(f_h->heap != NULL);
	EXPECT_TRUE(f_h->heap->key = 1);
	free(f_h);
}

TEST(TestInsert, Add2Nodes)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	Insert(f_h, 1);
	Insert(f_h, 2);
	EXPECT_TRUE(f_h != NULL);
	EXPECT_TRUE(f_h->heap != NULL);
	EXPECT_TRUE(f_h->heap->key = 1);
	EXPECT_TRUE(f_h->heap->left->key = 2);
	EXPECT_TRUE(f_h->heap->right->key = 2);
	free(f_h);
}

TEST(TestFindMin, TestError)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	node_t* node = findMin(f_h);
	EXPECT_TRUE(node == NULL);
	free(f_h);
}

TEST(TestFindMin, FindMin)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	node_t* node;
	int value = 1;
	node_t* new_node = (node_t*)malloc(sizeof(node_t));
	new_node->key = value;
	new_node->degree = 0;
	new_node->marked = false;
	new_node->visited = false;
	new_node->left = new_node;
	new_node->right = new_node;
	new_node->parent = NULL;
	new_node->child = NULL;
	f_h->heap = new_node;
	(f_h->maxNodes)++;
	node = findMin(f_h);
	EXPECT_TRUE(node != NULL);
	free(f_h);
}

TEST(TestMerge, Merge2heaps)
{
	fibonacci_heap_t* f_h1 = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h1->heap = NULL;
	f_h1->maxNodes = 0;
	fibonacci_heap_t* f_h2 = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h2->heap = NULL;
	f_h2->maxNodes = 0;
	fibonacci_heap_t* f_h3 = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h3->heap = NULL;
	f_h3->maxNodes = 0;
	int value = 1;
	node_t* new_node = (node_t*)malloc(sizeof(node_t));
	new_node->key = value;
	new_node->degree = 0;
	new_node->marked = false;
	new_node->visited = false;
	new_node->left = new_node;
	new_node->right = new_node;
	new_node->parent = NULL;
	new_node->child = NULL;
	f_h1->heap = new_node;
	(f_h1->maxNodes)++;
	value = 2;
	node_t* new_node2 = (node_t*)malloc(sizeof(node_t));
	new_node2->key = value;
	new_node2->degree = 0;
	new_node2->marked = false;
	new_node2->visited = false;
	new_node2->left = new_node2;
	new_node2->right = new_node2;
	new_node2->parent = NULL;
	new_node2->child = NULL;
	f_h2->heap = new_node2;
	(f_h2->maxNodes)++;
	f_h3 = Merge(f_h1, f_h2);
	EXPECT_TRUE(f_h3 != NULL);
	EXPECT_TRUE(f_h3->heap->key = 1);
	EXPECT_TRUE(f_h3->heap->right->key = 2);
	EXPECT_TRUE(f_h3->maxNodes = 2);
	free(f_h1);
	free(f_h2);
	free(f_h3);
}

TEST(TestExtractMin, TestError)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	node_t* min = extractMin(f_h);
	EXPECT_TRUE(min == NULL);
	free(f_h);
}

TEST(TestExtractMin, ExtractMin)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	int value = 1;
	node_t* new_node = (node_t*)malloc(sizeof(node_t));
	new_node->key = value;
	new_node->degree = 0;
	new_node->marked = false;
	new_node->visited = false;
	new_node->left = new_node;
	new_node->right = new_node;
	new_node->parent = NULL;
	new_node->child = NULL;
	f_h->heap = new_node;
	(f_h->maxNodes)++;
	value = 2;
	node_t* new_node2 = (node_t*)malloc(sizeof(node_t));
	new_node2->key = value;
	new_node2->degree = 0;
	new_node2->marked = false;
	new_node2->visited = false;
	new_node2->left = new_node2;
	new_node2->right = new_node2;
	new_node2->parent = NULL;
	new_node2->child = NULL;
	f_h->heap->left->right = new_node2;
	new_node2->right = f_h->heap;
	new_node2->left = f_h->heap->left;
	f_h->heap->left = new_node2;
	(f_h->maxNodes)++;
	node_t* min = extractMin(f_h);
	EXPECT_TRUE(min != NULL);
	EXPECT_TRUE(min = new_node);
	EXPECT_TRUE(min->key = 1);
	free(f_h);
}

TEST(TestDecreaseKey, DecreaseKey)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	int value = 3;
	node_t* node_decreased = (node_t*)malloc(sizeof(node_t));
	node_decreased->key = value;
	node_decreased->degree = 0;
	node_decreased->marked = false;
	node_decreased->visited = false;
	node_decreased->left = node_decreased;
	node_decreased->right = node_decreased;
	node_decreased->parent = NULL;
	node_decreased->child = NULL;
	f_h->heap = node_decreased;
	(f_h->maxNodes)++;
	int new_key = 1;
	decreaseKey(f_h, value, new_key);
	EXPECT_TRUE(f_h->heap->key  = 1);
	free(f_h);
}

TEST(TestDecreaseKey, TestError1)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	int value = 3;
	int new_key = 10;
	node_t* node_decreased = (node_t*)malloc(sizeof(node_t));
	node_decreased->key = value;
	node_decreased->degree = 0;
	node_decreased->marked = false;
	node_decreased->visited = false;
	node_decreased->left = node_decreased;
	node_decreased->right = node_decreased;
	node_decreased->parent = NULL;
	node_decreased->child = NULL;
	f_h->heap = node_decreased;
	(f_h->maxNodes)++;
	decreaseKey(f_h, value, new_key);
	EXPECT_TRUE(f_h->heap->key = 3);
	free(f_h);
}

TEST(TestDecreaseKey, TestError2)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	int value = 3;
	int new_key = 10;
	node_t* node_decreased = (node_t*)malloc(sizeof(node_t));
	node_decreased->key = value;
	decreaseKey(f_h, value, new_key);
	EXPECT_TRUE(f_h->heap == NULL);
	EXPECT_TRUE(node_decreased->key = 3);
	free(f_h);
}

TEST(TestDelete, TestError1)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	int k1 = f_h->maxNodes;
	int value = 1;
	Delete(f_h, value);
	int k2 = f_h->maxNodes;
	ASSERT_EQ(k1, k2);
	free(f_h);
}
TEST(TestDelete, DeleteElement)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	int value = 1;
	node_t* new_node = (node_t*)malloc(sizeof(node_t));
	new_node->key = value;
	new_node->degree = 0;
	new_node->marked = false;
	new_node->visited = false;
	new_node->left = new_node;
	new_node->right = new_node;
	new_node->parent = NULL;
	new_node->child = NULL;
	f_h->heap = new_node;
	(f_h->maxNodes)++;
	Delete(f_h, value);
	EXPECT_TRUE(f_h->heap == NULL);
	free(f_h);
}
TEST(TestDelete, TestError2)
{
	fibonacci_heap_t* f_h = (fibonacci_heap_t*)malloc(sizeof(fibonacci_heap_t));
	f_h->heap = NULL;
	f_h->maxNodes = 0;
	int value = 1;
	node_t* new_node = (node_t*)malloc(sizeof(node_t));
	new_node->key = value;
	new_node->degree = 0;
	new_node->marked = false;
	new_node->visited = false;
	new_node->left = new_node;
	new_node->right = new_node;
	new_node->parent = NULL;
	new_node->child = NULL;
	f_h->heap = new_node;
	(f_h->maxNodes)++;
	int val_del = 2;
	node_t* node = f_h->heap;
	Delete(f_h, val_del);
	EXPECT_TRUE(f_h->heap != NULL);
	free(f_h);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#include "heap.h"

int main(void)
{
	char ch;
	int num_insert, value, new_key;
	fibonacci_heap_t* f_h = Init();
	node_t *min, *extacted_min, *find_use;
	while (1)
	{
		printf("\Operations:\n i - insert\n p - print heap\n f - find minimum\n m - extract min \n k - decrease key\n r - remove \n q - quit\n");
		scanf("%c", &ch);
		switch (ch) {
		case 'i':
			printf("Enter number of nodes to be insert = ");
			scanf("%d", &num_insert);
			for (int i = 0; i < num_insert; i++)
			{
				printf("\n node %d and its key value = ", i);
				scanf("%d", &value);
				Insert(f_h, value);
			}
			break;
		case 'p':
			Display(f_h);
			break;
		case 'f':
			min = findMin(f_h);
			if (min == NULL)
				printf("There isn't min in heap");
			else {
				printf("\n min value = %d\n", min->key);
			}
			break;
		case 'm':
			if (f_h == NULL)
				printf("Fibonacci heap is empty");
			else {
				extacted_min = extractMin(f_h);
				printf("\n min value = %d\n", extacted_min->key);
			}
			break;
		case 'k':
			if (f_h == NULL)
				printf("Fibonacci heap is empty");
			else {
				printf(" \n node to be decreased = ");
				scanf(&value);
				printf(" \n enter the new key = ");
				scanf("%d", &new_key);
				find_use = f_h->heap;
				decreaseKey(f_h, find_use, value, new_key);
			}
			break;
		case 'r':
			if (f_h == NULL)
				printf("Fibonacci heap is empty");
			else {
				printf(" \n Enter node key to be deleted = ");
				scanf("%d", &value);
				Delete(f_h, value);
			}
			break;
		case 'q':
			free(f_h);
			exit(0);
		default:
			printf("Invalid choice ");
		}
	}
	return 0;
}
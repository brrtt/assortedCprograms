#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int size = 100000;

typedef int Key;
typedef int Item;

struct hashNode {
  Key key;
  Item data;
  struct hashNode *next;
};

typedef struct hashNode HashNode;

HashNode **hashTableArray = NULL;
int hashTableSize = 0;

void HTinit(int size)
{
  hashTableArray = malloc( size * sizeof(HashNode*) );

  // initialize - nothing is yet in the table
  int i;
  for(i=0; i<size; i++)
    hashTableArray[i] = NULL;
  
  hashTableSize = size;
}

int hash(Key key)
{
  unsigned int index =  ((unsigned)(key * 2341251)) % hashTableSize;

  return index;
}

void HTinsert(Key key, Item data)
{
  int index = hash(key);

  HashNode *tmp = malloc(sizeof(HashNode));
  tmp->key = key;
  tmp->data = data;

  // hashTableArray[index] is the head of a linked list for all the items
  // at this index

  tmp->next = hashTableArray[index];

  // update the head of the list to be this new item
  hashTableArray[index] = tmp;
}

int HTfind(Key k, Item *data)
{
  int index = hash(k);
  
  HashNode * head = hashTableArray[index];
  
  // loop through list looking for key k
  int comparisons = 0;

  while(head)
    {
      comparisons++;
      if (head->key == k)
	{
	  printf("Comparisons=%d\n",comparisons);

	  *data = head->data;
	  return 1;
	}
      
      head = head->next;
    }
  printf("Comparisons=%d\n",comparisons);

  return 0;
}


int main()
{
  int i;

  HTinit(size*10);

  srand(time(NULL));

  for(i=0; i<size; i++)
    {
      int key = rand() % (size*10); 
      HTinsert(key,key);
    }

  // is the number 3 in the array?

  Item data;
  int result = HTfind(3,&data);

  if (result)
    {
      printf("%d is in the array!\n", 3);
    }
  else
    {
      printf("%d is NOT in the array!\n", 3);
    }

  return 0;
}

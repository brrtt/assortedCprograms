#include <stdio.h>
#include <stdlib.h>

typedef struct item_def
{

} Item;

typedef struct list
{
  Item item;
  struct list *next;
} List;

List

void insert(Item item)
{
  List *tmp=malloc(sizeof(List));

  tmp->data=item;
  tmp->next=head;

  head=tmp;
}

int main()
{
  int i;
  for(i=0;i<100;i++)
    {
      insert(i);
    }
  List *tmp=head;
  while(tmp)
    {
      printf();
    }
  return 0;
}

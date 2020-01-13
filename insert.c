typedef struct node
{ int item;
  struct node * next;
} node_t;

node_t * head;

void insert(int item)
{
  node_t  * new =malloc(sizeof(struct node));
  new->item=item;
  new->next=head;
  head=new;
}
  

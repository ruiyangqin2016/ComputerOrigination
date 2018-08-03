
#define UNUSED_PARAMETER(x) (void)(x)

typedef struct lnode {
  struct lnode *next;
  char data;
} LNODE;

typedef struct llist {
  LNODE *head;
  LNODE *tail;
  unsigned int size;
} LLIST;

LLIST *create_list();
LNODE *create_node(char data);

void push_front(LLIST *llist, char data);
char pop_front(LLIST *llist);
void destroy_list(LLIST *llist);
char* get_string(LLIST *list);

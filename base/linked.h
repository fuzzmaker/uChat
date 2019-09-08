
typedef node{
	void *val;
	Node *next;
}Node;

Node *lk_head;
Node *cur_node;
int lk_size;

Node *create_linked();

void add(Node *linked,void *val);

void remove(Node *linked,void *val);

char *display();

void destroy(Node *linked);

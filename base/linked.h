
/*定义内部数据节点结构体*/
typedef struct node{
	void *val;
	struct node *next;
}Node;

typedef struct linked{
	Node *head;
	Node *tail;
	int size;
	int (*compareTo)(void *nd1,void *nd2);
	void (*insertNode)(Node *nd,void *val);
	void (*removeNode)(Node *nd,void *val);
}Linked;

/*初始化创建链表*/
Linked *init_linked(Linked *lkd);
/*销毁链表*/
void distroy_linked(Linked *lkd);
/*插入节点*/
static void insertNode(Linked *lkd,void *val);
/*删除节点*/
static void removeNode(Linked *lkd,void *val);


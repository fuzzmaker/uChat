#include<stdlib.h>
#include<stdio.h>
#include "linked.h"

Linked *create_linked(void *comparator){
	Linked *lkd=malloc(sizeof(Linked));
	lkd->head=NULL;
	lkd->size=0;
	if(comparator!=NULL){
		lkd->compareTo=comparator;
	}else{	
		lkd->compareTo=compareTo;
	}
	lkd->insertNode=&insertNode;
	lkd->removeNode=&removeNode;
}

static void insertNode(Linked *lkd,void *val){
	Node *new_node=malloc(sizeof(Node));
	new_node->val=val;
	new_node->next=NULL;
	if(lkd->head==NULL){
		lkd->head=new_node;
		printf("insert node\n");
	}else{
		Node *temp=lkd->head;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=new_node;
		printf("insert node\n");
	}
	(lkd->size)++;
}

static void removeNode(Linked *lkd,void *val){
	if(lkd->size<=0) return;
	Node *temp=lkd->head;
	Node *preNode=NULL;
	while(temp!=NULL){
		int cmp=lkd->compareTo(temp->val,val);
		if(cmp==0){
			printf("remove node\n");
			if(preNode==NULL){
				lkd->head=temp->next;
			}else{
				preNode->next=temp->next;
			}
			free(temp);
			(lkd->size)--;
			break;	
		}
		preNode=temp;
		temp=temp->next;
	}
}

static int compareTo(void *n1,void * n2){
	return *((int *)n1)-*((int *)n2);
}

void destroy(Linked *lkd){
	if(lkd->size==0) return;
	Node *temp=lkd->head;
	while(temp!=NULL){
		Node *oNext=temp->next;
		free(temp);
		temp=oNext;
	}
}

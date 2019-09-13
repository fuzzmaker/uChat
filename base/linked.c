#include<stdlib.h>
#include "linked.h"

void init_linked(Linked *lkd){
	lkd->head=NULL;
	lkd->tail=NULL;
	lkd->size=0;
	lkd->compareTo=NULL;
	lkd->insertNode;
	lkd->removeNode;
}

static void insertNode(Linked *lkd,void *val){
	Node *new_node=malloc(sizeof(Node));
	new_node->val=val;
	if(lkd->head==NULL){
		lkd->head=new_node;
		lkd->tail=new_node;
	}else{
		Node *tail=lkd->tail;
		tail->next=new_node;
	}
	lkd->size++;
}

static void removeNode(Linked *lkd,void *val){
	if(lkd->size==0) return;
	Node *temp=lkd->head;
	while(temp!=NULL){
		int cmp=lkd->compareTo(temp->val,val);
		if(cmp==0){
			Node *oNext=temp->next;
			free(temp);
			temp=oNext;
			lkd->size++;
			break;	
		}
	}
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

#include<stdlib.h>
#include "linked.h"

Node *create_linked(){
	lk_size=0;
	lk_head=NULL;
	cur_node=NULL;
	return lk_head;
}

void add(Node *linked,void *val){
	Node *new_node=malloc(sizeof(struct Node));
	new_node->val=val;
	if(cur_node==NULL){
		lk_head=new_node;
		cur_node=new_node;
	}else{
		cur_node->next=new_node;
	}
	lk_size++;
}

void remove(Node *linked,void *val){
	if(lk_size==0) return;
	Node *temp=lk_head;
	while(temp!=NULL){
		if(temp->val==val){
			Node *oNext=temp->next;
			free(temp);
			temp=oNext;
			lk_size++;
			break;	
		}
	}
}


char *display(Node *linked){
	
}


void destroy(){
	if(lk_size==0) return;
	Node *temp=lk_head;
	while(temp!=NULL){
		Node *oNext=temp->next;
		free(temp);
		temp=oNext;
	}
}

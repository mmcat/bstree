/*
 * =====================================================================================
 *
 *       Filename:  binarytree.cpp
 *
 *    Description: BST 
 *
 *        Version:  1.0
 *        Created:  03/14/2013 20:59:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef struct node{
	int value;
	struct node* left;
	struct node* right;
}node;

class btree{
	public:
		btree();
		virtual ~btree();
		int insertnode(int n);
		int deletenode(int n);
		int searchnode(int n);
		void print(node* s);
		node* root;

};

btree::btree(){
	root = NULL;
	

}

btree::~btree(){}

void btree::print(node* s){
	if(s==NULL) return;
	print(s->left);
	printf("%d ",s->value);
	print(s->right);

}

int btree::searchnode(int n){
	node* s = root;
	while(s&&s->value!=n){
		if(n<s->value){s=s->left;}
		else s=s->right;
	}
	if(s==NULL) return -1;
	else return 0;
}

int btree::insertnode(int n){
	node* newnode = new node;
	newnode->value = n;
	newnode->left = NULL;
	newnode->right = NULL;
	if(root==NULL) {root = newnode;return 0;}
	node* s = root;
	node* t = s;
	while(s){
		if(n<s->value) {t=s;s = s->left;}
		else if(n==s->value){printf("The node exist!\n");return -1;}
		else {t=s;s = s->right;}
	}
	if(n<t->value)  t->left = newnode;
	else t->right = newnode;
	return 0;

}

int btree::deletenode(int n){
	node* s = root;
	node* t = s;
	while(s&&s->value!=n){
		if(n<s->value){t=s;s = s->left;}
		else {t=s;s=s->right;}
	}
	if(s==NULL) return -1;
    if(s==root){
        if(s->right){
            node* r=s->right;
            while(r->left) r=r->left;
            r->left = s->left;
            root = s->right;

        }
        else root = s->left;
    }
	if(s==t->left){
		if(s->left==NULL)
			t->left = s->right;
		else if(s->right == NULL)
			t->left = s->left;
		else {
			node* r = s->right;
			while(r->left) r = r->left;
			r->left = s->left;
			t->left = s->right;
		}
	}
	if (s==t->right) {
		if(s->left==NULL)
			t->right = s->right;
		else if(s->right==NULL)
			t->right = s->left;
		else {
			node* r =s->right;
			while(r->left) r = r->left;
			r->left = s->left;
			t->right = s->right;
		}

	}
return 0;
}

void printusage(){

		printf("Usage: ./binarytree filename [argu] [value]\n \
-i value (insert a value in the binary tree)\n \
-s value (search a value in the binary tree)\n \
-d value (delete a value in the binary tree)\n");
}

int main(int argc,const char* argv[]){
	if(argc!=4||(strcmp(argv[2],"-s")!=0 && strcmp(argv[2],"-i")!=0 && strcmp(argv[2],"-d")!=0)){
		printusage();
		exit(0);
	}
	btree bt;
	
    char buffer[10];
    char* a;
    FILE* fp = fopen(argv[1],"r");
    if(fp==NULL) {printf("Cannot find file %s",argv[1]);}
    while(fgets(buffer,10,fp)){
        a=strtok(buffer,"\t\n");
        bt.insertnode(atof(a));

    }
    bt.print(bt.root);
    printf("\n");
	
	if(strcmp(argv[2],"-i")==0){
		if(bt.insertnode(atof(argv[3]))==0){
			printf("insert successfully:");
			bt.print(bt.root);
			printf("\n");
	}
	}
	if(strcmp(argv[2],"-d")==0){
		if(bt.deletenode(atof(argv[3]))==0){
			printf("delete successfully:");
			bt.print(bt.root);
			printf("\n");
		}
	}
	if(strcmp(argv[2],"-s")==0){
		if(bt.searchnode(atof(argv[3]))==0){
			printf("search successfully:");
		}
		else printf("Cannot find the value!\n");
	}
}

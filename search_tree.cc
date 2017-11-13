#include<iostream>
#include<stdint.h>
#include<unistd.h>
#include<stddef.h>
#include"search_tree.h"
int main()
{
	StNode* root=NULL;
	CreateRoot(root,20);
	InsertNode_ex(root,15);
	InsertNode_ex(root,25);
	InsertNode_ex(root,22);
	InsertNode_ex(root,30);
	InsertNode_ex(root,10);
	InsertNode_ex(root,12);
	InsertNode_ex(root,5);
	MidOrder(root);
	return 0;
}

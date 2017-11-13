#ifndef DATASTRUCT_SEARCH_TREE_H
#define DATASTRUCT_SEARCH_TREE_H
#include<iostream>
typedef int DataType;
struct Search_Tree_Node{
	DataType value;
	Search_Tree_Node* lchild;
	Search_Tree_Node* rchild;
	Search_Tree_Node* pchild;
	Search_Tree_Node(DataType x):value(x),lchild(nullptr),rchild(nullptr),pchild(nullptr){}
};
typedef Search_Tree_Node StNode;
void CreateRoot(StNode* &root,DataType x)
{
	if(root!=nullptr)
		root=nullptr;
	root=new StNode(x);
}
void InsertNode_ex(StNode* &root,DataType x)
{
	StNode* tmp=root;
	StNode* father=nullptr;
//	while(tmp->lchild!=nullptr||tmp->rchild!=nullptr)
	while(tmp!=NULL)
	{
		father=tmp;
		if(tmp->value>x)
			tmp=tmp->lchild;
		else if(tmp->value<x)
		{
			tmp=tmp->rchild;
		}/*else
		{
			return;
		}*/
	}
	StNode* s=new StNode(x);
	s->pchild=father;
	if(father->value>s->value)
		father->rchild=s;
	else
		father->lchild=s;
}
void InsertNode(StNode* &root,DataType x)
{
	if(root==nullptr)
	{
		StNode* s=new StNode(x);
	//	s->p=root;
		root=s;
	}
	if(root->value>x)
		InsertNode(root->lchild,x);
	else if(root->value<x)
		InsertNode(root->rchild,x);
	else 
		return;
}
void MidOrder(StNode* &root)
{
	if(root==nullptr)
		return;
	MidOrder(root->lchild);
	std::cout<<root->value<<"	";
	MidOrder(root->rchild);
}
StNode* FindMin(StNode* &v)
{
	StNode* tmp=v;
	while(tmp->lchild!=NULL)
	{
		tmp=tmp->lchild;
	}
	return tmp;
}
void Translate(StNode* &root,StNode* &u,StNode* &v)
{
	if(u->pchild==NULL)
	{
		root=v;
	}else if(u==u->pchild->lchild)
	{
		u->pchild->lchild=v;
	}else
	{
		u->pchild->rchild=v;
	}
	if(v!=nullptr)
	{
		v->pchild=u->pchild;
	}
}
void Delete_Node(StNode* root,StNode* z)
{
	if(z->rchild!=NULL)
		Translate(root,z,z->lchild);
	else if(z->lchild!=NULL)
	{
		Translate(root,z,z->rchild);
	}
	else
	{
		StNode* tmp=FindMin(z->rchild);
		if(z!=tmp->pchild)
		{
			Translate(root,tmp,tmp->rchild);
			tmp->rchild=z->rchild;
			tmp->rchild->pchild=tmp;
		}
		Translate(root,z,tmp);
		tmp->lchild=z->lchild;
		tmp->pchild=z->pchild;

	}
}
#endif

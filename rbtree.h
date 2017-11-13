#ifndef TEST_RBTREE_H
#define TEST_RBTREE_H

#include<unistd.h>
#include<stack>
#include<iostream>
#include<string>
#include<vector>
#include<stack>

typedef int data_type;

enum node_color
{
	red=1,
	black=2
};
struct rbtree_node
{
	data_type value;
	rbtree_node* parent;
	rbtree_node* left;
	rbtree_node* right;
	node_color color;
};
class Rbtree
{
private:
	void left_rotate(rbtree_node* x);
	void right_rotate(rbtree_node* y);
	void cover(rbtree_node* old,rbtree_node* news);
	bool remove_node(rbtree_node* root,rbtree_node* z);
	bool insert_node(rbtree_node* z);
	void insert_node_fixup(rbtree_node* s);
	void delete_node_fixup(rbtree_node* s);

private:
	//rbtree_node* find(rbtree_node* node,data_type x);
	rbtree_node* find_data_ex(rbtree_node* node,data_type data);
	rbtree_node* m_root;
	rbtree_node* m_nil;
	
public:
	Rbtree(){
		m_nil = new rbtree_node;
		m_nil ->value = -1;
		m_nil->color = black;
		m_nil->right = nullptr;
		m_nil->left = nullptr;
		m_nil->parent = nullptr;
		m_root =m_nil;
		
		}
	virtual ~Rbtree()
	{
		delete m_nil;
	}
	Rbtree(rbtree_node* s):m_root(s){}
	void pro_order();
	void in_order();
	void post_order();
	bool insert(data_type data);
	bool remove(data_type data);
	rbtree_node* successor(rbtree_node* z);
	rbtree_node* prosuccessor(rbtree_node* z);
	rbtree_node* min_node(rbtree_node* z);
	rbtree_node* max_node(rbtree_node* z);
	rbtree_node* find_data(data_type data);
	rbtree_node* get_root()const
	{
		return m_root;
	}
	//rbtree_node* find_last_common_node(rbtree_node* lh,rbtree_node* rh);
	
};
#endif

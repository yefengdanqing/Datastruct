#include"rbtree.h"

using namespace std;
void Rbtree::cover(rbtree_node* old,rbtree_node* news)
{
	if(old->parent == m_nil)
		m_root=news;
	else if(old->parent->left == old)
	{
		old->parent->left = news;
	}else
	{
		old->parent->right = news;
	}
	news->parent=old->parent;
}
void Rbtree::left_rotate(rbtree_node* x)
{
	rbtree_node* y =x->right;
	x->right = y->left;
	if(y->left!= m_nil)
	{
		y->left->parent = x;//保证y有非空节点
	}
	if(x->parent == m_nil)
	{
		m_root=y;
	}else if(x->parent->left == x)
	{
		x->parent->left = y;
	}else
	{
		x->parent->right = y;
	}
	y->left = x;
	y->parent=x->parent;
	x->parent = y;
}
void Rbtree::right_rotate(rbtree_node* y)
{
	rbtree_node* x = y->left;
	if(x->right != m_nil)
	{
		x->right->parent = y;
	}
	y->left = x->right;
	if(y->parent == m_nil)
	{
		m_root =x;
	}else if(y->parent->left == y)
	{
		y->parent->left = x;
	}else
	{
		y->parent->right =x;
	}
	x->parent = y->parent;
	x->right = y;
	y->parent =x;
}
bool Rbtree::insert_node(rbtree_node * z)
{

}
bool Rbtree::insert(data_type data)
{
	rbtree_node* p =new rbtree_node;
	p->parent = m_nil;
	p->color = red;
	p->left = m_nil;
	p->right = m_nil;
	p->value = data;
	rbtree_node* tmp =m_root;
	/*if(tmp == m_nil)
	{
		m_root=p;
		return true;
	}*/
	rbtree_node* y = m_nil;
	while(tmp !=m_nil)
	{
		y = tmp;
		if(data > tmp->value)
			tmp = tmp->right;
		else 
			tmp = tmp->left;
	}
	p->parent = y;
	if(y != m_nil)
	{
		if(data>y->value)
			y->right = p;
		else if(data< y->value)
			y->left = p;
		else 
			return false;
	}else
	{
		m_root = p;
		p->color = black;
		return true;
	}
	insert_node_fixup(p);
	return true;
}
void Rbtree::insert_node_fixup (rbtree_node* s)
{
	while(s->parent->color == red)
	{
		if(s->parent == s->parent->parent->left)
		{
			//rbtree_node* y =s.parent.parent;
			if(s->parent->parent->right->color== red)
			{
				s->parent->parent->right->color = black;
				s->parent->color=black;
				s->parent->parent->color = red;
				s = s->parent->parent;
			}else
			{
				if(s->parent->right == s)
				{
					s=s->parent;
					left_rotate(s);				
				}
				s->parent->color = black;
				s->parent->parent->color = red;
				right_rotate(s->parent->parent);
			}
			
		}else if(s->parent->parent->right == s->parent)
		{
			if(s->parent->parent->left->color == red)
			{
				s->parent->color = black;
				s->parent->parent->left->color = black;
				s->parent->parent->color = red;
				s =s->parent->parent;
			}else
			{
				if(s->parent->left == s)
				{
					s  =s->parent;
					right_rotate(s);
				}
				s->parent->color = black;
				s->parent->parent->color  = red;
				left_rotate(s->parent->parent);
			}
		}
		
	}
	m_root->color = black;
}
bool Rbtree::remove(data_type data)
{	
	rbtree_node* z=find_data(data);
	rbtree_node* y=z,*x=m_nil;
	node_color tmp_color=y->color;
	if(z->left == m_nil)
	{
		x=z->right;
		cover(z,z->right);
	}else if(z->right == m_nil)
	{
		x = z->left;
		cover(z,z->left);
	}else
	{
		y =successor(z);
		x=y->right;
		tmp_color = y->color;
		if(y->parent == z)
		{
			x->parent = y;
		}else
		{
			cover(y,y->right);
			y->right=z->right;
			y->right->parent =y;
			y->color = z->color;
		}
		cover(z,y);
		y->left = z->left;
		y->left->parent = y;
	}
	if(tmp_color == black)
	{
	  delete_node_fixup(x);
	}
	delete z;
	return true;
}
void Rbtree::delete_node_fixup(rbtree_node* s)
{	
	rbtree_node* w =m_nil;
	while(s != m_root && s->color == black)
	{
		if(s == s->parent->left)
		{
			w = s->parent->right;
			if(w->color == red)
			{
				w->color = black;
				w->parent->color = red;
				left_rotate(w->parent);
				w= s->parent->left;
			}
			if(w->left->color == black && w->right->color ==black)
			{
				w->color = black;
				s = s->parent;
			}else
			{
				if(w->left->color == black)
				{
					w->color = red;
					w->left->color = black;
					right_rotate(w);
					w=s->right;
				}
				w->color = w->parent->color;
				s->parent->color = black;
				left_rotate(s->parent);
				s = m_root;
			}
		}else if(s == s->parent->right)
		{
			w = s->left;
			if(w->color == red)
			{
				w->color = black;
				w->parent->color = red;
				right_rotate(w->parent);
				w = s->parent->left;
			}
			if(w->left->color == black&& w->right->color == black)
			{
				w->color =black;
				s = s->parent;
			}else
			{
				if(w->right->color == red)
				{
					w->color = red;
					w->right->color = black;
					left_rotate(w);
					w = s->parent;
				}
				w->color = s->parent->color;
				w->left->color = black;
				w->parent->color = black;
				right_rotate(w);
				s =m_root;
			}
		}
	}
	s->color =black;
}
rbtree_node* Rbtree::find_data(data_type x)
{
	rbtree_node* temp = m_root;
	while(temp!=m_nil)
	{
		if(temp->value == x)
			return temp;
		else if(temp->value > x)
			temp =temp->left;
		else
			temp = temp->right;
	}
	return m_nil;
}
rbtree_node* Rbtree::find_data_ex(rbtree_node* node,data_type x)
{
	if(node != m_nil)
	{
		if(x == node->value)
		{
			return node;
		}else if(x<node->value)
		{
			return find_data_ex(node->left,x);
		}else
		{
			return find_data_ex(node->right,x);
		}
	}
	return m_nil;
}
rbtree_node* Rbtree::min_node(rbtree_node* z)
{
	rbtree_node* temp =z;
	rbtree_node* y =m_nil;
	while(temp != m_nil)
	{
		y=temp;
		temp = temp->left;
	}
	return y;
}
rbtree_node* Rbtree::max_node(rbtree_node* z)
{
	rbtree_node* temp =z;
	rbtree_node* y =m_nil;
	while(temp != m_nil)
	{
		y=temp;
		temp=temp->right;
	}
	return y;
}
rbtree_node* Rbtree::successor(rbtree_node * z)
{
	rbtree_node* temp = z;
	if(temp == max_node(m_root))
		return m_nil;
	if(temp->right != m_nil)
	{
		return min_node(temp->right);
	}
	
	while(temp != m_nil&& temp==temp->parent->right)
	{
		temp = temp->parent;
	}
	return temp->parent;
}
rbtree_node* Rbtree::prosuccessor(rbtree_node* z)
{
	rbtree_node* temp =z;
	if(z == min_node(m_root))
	{
		return m_nil;
	}
	if(z->left != m_nil)
	{
		return max_node(temp->left);
	}
	while(temp != m_nil&&temp == temp->parent->left)
	{
		temp = temp->parent;
	}
	return temp->parent;	
}
void Rbtree::pro_order()
{
	rbtree_node* p = m_root;
	stack<rbtree_node*> temp_stack;
	//temp_stack.push(p);
	while(!temp_stack.empty()||p!=m_nil)
	{
		while(p != m_nil)
		{
			//temp_stack.push(p);
			cout<<"颜色："<<p->color<<" 值："<<p->value<<endl;
			temp_stack.push(p);
			p = p->left;
		}
		if(!temp_stack.empty())
		{
			p =temp_stack.top();
			temp_stack.pop();
			p =p ->right;
		}
	}
}
void Rbtree::in_order()
{
	rbtree_node* p =m_root;
	stack<rbtree_node*> temp_stack;
	while(p != m_nil|| !temp_stack.empty())
	{
		while(p != m_nil)
		{
			temp_stack.push(p);
			p = p->left;
		}
		if(!temp_stack.empty())
		{
			p = temp_stack.top();
			cout<<"颜色："<<p->color<<" 值："<<p->value<<endl;
			temp_stack.pop();
			p = p->right;
		}
	}
}
void Rbtree::post_order()
{
	rbtree_node* p = m_root;
	stack<rbtree_node*> temp_stack;
	rbtree_node* pre = m_nil;
	temp_stack.push(p);
	//while(p != m_nil|| !temp_stack.empty())
	while(!temp_stack.empty())
	{
		p = temp_stack.top();
		if((p->left == m_nil&& p->right ==m_nil)||pre != m_nil&&(p ->left == pre||p->right == pre))
		{
			//p = temp_stack.top();
			temp_stack.pop();
			cout<<"颜色："<<p->color<<" 值："<<p->value<<endl;
			pre = p;
		}
		else
		{
			if(p->right != m_nil)
				temp_stack.push(p->right);
			if(p->left != m_nil)
				temp_stack.push(p->left);
		}
	}
}
int main()
{
	Rbtree obj_test;
	if(obj_test.insert(8)==true)
		cout<<"insert success"<<endl;
	if(obj_test.insert(10)==true)
		cout<<"insert success"<<endl;
	if(obj_test.insert(5)==true)
		cout<<"insert success"<<endl;
	if(obj_test.insert(7)==true)
		cout<<"insert success"<<endl;
	if(obj_test.insert(3)==true)
		cout<<"insert success"<<endl;
	if(obj_test.insert(1)==true)
		cout<<"insert success"<<endl;
	if(obj_test.insert(11)==true)
		cout<<"insert success"<<endl;
	if(obj_test.insert(13)==true)
		cout<<"insert success"<<endl;
	if(obj_test.insert(15)==true)
		cout<<"insert success"<<endl;
	if(obj_test.insert(14)==true)
		cout<<"insert success"<<endl;
	if(obj_test.remove(14)==true)
		cout<<"insert success"<<endl;
	
	//rbtree_node* p =obj_test.get_root();
	cout<<"qianqu:"<<obj_test.prosuccessor(obj_test.find_data(3))->value<<endl;
	cout<<"qianqu:"<<obj_test.prosuccessor(obj_test.find_data(10))->value<<endl;
	
	obj_test.pro_order();
	cout<<"================================="<<endl;
	obj_test.in_order();
	cout<<"================================="<<endl;
	obj_test.post_order();
	return 0;
}

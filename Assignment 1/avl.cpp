#include <iostream>
using namespace std ;
struct point
{
	int x ;
	int y ;
};
struct line
{
	point p1 ;
	point p2 ;
};
struct Node
{
	line l ;
	struct Node *left ;
	struct Node *right ;
	int height ;
};
inline bool operator ==(const line l1, const line l2)
{
	return ((l1.p1.x == l2.p1.x) && (l1.p1.y == l2.p1.y) && (l1.p2.x == l2.p2.x) && (l1.p2.y == l2.p2.y));
}
inline bool operator !=(const line l1, const line l2)
{
	return !(l1 == l2);
}
inline bool operator <(const line l1, const line l2)
{
	return ((l1.p1.y > l2.p1.y) || ((l1.p1.y == l2.p1.y) && (l1.p1.x < l2.p1.x)));
}
inline bool operator >(const line l1, const line l2)
{
	return ((l1.p1.y < l2.p1.y) || ((l1.p1.y == l2.p1.y) && (l1.p1.x > l2.p1.x)));
}
ostream* operator <<(ostream &out, const Node* n)
{
	out << "((" << n->l.p1.x << "," << n->l.p1.y << "),(" << n->l.p2.x << "," << n->l.p2.y << ")," << n->height << ")) " ;
}
int h(struct Node *r);
struct Node *rr(struct Node *x);
struct Node *lr(struct Node *x);
int bf(struct Node *r);
struct Node* insert_node(struct Node* r, line x);
struct Node *lowest_node(struct Node* r);
struct Node *highest_node(struct Node* r);
struct Node* delete_node(struct Node* r, line x);
struct Node *above(struct Node* r, line x);
struct Node *below(struct Node* r, line x);
struct point create_point(int a, int b);
struct line create_line(int a, int b, int c, int d);
void preorder(struct Node *r);
void inorder(struct Node *r);
void postorder(struct Node *r);
int main()
{
	struct Node *avl = NULL ;
	struct line l ;
	struct point p ;
	int n ;
	cout << "Enter the number of points: " ;
	cin >> n ;
	cout << "Enter each point in the format x1 y1 x2 y2\n" ;
	for(int i = 0; i < n; i++)
	{
		int x1, y1, x2, y2 ;
		cin >> x1 >> y1 >> x2 >> y2 ;
		if(y1 > y2)
			l = create_line(x1, y1, x2, y2);
		else
			l = create_line(x2, y2, x1, y1);
		avl = insert_node(avl, l);
	}
	cout << "\nInorder Traversal: " ;
	inorder(avl);
	cout << "\nPreorder Traversal: " ;
	preorder(avl);
	cout << "\nPostorder Traversal: " ;
	postorder(avl);
}
int h(struct Node *n)
{
	if(n == NULL)
		return 0 ;
	return n->height ;
}
struct Node *rr(struct Node *x)
{
	struct Node *y = x->left ;
	struct Node *z = y->right ;
	y->right = x ;
	x->left = z ;
	x->height = max(h(x->left), h(x->right))+1 ;
	y->height = max(h(y->left), h(y->right))+1 ;
	return x ;
}
struct Node *lr(struct Node *x)
{
	struct Node *y = x->right ;
	struct Node *T2 = y->left ;
	y->left = x ;
	x->right = T2 ;
	x->height = max(h(x->left), h(x->right))+1 ;
	y->height = max(h(y->left), h(y->right))+1 ;
	return y ;
}
int bf(struct Node *n)
{
	if(n == NULL)
		return 0 ;
	return (h(n->left)-h(n->right));
}
struct Node* insert_node(struct Node* n, line x)
{
	if(n == NULL)
	{
		struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
		temp->l = x ;
		temp->left = NULL ;
		temp->right = NULL ;
		temp->height = 1 ;
		return temp ;
	}
	if(x < n->l)
		n->left = insert_node(n->left, x);
	else if(x > n->l)
		n->right = insert_node(n->right, x);
	else
		return n ;
	n->height = 1 + max(h(n->left),h(n->right));
	int balance = bf(n);
	if(balance > 1)
	{
		if(x < (n->left)->l)
			return rr(n);
		if(x > (n->left)->l)
		{
			n->left = lr(n->left);
			return rr(n);
		}
	}
	if(balance < -1)
	{
		if(x > (n->right)->l)
			return lr(n);
		if(x < (n->right)->l)
		{
			n->right = rr(n->right);
			return lr(n);
		}
	}
	return n ;
}
struct Node *lowest_node(struct Node* n)
{
	struct Node* cur = n ;
	while(cur->left != NULL)
		cur = cur->left ;
	return cur ;
}
struct Node *highest_node(struct Node* n)
{
	struct Node* cur = n ;
	while(cur->right != NULL)
		cur = cur->right ;
	return cur ;
}
struct Node *above(struct Node* n, line x)
{
	struct Node* pre = NULL ;
	struct Node* cur = n ;
	while(cur->l != x)
	{
		if(x > cur->l)
		{
			if(pre == NULL)
				pre = cur ;
			else
			{
				if(pre->l < cur->l)
					pre = cur ;
			}
		}
		if(x < cur->l)
			cur = cur->left ;
		else
			cur = cur->right ;
	}
	if(cur->left != NULL)
		return highest_node(cur->left);
	return pre ;
}
struct Node *below(struct Node* n, line x)
{
	struct Node* suc = NULL ;
	struct Node* cur = n ;
	while(cur->l != x)
	{
		if(x < cur->l)
		{
			if(suc == NULL)
				suc = cur ;
			else
			{
				if(suc->l >cur->l)
					suc = cur ;
			}
		}
		if(x < cur->l)
			cur = cur->left ;
		else
			cur = cur->right ;
	}
	if(cur->right != NULL)
		return lowest_node(cur->right);
	return suc ;
}
struct Node* delete_node(struct Node* r, line x)
{
	if(r == NULL)
		return r ;
	if(x < r->l)
		r->left = delete_node(r->left, x);
	else if(x > r->l)
		r->right = delete_node(r->right, x);
	else
	{
		if((r->left == NULL)||(r->right == NULL))
		{
			struct Node *temp ;
			if(r->left != NULL)
				temp = r->left ;
			else
				temp = r->right ;
			if(temp == NULL)
			{
				temp = r ;
				r = NULL;
			}
			else
				*r = *temp;
			free(temp);
		}
		else
		{
			struct Node* temp = lowest_node(r->right);
			r->l = temp->l;
			r->right = delete_node(r->right, temp->l);
		}
	}
	if(r == NULL)
		return r ;
	r->height = 1 + max(h(r->left),h(r->right));
	int balance = bf(r);
	if(balance > 1)
	{
		if(bf(r->left) >= 0)
			return rr(r);
		else
		{
			r->left = lr(r->left);
			return rr(r);
		}
	}
	if(balance < -1)
	{
		if(bf(r->left) >= 0)
			return lr(r);
		else
		{
			r->right = rr(r->right);
			return lr(r);
		}
	}
	return r ;
}
struct point create_point(int a, int b)
{
	struct point p ;
	p.x = a ;
	p.y = b ;
	return p ;
}
struct line create_line(int a, int b, int c, int d)
{
	struct line l ;
	l.p1 = create_point(a,b);
	l.p2 = create_point(c,d);
	return l ;
}
void preorder(struct Node *n)
{
	if(n != NULL)
	{
		cout << n ;
		preorder(n->left);
		preorder(n->right);
	}
}
void inorder(struct Node *n)
{
	if(n != NULL)
	{
		inorder(n->left);
		cout << n ;
		inorder(n->right);
	}
}
void postorder(struct Node *n)
{
	if(n == NULL)
		return ;
	postorder(n->left);
	postorder(n->right);
	cout << n ;
}

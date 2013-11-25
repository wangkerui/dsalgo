/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw5/1/
 * 
 * 
1:二叉树的操作

总时间限制: 1000ms 内存限制: 65535kB
描述
给定一棵二叉树，在二叉树上执行两个操作：
1. 节点交换
把二叉树的两个节点交换。

2. 前驱询问
询问二叉树的一个节点对应的子树最左边的节点。

输入
第一行输出一个整数t，代表测试数据的组数。

对于每组测试数据，第一行输入两个整数n m，n代表二叉树节点的个数，m代表操作的次数。

随后输入n行，每行包含3个整数X Y Z，对应二叉树一个节点的信息。X表示节点的标识，Y表示其左孩子的标识，Z表示其右孩子的标识。

再输入m行，每行对应一次操作。每次操作首先输入一个整数type。

当type=1，节点交换操作，后面跟着输入两个整数x y，表示将标识为x的节点与标识为y的节点交换。输入保证对应的节点不是祖先关系。

当type=2，前驱询问操作，后面跟着输入一个整数x，表示询问标识为x的节点对应子树最左的孩子。

1<=n<=100，节点的标识从0到n-1，根节点始终是0.
输出
对于每次询问操作，输出相应的结果。
样例输入
2
5 5
0 1 2
1 -1 -1
2 3 4
3 -1 -1
4 -1 -1
2 0
1 1 2
2 0
1 3 4
2 2
3 2
0 1 2
1 -1 -1
2 -1 -1
1 1 2
2 0
样例输出
1
3
4
2
*/
#include<iostream>
#include<stack>
#include<stdlib.h>
using namespace std;

#define LEFT 1
#define RIGHT 2

/* the defination of binary tree node */
typedef struct BinaryTreeNode{
	int i;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
}BinaryTreeNode, *BinaryTree;

/* construct binary tree */
BinaryTree*
construct(BinaryTree* bt, int len)
{
	for (int i = 0; i < len; ++i)
	{
		bt[i] = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
		bt[i]->i = i;
	}
	return bt;
}

/* link nodes */
BinaryTree*
link(BinaryTree* bt, int index, int left, int right)
{
	if (-1 == left) bt[index]->left = NULL;
	else bt[index]->left = bt[left];

	if (-1 == right) bt[index]->right = NULL;
	else bt[index]->right = bt[right];
	
	return bt;
}

/* destroy binary tree */
void
destruct(BinaryTree* bt, int len)
{
	for (int i = 0; i < len; ++i)
		free(bt[i]);
	return;
}

/* find the parent of a node.
 * tag tells that whether the node is left or right child of parent.
 */
BinaryTreeNode* 
parent(BinaryTree root, BinaryTreeNode* node, int* tag)
{
	if(root==NULL || node==root) return NULL;

	stack<BinaryTreeNode*> *s = new stack<BinaryTreeNode*>();
	s->push(NULL);
	BinaryTreeNode* p = root;
	while(p)
	{
		if (node==p->left) {*tag=LEFT; delete s; return p;}
		if (node==p->right) {*tag=RIGHT; delete s; return p;}

		if (p->right != NULL) s->push(p->right);
		if (p->left != NULL)
		{
			p = p->left;
		}
		else
		{
			p = s->top();
			s->pop();
		}
	}

	delete s;
	return NULL;
}

/* swap two nodes */
BinaryTree
swap(BinaryTree root, BinaryTreeNode* n1, BinaryTreeNode* n2)
{
	int tag1=0, tag2=0;
	BinaryTreeNode* p1 = parent(root, n1, &tag1);
	BinaryTreeNode* p2 = parent(root, n2, &tag2);

	if (tag1 == LEFT) p1->left = n2;
	if (tag1 == RIGHT) p1->right = n2;
	if (tag2 == LEFT) p2->left = n1;
	if (tag2 == RIGHT) p2->right = n1;

	return root;
}

/* find the leftest child of a node */
BinaryTreeNode*
leftest(BinaryTreeNode* node)
{
	if (node == NULL) return NULL;

	BinaryTreeNode* p = node;
	while ( p!=NULL && p->left!=NULL)
		p = p->left;

	return p;
}

/* main */
int
main()
{
	int t,n,m,x,y,z,type;

	cin>>t; // the number of test cases
	for(int i=0; i<t; ++i)
	{
		cin>>n>>m;
		BinaryTree* bt = (BinaryTree*)malloc(sizeof(BinaryTree)*n);
		construct(bt, n); // allocate memory initially
		for(int j=0; j<n; ++j) // link
		{
			cin>>x>>y>>z;
			link(bt, x, y, z);
		}
		for(int j=0; j<m; ++j)
		{
			cin>>type;
			if (1==type)
			{
				cin>>x>>y;
				swap(*bt, bt[x], bt[y]);
			}
			if (2==type)
			{
				cin>>x;
				BinaryTreeNode* l = leftest(bt[x]);
				cout<<l->i<<endl;
			}
		}
		destruct(bt, n); // deallocate memory
		free(bt);
	}
	return 0;
}




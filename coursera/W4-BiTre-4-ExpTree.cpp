/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw5/4/?lang=zh_CN
 * 
4:表达式·表达式树·表达式求值

总时间限制: 1000ms 内存限制: 65535kB
描述
众所周知，任何一个表达式，都可以用一棵表达式树来表示。例如，表达式a+b*c，可以表示为如下的表达式树：

   +
  / \
a   *
    / \
    b c

现在，给你一个中缀表达式，这个中缀表达式用变量来表示（不含数字），请你将这个中缀表达式用表达式二叉树的形式输出出来。

输入
输入分为三个部分。
第一部分为一行，即中缀表达式。中缀表达式可能含有小写字母代表变量（a-z），也可能含有运算符（+、-、*、/、小括号），不含有数字，也不含有空格。
第二部分为一个整数n，表示中缀表达式的变量数。
第三部分有n行，每行格式为C　x，C为变量的字符，x为该变量的值。
输出
输出分为三个部分，第一个部分为该表达式的逆波兰式，即该表达式树的后根遍历结果。占一行。
第二部分为表达式树的显示，如样例输出所示。如果该二叉树是一棵满二叉树，则最底部的叶子结点，分别占据横坐标的第1、3、5、7……个位置（最左边的坐标是1），然后它们的父结点的横坐标，在两个子结点的中间。如果不是满二叉树，则没有结点的地方，用空格填充（但请略去所有的行末空格）。每一行父结点与子结点中隔开一行，用斜杠（/）与反斜杠（\）来表示树的关系。/出现的横坐标位置为父结点的横坐标偏左一格，\出现的横坐标位置为父结点的横坐标偏右一格。也就是说，如果树高为m，则输出就有2m-1行。
第三部分为一个整数，表示将值代入变量之后，该中缀表达式的值。需要注意的一点是，除法代表整除运算，即舍弃小数点后的部分。同时，测试数据保证不会出现除以0的现象。
样例输入
a+b*c
3
a 2
b 7
c 5
样例输出
abc*+
   +
  / \
 a   *
    / \
    b c
37
*/
#include<iostream>
#include<stack>
#include<queue>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

#define rept(i,s,e) for(i=s;i<e;++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=h;i>l;--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<n;++i)
#define per(i,n)    for(i=n;i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */

#define E -2

/* the defination of binary tree node */
typedef struct BinaryTreeNode{
	char c;
	int pos_low;
	int pos_high;
	int pos;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
}BinaryTreeNode, *BinaryTree;

/* construct binary tree by post order expression. */
BinaryTree
init(char* post_order_exp)
{
	if (NULL==post_order_exp) return NULL;

	int i = 0; char c;
	stack<BinaryTreeNode*> *s = new stack<BinaryTreeNode*>();
	while( (c=post_order_exp[i++])!='\0')
	{
		BinaryTreeNode* node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
		BinaryTreeNode* n1 = NULL;
		BinaryTreeNode* n2 = NULL;
		node->c = c;
		node->left = NULL;
		node->right = NULL;
		switch(c)
		{
		case '+': case '-': case '*': case '/':
			n1 = s->top();
			s->pop();
			n2 = s->top();
			s->pop();
			node->left = n2;
			node->right = n1;
			s->push(node);
			break;
		default: // 'a' - 'z'			
			s->push(node);
			break;
		}
	}
	if (!s->empty())
	{
		BinaryTreeNode* bt = s->top();
		s->pop();
		delete s;
		return bt;
	}
	delete s;
	return NULL;
}

/* destroy binary tree */
void
destroy(BinaryTree bt)
{
	if (NULL==bt) return;

	queue<BinaryTreeNode*> *q = new queue<BinaryTreeNode*>();
	BinaryTreeNode* p = bt;
	q->push(p);
	while(!q->empty())
	{
		p = q->front();
		q->pop();
		if(p->left!=NULL) q->push(p->left);
		if(p->right!=NULL) q->push(p->right);
		free(p); // 释放节点
	}

	delete q;
	return;
}

/* compute the height of binary tree */
int
bt_height(BinaryTree bt)
{
	if (NULL==bt) return 0;

	queue<BinaryTreeNode*> *q = new queue<BinaryTreeNode*>();
	BinaryTreeNode* p = bt;
	int height = 0;
	q->push(p);
	q->push(NULL); // 高度监视哨
	while(!q->empty())
	{
		p = q->front();
		q->pop();
		if (NULL==p)
		{
			++height;
			if (!q->empty()) // 未遍历完成
				q->push(NULL);
		}
		else
		{	
			if(p->left!=NULL) q->push(p->left);
			if(p->right!=NULL) q->push(p->right);
		}
	}

	delete q;
	return height;
}

/* set the position of every node */
BinaryTree
bt_set_nodes_pos(BinaryTree bt, int col)
{
	if (NULL==bt) return NULL;

	queue<BinaryTreeNode*> *q = new queue<BinaryTreeNode*>();
	bt->pos_low = 0;
	bt->pos_high = col-1;
	BinaryTreeNode* p = bt;
	q->push(p);
	while(!q->empty())
	{
		p = q->front();
		p->pos = (p->pos_low + p->pos_high) >> 1; // low and high divided by 2.

		if(p->left!=NULL) 
		{
			p->left->pos_low = p->pos_low;
			p->left->pos_high = p->pos - 1;
			q->push(p->left); // 左孩子入队
		}
		if(p->right!=NULL) 
		{
			p->right->pos_low = p->pos + 1;
			p->right->pos_high = p->pos_high;
			q->push(p->right); // 右孩子入队
		}
		
		q->pop(); // 队首出队
	}

	delete q;
	return bt;
}

/* visualize binary tree to matrix format */
char**
put_bt_in_matrix(BinaryTree bt, char** matrix)
{
	if (NULL==bt) return matrix;

	queue<BinaryTreeNode*> *q = new queue<BinaryTreeNode*>();
	BinaryTreeNode* p = bt;
	int level = 0;
	q->push(p);
	q->push(NULL); // 层数监视哨
	while(!q->empty())
	{
		p = q->front();
		q->pop();
		if (NULL==p)
		{
			++level;
			if (!q->empty()) // 未遍历完成
				q->push(NULL);
		}
		else
		{	
			int row_index = (level<<1); // 2*level
			matrix[row_index][p->pos] = p->c;
			if (p->left!=NULL)
			{	matrix[row_index+1][p->pos-1] = '/';
				q->push(p->left);
			}
			if (p->right!=NULL)
			{	matrix[row_index+1][p->pos+1] = '\\';
				q->push(p->right);
			}
		}
	}

	delete q;
	return matrix;
}

/* trim white spaces appending in every row */
char**
trim_matrix(char** matrix, int row, int col)
{
	int i,j;
	rep(i,row)
		for(j=col; matrix[i][j-1]==' '; --j)
			matrix[i][j-1] = '\0';

	return matrix;
}

/* print the matrix row by row. */
void
print_matrix(char** matrix, int row)
{
	int i;
	rep(i, row)
		printf("%s\n", matrix[i]);
}

/* return the length of string */
int
length(char* str)
{
	if (NULL==str) return 0;
	int len = 0;
	int i = 0;
	while(str[i++]!='\0') ++len;
	return len;
}

/* 中缀表达式-->后缀表达式 */
char*
in2post(char* post_order_exp, char* in_order_exp)
{
	if (NULL==in_order_exp) return NULL;
	
	/* 优先级矩阵 
	 * *=42 +=43 -=45 /=47 ascii
	 * 0：优先级相等；1：优先级高；-1：低；E：占位符
	 * 两个$行和$列是为索引方便而填充
	 该矩阵表示的转换规则如下：
	1.当读到一个操作数时，立即将它放到输出中。操作符则不立即输出，放入栈中。遇到左圆括号也推入栈中。
	2.如果遇到一个右括号，那么就将栈元素弹出，将符号写出直到遇到一个对应的左括号。但是这个左括号只被弹出，并不输出。
	3.在读到操作符时，如果此时栈顶操作符优先性{大于或等于}此操作符，弹出栈顶操作符直到发现优先级更低的元素位置。
	  除了处理）的时候，否则决不从栈中移走"（"。操作符中，+-优先级最低，（）优先级最高。
	4.如果读到输入的末尾，将栈元素弹出直到该栈变成空栈，将符号写到输出中。
	*/
	short priority[6][6] = {
		/*       *  +  $  -  $  /    */
		/* * */{ 0, 1, E, 1, E, 0},
		/* + */{-1, 0, E, 0, E,-1},
		/* $ */{ E, E, E, E, E, E},
		/* - */{-1, 0, E, 0, E,-1},
		/* $ */{ E, E, E, E, E, E},
		/* / */{ 0, 1, E, 1, E, 0}
	};
		
	// convert
	int i = 0, j = 0;
	char op;                      /* 操作符 */
	stack<char> *convertor = new stack<char>();
		
	while ( (op=in_order_exp[i++])!='\0')
	{
		switch(op)
		{
		case '(': 
			/* 左括号，直接入栈 */
			convertor->push(op);
			break;
		case ')': 
			/* 右括号，出栈直至遇到左括号 */
			while ( (op=convertor->top()) != '(') 
			{
				convertor->pop();
				post_order_exp[j++] = op;
			}
			convertor->pop(); /* pop '(' */
			break;
		case '+': case '-': case '*': case '/': 
			/* 加减乘除，弹出（左括号以上）且（比自己优先级高或相等）的运算符 */
			char top;
			while ( !convertor->empty() && (top=convertor->top())!='(' && priority[top-'*'][op-'*']>=0) 
			{
				convertor->pop();
				post_order_exp[j++] = top; 
			}
			convertor->push(op);
			break;
		default: // 'a' - 'z'
			/* 非操作符，直接存入表达式 */
			post_order_exp[j++] = op;
			break;
		}
	}
	while(!convertor->empty()) /* 表达式末尾，弹出栈内剩余元素（符号） */
	{
		post_order_exp[j++] = convertor->top();
		convertor->pop();
	}
	post_order_exp[j] = '\0'; // 字符串封尾
	
	delete convertor;
	return post_order_exp;
}

int
hash(char c)
{
	return (int)(c-'a');
}

int
eval(int a, int b, char op)
{
	switch(op)
	{
	case '+': return a+b;
	case '-': return a-b;
	case '*': return a*b;	
	case '/': return a/b;
	default: return 0;
	}
}

/* 计算后缀表达式的值 */
int
evaluate(char* exp, int* vals)
{
	stack<int> *computor = new stack<int>();
	int i=0;
	char c;
	while( (c=exp[i++])!='\0' )
	{
		int op1,op2;
		switch(c)
		{
		case '+': case '-': case '*': case '/': 
			op1 = computor->top();
			computor->pop();
			op2 = computor->top();
			computor->pop();		
			computor->push( eval(op2,op1,c) );
			break;
		default: // 'a' - 'z'
			computor->push(vals[hash(c)]);
		}
	}
	int result = computor->top();
	computor->pop();
	delete computor;
	return result;
}

/* main */
int
main()
{
	int i,j,n,x;
	char c;
	
	char* exp = (char*)malloc(sizeof(char)*100);
	cin>>exp;
	
	// 表达式长度
	int len = length(exp);
	// 中缀转后缀
	char* post_order_exp = (char*)malloc(sizeof(char)*(len+1));
	post_order_exp = in2post(post_order_exp, exp);
	// 输出后缀表达式
	printf("%s\n",post_order_exp);

	BinaryTree bt = init(post_order_exp);
	int height = bt_height(bt);
	int row = (height<<1)-1; // 2*height-1, 父子节点之间添加/\占据一行
	int col = (1<<height)-1; // 2^height-1，叶子节点之间隔一个位置
	
	// init matrix
	char** matrix = (char**)malloc(sizeof(char*)*(row));
	rep(i,row)
	{
		matrix[i] = (char*)malloc(sizeof(char)*(col+1));
		rep(j,col)
			matrix[i][j] = ' ';
		matrix[i][j] = '\0'; // 字符串末尾要加'\0'
	}

	bt_set_nodes_pos(bt, col);    // 设置结点的打印坐标
	put_bt_in_matrix(bt, matrix); // 打印字符填充至矩阵
	trim_matrix(matrix,row,col);  // 去掉末尾空格
	print_matrix(matrix, row);    // 打印矩阵

	// 表达式求值
	int* vals = (int*)malloc(sizeof(int)*26);
	cin>>n;
	rep(i,n)
	{	cin>>c>>x;
		vals[hash(c)] = x;
	}
	int result = evaluate(post_order_exp, vals);
	printf("%d\n", result);

	rep(i,row)
		free(matrix[i]);
	free(matrix);
	destroy(bt);
	free(post_order_exp);
	free(exp);
	return 0;
}

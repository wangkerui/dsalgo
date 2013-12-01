/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw5/3/
 *
3:由中根序列和后根序列重建二叉树

总时间限制: 500ms 内存限制: 65535kB
描述
我们知道如何按照三种深度优先次序来周游一棵二叉树，来得到中根序列、前根序列和后根序列。反过来，如果给定二叉树的中根序列和后根序列，或者给定中根序列和前根序列，可以重建一二叉树。本题输入一棵二叉树的中根序列和后根序列，要求在内存中重建二叉树，最后输出这棵二叉树的前根序列。

用不同的整数来唯一标识二叉树的每一个结点，下面的二叉树
  5
 / \
9  67
  /
 32

中根序列是9 5 32 67

后根序列9 32 67 5

前根序列5 9 67 32

输入
两行。第一行是二叉树的中根序列，第二行是后根序列。每个数字表示的结点之间用空格隔开。结点数字范围0～65535。暂不必考虑不合理的输入数据。
输出
一行。由输入中的中根序列和后根序列重建的二叉树的前根序列。每个数字表示的结点之间用空格隔开。
样例输入
9 5 32 67
9 32 67 5
样例输出
5 9 67 32
 */
#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<queue>
#include<string>
#include<vector>
#include<iostream>

using std::stack;
using std::queue;
using std::string;
using std::vector;
using std::cin;
using std::cout;

#define rept(i,s,e) for(i=int(s);i<int(e);++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=int(h);i>int(l);--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<int(n);++i)
#define per(i,n)    for(i=int(n);i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */
#define max(a,b)    ((a)>(b)?(a):(b))
#define min(a,b)    ((a)<(b)?(a):(b))

#define SEPARATOR (' ')

/* return the index of v in the array */
int
find(int* arr, int off, int len, int v)
{
  int i;
  rept(i,off,off+len)
    if (arr[i] == v)
      return i;
  return -1;
}

/* the definition of binary tree node */
typedef struct BinaryTreeNode
{
  int val;
  struct BinaryTreeNode* left;
  struct BinaryTreeNode* right;
} BiTreNd, *BiTre;

/* build binary tree from in_order and post_order sequence */
BiTre
build(int* in_order, int low1, int high1,
    int* post_order, int low2, int high2)
{
  if (low1 > high1) return NULL;
  if (low1 == high1)
  {
      BiTreNd* node = (BiTreNd*)malloc(sizeof(BiTreNd));
      node->val = in_order[low1];
      node->left = NULL;
      node->right = NULL;
      return node;
  }
  int size = high1-low1+1; // the size of sequence
  int index = find(in_order, low1, size, post_order[high2]);
  BiTreNd* node = (BiTreNd*)malloc(sizeof(BiTreNd));
  int left_size = index-low1; // the size of left child sequence
  node->val = in_order[index];
  node->left = build(in_order, low1, index-1,
      post_order, low2, low2+left_size-1);
  node->right = build(in_order, index+1, high1,
      post_order, low2+left_size, high2-1);
  return node;
}

/* destroy binary tree */
void
destroy(BiTre bt)
{
  if (NULL == bt) return;
  queue<BiTreNd*> *q = new queue<BiTreNd*>();
  BiTreNd* p = bt;
  q->push(p);
  while (!q->empty())
  {
      p = q->front();
      q->pop();
      if (p->left != NULL)
        q->push(p->left);
      if (p->right != NULL)
        q->push(p->right);
      free(p); // 释放节点
      p = NULL;
  }
  delete q;
  return;
}

/* pre-order travel*/
int*
pre_order_travel(BiTre bt, int* pre_order)
{
  int i = 0;
  BiTreNd* p = bt;
  stack<BiTreNd*> *s = new stack<BiTreNd*>();
  s->push(NULL); // 栈底监视哨
  while (!s->empty() || p)
  {
      if (p)
      {
          pre_order[i++] = p->val;
          if (p->right != NULL) s->push(p->right);
          p = p->left;
      }
      else
      {
          p = s->top();
          s->pop();
      }
  }
  delete s;
  return pre_order;
}

/* string to array of integers */
int*
str2arr(string str, int* size)
{
  vector<int> *v = new vector<int>();
  int i,val=0;
  char c;
  str = str + " ";
  rep(i,str.length())
    switch( (c=str.at(i)))
    {
    case SEPARATOR:
      v->push_back(val);
      val = 0;
      break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      val = val*10+(c-'0');
      break;
    }
  int* arr = (int*)malloc(sizeof(int)*v->size());
  rep(i,v->size())
    arr[i] = v->at(i);
  *size = v->size(); // record array size
  delete v;
  return arr;
}

/* array of integers to string */
void
print_arr(int* arr, int size)
{
  int i;
  rep(i,size)
  {
    printf("%d", arr[i]);
    if (i == size-1) return;
    printf(" ");
  }
}

/* main: program entry */
int
main()
{
  string line1 = "";
  string line2 = "";
  getline(cin,line1);
  getline(cin,line2);

  int size = 0;
  int* in_order = str2arr(line1,&size);
  int* post_order = str2arr(line2,&size);

  BiTre bt = build(in_order, 0, size-1, post_order, 0, size-1); // build BiTre
  int* pre_order = (int*)malloc(sizeof(int)*size);
  pre_order = pre_order_travel(bt, pre_order); // pre-order travel
  print_arr(pre_order,size);
  destroy(bt);     // release memory of nodes of binary tree

  free(post_order);
  free(in_order);
  return 0;
}

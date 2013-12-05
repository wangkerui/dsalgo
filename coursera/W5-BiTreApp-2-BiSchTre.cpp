/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw6/2/
 *
2:二叉搜索树

总时间限制: 1000ms 内存限制: 1024kB
描述
   二叉搜索树在动态查表中有特别的用处，一个无序序列可以通过构造一棵二叉搜索树变成一个有序序列，构造树的过程即为对无序序列进行排序的过程。
   每次插入的新的结点都是二叉搜索树上新的叶子结点，在进行插入操作时，不必移动其它结点，只需改动某个结点的指针，由空变为非空即可。

   这里，我们想探究二叉树的建立和序列输出。

输入
只有一行，包含若干个数字，中间用空格隔开。（数字可能会有重复）
输出
输出一行，对输入数字建立二叉搜索树后进行前序周游的结果。
样例输入
41 467 334 500 169 724 478 358 962 464 705 145 281 827 961 491 995 942 827 436
样例输出
41 467 334 169 145 281 358 464 436 500 478 491 724 705 962 827 961 942 995
 */
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<stack>
#include<iostream>

using std::queue;
using std::stack;
using std::cin;

#define rept(i,s,e) for(i=(int)(s);i<(int)(e);++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=(int)(h);i>(int)(l);--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<(int)(n);++i)
#define per(i,n)    for(i=(int)(n);i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */
#define max(a,b)    ((a)>(b)?(a):(b))
#define min(a,b)    ((a)<(b)?(a):(b))

#define LEFT 1
#define RIGHT 2

/* the definition and operation of binary tree */
typedef struct BinaryTreeNode
{
  int value;
  struct BinaryTreeNode* left;
  struct BinaryTreeNode* right;
} BiSchTreNd, *BiSchTre;

BiSchTre
insert(BiSchTre bt, int value)
{
  BiSchTreNd* nd = (BiSchTreNd*)malloc(sizeof(BiSchTreNd));
  nd->value = value;
  nd->left = NULL;
  nd->right = NULL;
  if (NULL == bt) return (bt = nd); // if binary tree is empty
  // else, find its appreciated parent.
  BiSchTreNd* curr = bt;
  BiSchTreNd* parent = NULL;
  int flag = LEFT;
  while (curr)
  {
      if (value == curr->value) return bt;
      else if (value < curr->value) parent = curr, curr = curr->left, flag = LEFT;
      else parent = curr, curr = curr->right, flag = RIGHT;
  }
  if (LEFT == flag) parent->left = nd;
  else parent->right = nd;
  return bt;
}

void
pre_order_travel(BiSchTre bt)
{
  if (NULL == bt) return;
  stack<BiSchTreNd*> *s = new stack<BiSchTreNd*>();
  BiSchTreNd* p = bt;
  s->push(NULL); // the bottom watch dog
  while (!s->empty() || p)
  {
      if (p)
      {
          printf("%d ", p->value);
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
  return;
}

/* destroy binary tree */
void
destroy(BiSchTre bt)
{
  if (NULL == bt) return;
  queue<BiSchTreNd*> *q = new queue<BiSchTreNd*>();
  BiSchTreNd* p = bt;
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
/* the end of definition and operation of binary tree */

/* main: program entry */
int
main()
{
  int val = 0;
  char c;
  BiSchTre bt = NULL;
  while ( (c=cin.get()) != '\n')
  {
      if (c != ' ')
      {
          cin.putback(c);
          cin>>val;
          bt = insert(bt, val);
      }
  }
  pre_order_travel(bt);
  destroy(bt);
  return 0;
}

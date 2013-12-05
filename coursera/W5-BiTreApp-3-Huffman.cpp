/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw6/3/
 *
3:Huffman编码树

总时间限制: 1000ms 内存限制: 65535kB
描述

构造一个具有n个外部节点的扩充二叉树，每个外部节点Ki有一个Wi对应，作为该外部节点的权。使得这个扩充二叉树的叶节点带权外部路径长度总和最小：
                                     Min( W1 * L1 + W2 * L2 + W3 * L3 + … + Wn * Ln)
Wi:每个节点的权值。
Li:根节点到第i个外部叶子节点的距离。
编程计算最小外部路径长度总和。
输入
第一行输入一个整数t，代表测试数据的组数。
对于每组测试数据，第一行输入一个整数n，外部节点的个数。第二行输入n个整数，代表各个外部节点的权值。
2<=N<=100
输出
输出最小外部路径长度总和。
样例输入
2
3
1 2 3
4
1 1 3 5
样例输出
9
17
提示
仅考查huffman树的建立，数据范围小，可以不需要使用堆结构.
不过鼓励使用第一题实现的堆来寻找最小和次小元素。
 */
#include<stdio.h>
#include<stdlib.h>
#include<queue>

using std::queue;

#define rept(i,s,e) for(i=(int)(s);i<(int)(e);++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=(int)(h);i>(int)(l);--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<(int)(n);++i)
#define per(i,n)    for(i=(int)(n);i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */
#define max(a,b)    ((a)>(b)?(a):(b))
#define min(a,b)    ((a)<(b)?(a):(b))

/* the definition and operation of binary tree */
typedef struct BinaryTreeNode
{
  int weight;
  struct BinaryTreeNode* left;
  struct BinaryTreeNode* right;
} BiTreNd, *BiTre;

BiTreNd*
merge(BiTreNd* n1, BiTreNd* n2)
{
  BiTreNd* new_nd = (BiTreNd*)malloc(sizeof(BiTreNd));
  new_nd->weight = n1->weight + n2->weight;
  new_nd->left = n1;
  new_nd->right = n2;
  return new_nd;
}

/* 外部节点加权路径长度 */
int
sum_weight(BiTre bt)
{
  if (NULL == bt) return 0;

  int sum = 0;
  int level = 0;
  queue<BiTreNd*> *q = new queue<BiTreNd*>();
  BiTreNd* p = bt;
  q->push(p);
  q->push(NULL); // level watch dog
  while (!q->empty())
  {
      p = q->front();
      q->pop();
      if (p)
      {
        if (p->left != NULL)
          q->push(p->left);
        if (p->right != NULL)
          q->push(p->right);
        if (p->left == NULL && p->right == NULL) // the leaf
          sum += p->weight*level;
      }
      else
      {
          ++level;
          if (!q->empty()) q->push(NULL);
      }
  }
  delete q;
  return sum;
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
/* the end of definition and operation of binary tree */

/* the definition of heap */
typedef struct Heap
{
  int size;
  BiTreNd** vals;
} Heap;

/* allocate heap memory */
Heap*
init(Heap* h, int max_len)
{
  h->size = 0;
  h->vals = (BiTreNd**)malloc(sizeof(BiTreNd*)*max_len);
  return h;
}

/* release heap memory */
void
destroy(Heap* h)
{
  free(h->vals);
  return;
}

void
shift_down(Heap* h, int position)
{
  if (position < 0 || position > h->size/2-1)
    return;
  int i = position;
  int j = i*2+1;    // left child
  if (j+1 < h->size && h->vals[j+1]->weight < h->vals[j]->weight)
    ++j;     // if right child (if exists) is smaller, then turn to it.
  BiTreNd* tmp = h->vals[i];
  while (j < h->size && tmp->weight > h->vals[j]->weight )
  {
      h->vals[i] = h->vals[j];
      i = j;
      j = j*2+1;
      if (j+1 < h->size && h->vals[j+1]->weight < h->vals[j]->weight)
          ++j;     // if right child (if exists) is smaller, then turn to it.
  }
  h->vals[i] = tmp;
}

void
shift_up(Heap* h, int position)
{
  if (position <= 0 || position >= h->size)
    return;
  int curr = position;
  int parent = (curr+1)/2-1;
  BiTreNd* tmp = h->vals[curr];
  while (curr > 0 && h->vals[parent]->weight > tmp->weight)
  {
      h->vals[curr] = h->vals[parent];
      curr = parent;
      parent = (curr+1)/2-1;
  }
  h->vals[curr] = tmp;
}

BiTreNd*
insert(Heap* h, int val)
{
  BiTreNd* nd = (BiTreNd*)malloc(sizeof(BiTreNd));
  nd->weight = val;
  nd->left = NULL;
  nd->right = NULL;
  h->vals[h->size++] = nd;
  shift_up(h, h->size-1);
  return nd;
}

BiTreNd*
insert(Heap* h, BiTreNd* nd)
{
  h->vals[h->size++] = nd;
  shift_up(h, h->size-1);
  return nd;
}

BiTreNd*
del(Heap* h, int position)
{
  BiTreNd* tmp = h->vals[position];
  h->vals[position] = h->vals[--h->size];
  h->vals[h->size] = tmp;
  int parent = (position+1)/2-1;
  if (parent >= 0 && h->vals[parent]->weight > h->vals[position]->weight)
    shift_up(h, position);
  else
    shift_down(h, position);
  return tmp;
}

BiTreNd*
remove_min(Heap* h)
{
  BiTreNd* tmp = h->vals[0];
  h->vals[0] = h->vals[--h->size];
  h->vals[h->size] = tmp;
  shift_down(h, 0);
  return tmp;
}
/* the end of definition and operation of heap  */

/* main: program entry */
int
main()
{
  int t = 0, i;
  scanf("%d\n", &t);
  rep(i,t)
  {
    int n = 0, j;
    scanf("%d\n", &n);
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h = init(h, n);
    rep(j,n)  // 初始化堆
    {
       int value = 0;
       scanf("%d", &value);
       insert(h, value);
    }
    // 构造Huffman树
    BiTre bt = NULL;
    while (h->size >= 2)
    {
        BiTreNd* n1 = remove_min(h);
        BiTreNd* n2 = remove_min(h);
        bt = insert(h, merge(n1, n2));
    }
    printf("%d\n", sum_weight(bt));
    // release memory
    destroy(bt);
    destroy(h);
    free(h);
  }
  return 0;
}

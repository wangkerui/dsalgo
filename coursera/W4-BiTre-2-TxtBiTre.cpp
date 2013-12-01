/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw5/2/
 *
2:文本二叉树

总时间限制: 1000ms 内存限制: 65536kB
描述

如上图，一棵每个节点都是一个字母，且字母互不相同的二叉树，可以用以下若干行文本表示:

A
-B
--*
--C
-D
--E
---*
---F


在这若干行文本中：

1) 每个字母代表一个节点。该字母在文本中是第几行，就称该节点的行号是几。根在第1行
2) 每个字母左边的'-'字符的个数代表该结点在树中的层次（树根位于第0层）
3) 若某第 i 层的非根节点在文本中位于第n行，则其父节点必然是第 i-1 层的节点中，行号小于n,且行号与n的差最小的那个
4) 若某文本中位于第n行的节点(层次是i) 有两个子节点，则第n+1行就是其左子节点，右子节点是n+1行以下第一个层次为i+1的节点
5) 若某第 i 层的节点在文本中位于第n行，且其没有左子节点而有右子节点，那么它的下一行就是 i+1个'-' 字符再加上一个 '*'


给出一棵树的文本表示法，要求输出该数的前序、后序、中序遍历结果
输入
第一行是树的数目 n

接下来是n棵树，每棵树以'0'结尾。'0'不是树的一部分
每棵树不超过100个节点
输出
对每棵树，分三行先后输出其前序、后序、中序遍历结果
两棵树之间以空行分隔
样例输入
2
A
-B
--*
--C
-D
--E
---*
---F
0
A
-B
-C
0
样例输出
ABCDEF
CBFEDA
BCAEFD

ABC
BCA
BAC
 */
#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<queue>

using std::stack;
using std::queue;

#define rept(i,s,e) for(i=int(s);i<int(e);++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=int(h);i>int(l);--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<int(n);++i)
#define per(i,n)    for(i=int(n);i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */
#define max(a,b)    ((a)>(b)?(a):(b))
#define min(a,b)    ((a)<(b)?(a):(b))

#define MAX_LEN 100

void
level_value(char* str, int* level, char* value)
{
  if (NULL == str) return;
  int l = 0, i = 0; char val;
  while ( (val=str[i++]) != '\0' && val == '-') ++l;
  *level = l; *value = val;
  return;
}

/* the definition of binary tree node */
typedef struct BinaryTreeNode
{
  char c;
  short visited;
  struct BinaryTreeNode* left;
  struct BinaryTreeNode* right;
  struct BinaryTreeNode* parent;
} BiTreNd, *BiTre;

/* build binary tree from stdin */
BiTre
build(int* num)
{
  char* str = (char*)malloc(sizeof(char)*(MAX_LEN+1));
  BiTreNd* curr = NULL;
  int curr_level = -1; // for first node
  while ( gets(str)[0] != '0') // input one line
  {
      int level = 0; char value = '\0';
      level_value(str, &level, &value);

      if ('*' != value) *num = *num + 1;

      BiTreNd* node = (BiTreNd*)malloc(sizeof(BiTreNd));
      node->c = value;
      node->visited = 0;
      node->left = NULL;
      node->right = NULL;
      if (-1 == curr_level) // root node
      {
          node->parent = NULL;
      }
      else if (level > curr_level)
      {
          curr->left = node;
          node->parent = curr;
      }
      else if (level == curr_level)
      {
          curr->parent->right = node;
          node->parent = curr->parent;
      }
      else if (level < curr_level)
      {
          int diff = curr_level-level;
          while (diff--) curr = curr->parent;
          curr->parent->right = node;
          node->parent = curr->parent;
      }
      curr = node; curr_level = level;
  }
  free(str);

  int diff = max(curr_level-0, 0);
  while(diff--) curr = curr->parent; // 回溯到根结点

  return curr;
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
char*
pre_order_travel(BiTre bt, char* pre_order)
{
  int i = 0;
  BiTreNd* p = bt;
  stack<BiTreNd*> *s = new stack<BiTreNd*>();
  s->push(NULL); // 栈底监视哨
  while (!s->empty() || p)
  {
      if (p)
      {
          if ('*' != p->c) // 过滤*结点（*结点代表NULL）
            pre_order[i++] = p->c;
          if (p->right != NULL) s->push(p->right);
          p = p->left;
      }
      else
      {
          p = s->top();
          s->pop();
      }
  }
  pre_order[i++] = '\0'; // 字符串封尾

  delete s;
  return pre_order;
}

/* post-order travel */
char*
post_order_travel(BiTre bt, char* post_order)
{
  if (NULL == bt) {post_order[0] = '\0'; return post_order;}
  int i = 0;
  BiTreNd* p = bt;
  stack<BiTreNd*> *s = new stack<BiTreNd*>();
  s->push(p);
  while (!s->empty())
  {
      p = s->top();
      if ( (p->left == NULL || p->left->visited)
          && (p->right == NULL || p->right->visited) )
      {
          if ('*' != p->c) {post_order[i++] = p->c;}
          p->visited = 1;
          s->pop();
      }
      if (p->right != NULL && !p->right->visited) s->push(p->right);
      if (p->left != NULL && !p->left->visited) s->push(p->left);
  }
  post_order[i++] = '\0';

  delete s;
  return post_order;
}

/* in-order travel */
char*
in_order_travel(BiTre bt, char* in_order)
{
  if (NULL == bt) {in_order[0] = '\0'; return in_order;}
  int i = 0;
  BiTreNd* p = bt;
  stack<BiTreNd*> *s = new stack<BiTreNd*>();
  s->push(p);
  while (!s->empty())
  {
      while ( p && (p = p->left) != NULL) s->push(p);
      p = s->top();
      s->pop();
      if ('*' != p->c) in_order[i++] = p->c;
      if ( (p = p->right) != NULL) s->push(p);
  }
  in_order[i++] = '\0';

  delete s;
  return in_order;
}

/* main: program entry */
int
main()
{
  int n = 0;
  scanf("%d\n", &n);
  int i;
  rep(i,n)
  {
    int size = 0;
    BiTre bt = build(&size); // build from stdin
    // pre-order
    char* pre_order = (char*)malloc(sizeof(char)*(size+1));
    pre_order = pre_order_travel(bt, pre_order);
    printf("%s\n", pre_order);
    // post-order
    char* post_order = (char*)malloc(sizeof(char)*(size+1));
    post_order = post_order_travel(bt, post_order);
    printf("%s\n", post_order);
    // in-order
    char* in_order = (char*)malloc(sizeof(char)*(size+1));
    in_order = in_order_travel(bt, in_order);
    printf("%s\n", in_order);

    free(pre_order);
    free(post_order);
    free(in_order);
    destroy(bt);

    printf("\n");
  }
  return 0;
}

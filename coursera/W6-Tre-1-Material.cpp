/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw7/1/
 *
1:物质分解记录

总时间限制: 60000ms 内存限制: 131064kB
描述
对 物质分解记录 的结构进行统计分析。
例如：
给出一份 物质分解记录。
Material_1
{
Material_2
{
Material_3
                Material_4
Material_5
                {
                Material_6
                Material_7
                }
                Material_8
}
Material_9
Material_10
}
Material_11
{
Material_l3
Material_7
Material_2
{
Material_3
                Material_4
Material_5
                {
             Material_6
             Material_7
                }
                Material_8
}
Material_13
}

上述记录的含义是，Material_1分解为 Material_2、Material_9和Material_10，Material_2又分解为Material_3、Material_4、Material_5和Material_8。以此类推，大括号外书写特定物质名称，括号内表示此特定物质分解出来的子物质名称，每个子物质还可再分解。

现输入一个物质名称R，要求输出所有和物质R在记录中属于同一层次且位置在R之后的物质名称。
比如R=“Material_1” ，则应该输出“Material_11”；
比如R=“Material_9” ，则应该输出“Material_10”
如果R在代码中出现了多次，则以其第一次出现为准，即仅输出与第一次出现的R属于同一层次且位置在R之后的语句内容。
比如R=“Material_2” ，则应该输出
        Material_9
Material_10

输入
输入包含多组数据。第一行是物质分解记录的份数，仅用一个整数表示。从第二行开始，每组数据包括 物质分解记录 和 所需查找的物质R 两部分，物质分解记录样式如描述中所示，R的内容和物质分解记录之间有一行空行，下一份记录与上一个R之间有两行空行。
若输入！则表示输入结束。
为简单起见，物质分解记录中每一行的内容为“{”或者“}”或者一个物质名称，不会有其他情况（比如空行）出现。同时每行文字前不会有任何缩进。物质名称是英文字母、数字和下划线组成的字符串。
输出
对每组数据输出一行，如果R在记录中找到，则输出所有与R在同一层次且位置在R之后的物质名称，名称之间无需添加空格，紧密连接即可；否则输出No。若R是其所在层次中最后一个物质，则输出"",即输出一个空字符。
样例输入
3
Material_1
{
Material_2
{
Material_3
Material_4
Material_5
{
Material_6
Material_7
}
Material_8
}
Material_9
Material_10
}

Material_2


Material_1
{
Material_2
{
Material_3
Material_4
Material_5
{
Material_6
Material_7
}
Material_8
}
Material_9
Material_10
}
Material_11
{
Material_3
Material_7
Material_2
{
Material_3
Material_4
Material_5
{
Material_6
Material_7
}
Material_8
}
Material_13
}

Material_2


Material_1
{
Material_2
{
Material_3
Material_4
Material_5
{
Material_6
Material_7
}
Material_8
}
Material_9
Material_10
}

Material_20


！
样例输出
Material_9Material_10
Material_9Material_10
No
提示
读入数据时，需采用如下方式进行读取。
例：若要读取一行输入内容，则
cin.getline(line, lineSize, '\n');
sscanf(line, "%s", tmp);

其中line和tmp为数组指针，类型为char* ，linesize为line所指向的数组的规模，为int型。
所需读取的内容最终是存储在tmp数组中。之后如需对读取的内容进行操作，就对tmp进行操作即可，读到空行时tmp长度即为0。

采用其他方法读取可能会出现WA以及RE，TLE。
 * */

#include <iostream>
#include <stack>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define rept(i,s,e) for(i=s;i<e;++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=h;i>l;--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<n;++i)
#define per(i,n)    for(i=n;i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */

#define LINE_SIZE   (20)
#define CHILD       1
#define SIBLING     2

typedef struct TreeNode{
  char name[LINE_SIZE];
  struct TreeNode* child;
  struct TreeNode* sibling;
}TreNd, *Tre;

Tre
tre_build()
{
  Tre t = (TreNd*)malloc(sizeof(TreNd));
  t->child = NULL;
  t->sibling = NULL;
  unsigned short flag = CHILD;
  stack<TreNd*> *s = new stack<TreNd*>();
  s->push(t);
  while ( !s->empty() )
  {
      char* line = (char*)malloc(sizeof(char)*LINE_SIZE);
      cin.getline(line, LINE_SIZE, '\n');
      switch(line[0])
      {
      case '\0':
        while ( !s->empty() ) s->pop();
        break;
      case '{':
        flag = CHILD;
        break;
      case '}':
        s->pop();
        break;
      default:
        TreNd *curr = (TreNd*)malloc(sizeof(TreNd));
        sscanf(line, "%s", curr->name);
        curr->child = NULL;
        curr->sibling = NULL;
        TreNd* top = s->top();
        if ( CHILD == flag ) // 入栈
        {
          top->child = curr;
          s->push(curr);
        }
        else // 替换栈顶
        {
          top->sibling = curr;
          s->pop();
          s->push(curr);
        }
        flag = SIBLING;
        break;
      }
      free(line);
      line = NULL;
  }
  delete s;
  s = NULL;

  return t;
}

TreNd*
tre_find_nd(Tre t, char* target_name)
{
  if (NULL == t) return NULL;
  stack<TreNd*> *s = new stack<TreNd*>();
  TreNd* p = t;
  s->push(p);
  while ( !s->empty() )
  {
      if (p)
      {
        string str = target_name;
        if ( 0 == str.compare(p->name) ) { delete s; return p; }
        if ( p->sibling != NULL ) s->push(p->sibling);
        p = p->child;
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

void
tre_print_sibling(TreNd* node)
{
  if ( NULL == node )
    {
      cout<<"No"<<endl;
      return;
    }
  while (node && node->sibling)
  {
      cout<<node->sibling->name;
      node = node->sibling;
  }
  cout<<endl;
  return;
}

void
tre_destroy(Tre t)
{
  if (NULL == t) return;
  stack<TreNd*> *s = new stack<TreNd*>();
  TreNd* p = t;
  s->push(p);
  while ( !s->empty())
  {
      p = s->top();
      s->pop();
      if ( p->sibling != NULL ) s->push(p->sibling);
      if ( p->child != NULL) s->push(p->child);

      free(p);
      p = NULL;
  }
  delete s;
  return;
}

/* main */
int
main()
{
  int t, i;
  scanf("%d\n", &t);
  rep(i,t)
  {
    Tre t = tre_build();
    char* line = (char*)malloc(sizeof(char)*LINE_SIZE);
    char tmp[LINE_SIZE];
    cin.getline(line, LINE_SIZE, '\n');
    sscanf(line, "%s", tmp);
    TreNd* node = tre_find_nd(t, tmp);
    tre_print_sibling(node);
    // read another two empty lines
    cin.getline(line, LINE_SIZE, '\n');
    cin.getline(line, LINE_SIZE, '\n');
    free(line);
    line = NULL;
    tre_destroy(t);
  }
  char* line = (char*)malloc(sizeof(char)*LINE_SIZE);
  cin.getline(line, LINE_SIZE, '\n');
  free(line);
  line = NULL;
  return 0;
}

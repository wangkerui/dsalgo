/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw6/1/
 *
1:实现堆结构

总时间限制: 3000ms 内存限制: 65535kB
描述
定义一个数组，初始化为空。在数组上执行两种操作：

1、增添1个元素，把1个新的元素放入数组。

2、输出并删除数组中最小的数。

使用堆结构实现上述功能的高效算法。

输入
第一行输入一个整数t，代表测试数据的组数。
对于每组测试数据，第一行输入一个整数n，代表操作的次数。
每次操作首先输入一个整数type。
当type=1，增添操作，接着输入一个整数u，代表要插入的元素。
当type=2，输出删除操作，输出并删除数组中最小的元素。
1<=n<=100000。
输出
每次删除操作输出被删除的数字。
样例输入
2
5
1 1
1 2
1 3
2
2
4
1 5
1 1
1 7
2
样例输出
1
2
1
提示
每组测试数据的复杂度为O(nlgn)的算法才能通过本次，否则会返回TLE(超时)
需要使用最小堆结构来实现本题的算法
 */
#include<stdio.h>
#include<stdlib.h>

#define rept(i,s,e) for(i=(int)(s);i<(int)(e);++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=(int)(h);i>(int)(l);--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<(int)(n);++i)
#define per(i,n)    for(i=(int)(n);i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */
#define max(a,b)    ((a)>(b)?(a):(b))
#define min(a,b)    ((a)<(b)?(a):(b))

/* the definition of heap */
typedef struct Heap
{
  int size;
  int* vals;
} Heap;

/* allocate heap memory */
Heap*
init(Heap* h, int max_len)
{
  h->size = 0;
  h->vals = (int*)malloc(sizeof(int)*max_len);
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
  if (j+1 < h->size && h->vals[j+1] < h->vals[j])
    ++j;     // if right child (if exists) is smaller, then turn to it.
  int tmp = h->vals[i];
  while (j < h->size && tmp > h->vals[j] )
  {
      h->vals[i] = h->vals[j];
      i = j;
      j = j*2+1;
      if (j+1 < h->size && h->vals[j+1] < h->vals[j])
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
  int tmp = h->vals[curr];
  while (curr > 0 && h->vals[parent] > tmp)
  {
      h->vals[curr] = h->vals[parent];
      curr = parent;
      parent = (curr+1)/2-1;
  }
  h->vals[curr] = tmp;
}

int
insert(Heap* h, int val)
{
  h->vals[h->size++] = val;
  shift_up(h, h->size-1);
  return val;
}

int
delete(Heap* h, int position)
{
  int tmp = h->vals[position];
  h->vals[position] = h->vals[--h->size];
  int parent = (position+1)/2-1;
  if (parent >= 0 && h->vals[parent] > h->vals[position])
    shift_up(h, position);
  else
    shift_down(h, position);
  return tmp;
}

int
remove_min(Heap* h)
{
  int tmp = h->vals[0];
  h->vals[0] = h->vals[--h->size];
  shift_down(h, 0);
  return tmp;
}

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
    rep(j,n)
    {
       int type, u;
       scanf("%d", &type);
       if (1 == type)
       {
           scanf("%d\n", &u);
           insert(h, u);
       }
       else
         printf("%d\n", remove_min(h));
    }
    destroy(h);
    free(h);
  }
  return 0;
}

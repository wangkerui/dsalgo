/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw9/1/
 *
1:距离排序
总时间限制: 1000ms 内存限制: 65536kB
描述
给出三维空间中的n个点（不超过10个）,求出n个点两两之间的距离,并按距离由大到小依次输出两个点的坐标及它们之间的距离。
输入
输入包括两行，第一行包含一个整数n表示点的个数，第二行包含每个点的坐标(坐标都是整数)。点的坐标的范围是0到100，输入数据中不存在坐标相同的点。
输出
对于大小为n的输入数据，输出n*(n-1)/2行格式如下的距离信息：
(x1,y1,z1)-(x2,y2,z2)=距离
其中距离保留到数点后面2位。
(用cout输出时保留到小数点后2位的方法:cout<<fixed<<setprecision(2)<<x)
样例输入
4
0 0 0 1 0 0 1 1 0 1 1 1
样例输出
(0,0,0)-(1,1,1)=1.73
(0,0,0)-(1,1,0)=1.41
(1,0,0)-(1,1,1)=1.41
(0,0,0)-(1,0,0)=1.00
(1,0,0)-(1,1,0)=1.00
(1,1,0)-(1,1,1)=1.00
提示
用cout输出时保留到小数点后2位的方法:cout<<fixed<<setprecision(2)<<x

注意：
冒泡排序满足下面的性质,选择排序和快速排序(qsort或sort)需要对下面的情况进行额外处理
使用冒泡排序时要注意边界情况的处理,保证比较的两个数都在数组范围内

1. 对于一行输出中的两个点(x1,y1,z1)和(x2,y2,z2)，点(x1,y1,z1)在输入数据中应出现在点(x2,y2,z2)的前面。

比如输入：
2
0 0 0 1 1 1
输出是：
(0,0,0)-(1,1,1)=1.73
但是如果输入：
2
1 1 1 0 0 0
输出应该是：
(1,1,1)-(0,0,0)=1.73

2. 如果有两对点p1,p2和p3,p4的距离相同，则先输出在输入数据中靠前的点对。

比如输入：
3
0 0 0 0 0 1 0 0 2
输出是：
(0,0,0)-(0,0,2)=2.00
(0,0,0)-(0,0,1)=1.00
(0,0,1)-(0,0,2)=1.00
如果输入变成：
3
0 0 2 0 0 1 0 0 0
则输出应该是：
(0,0,2)-(0,0,0)=2.00
(0,0,2)-(0,0,1)=1.00
(0,0,1)-(0,0,0)=1.00
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define rept(i,s,e) for(i=s;i<e;++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=h;i>l;--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<n;++i)
#define per(i,n)    for(i=n;i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */
#define min(a,b)    ((a)<(b)?(a):(b))

typedef struct point{
  int x;
  int y;
  int z;
}point;

void
p_print(point* p)
{
  printf("%d,%d,%d", p->x, p->y, p->z);
}

typedef struct distance{
  int i;
  int j;
  double d;
}distance;

double
d_dis(point* p1, point* p2)
{
  int dx = p2->x - p1->x;
  int dy = p2->y - p1->y;
  int dz = p2->z - p1->z;
  return sqrt( (double)(dx*dx + dy*dy + dz*dz) );
}

int
d_compare(distance* d1, distance* d2)
{
  if ( (d1->d - d2->d) < 0.01 && (d1->d - d2->d) > -0.01 )
  {
    if ( d1->i == d2->i ) return d2->j - d1->j;
    else return d2->i - d1->i;
  }
  else if (d1->d < d2->d) return -1;
  else return 1;
}

void
d_swap(distance* d1, distance* d2)
{
  swap(d1->i, d2->i);
  swap(d1->j, d2->j);
  double td = d1->d;
  d1->d = d2->d;
  d2->d = td;
}

void
d_sort(distance **d, int size)
{
  int i=0, j=0;
  rep(i,size)
    tper(j,size-1,i)
      if ( d_compare(d[j],d[j-1]) > 0 ) d_swap(d[j-1],d[j]);
}

void
d_print(point **p, distance* d)
{
  printf("(");
  p_print(p[d->i]);
  printf(")-(");
  p_print(p[d->j]);
  printf(")");
  printf("=%.2f", d->d);
}

/* main */
int
main()
{
  int n, m, i, j, count=0;
  scanf("%d\n", &n);
  m = n*(n-1)/2;
  point** p = (point**)malloc( sizeof(point*)*n );
  rep(i,n)
  {
    p[i] = (point*)malloc( sizeof(point) );
    scanf("%d %d %d", &(p[i]->x), &(p[i]->y), &(p[i]->z));
  }
  distance** d = (distance**)malloc( sizeof(distance*)*m );
  rep(i,n)
  {
    rept(j,i+1,n)
    {
      d[count] = (distance*)malloc( sizeof(distance) );
      d[count]->i = i;
      d[count]->j = j;
      d[count]->d = d_dis(p[i],p[j]);
      ++count;
    }
  }
  d_sort(d, m);
  rep(i,m)
    d_print(p, d[i]), printf("\n");
  // release memory
  rep(i,m)
    free(d[i]);
  free(d);
  d = NULL;
  rep(i,n)
    free(p[i]);
  free(p);
  p = NULL;
  return 0;
}

/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw9/2/
 *
2:寻找中位数

总时间限制: 1000ms 内存限制: 65536kB
描述
在N（1<=N<10,000且N为奇数）个数中，找到中位数。

输入
第1行：N

第2至N+1行：每行是一个整数
输出
第一行：中位数
样例输入
5
2
4
1
3
5
样例输出
3
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

void
bubble_sort(int* arr, int size)
{
  int i=0, j=0;
  rep(i,size)
    tper(j,size-1,i)
      if ( arr[j] < arr[j-1] ) swap(arr[j-1], arr[j]);
}

/* main */
int
main()
{
  int i, n;
  scanf("%d", &n);
  int* arr = (int*)malloc( sizeof(int)*n );
  rep(i,n)
  {
    scanf("%d", &(arr[i]));
  }
  bubble_sort(arr, n);
  printf("%d\n", arr[n/2]);
  // release memory
  free(arr);
  arr = NULL;
  return 0;
}

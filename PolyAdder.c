/**
 * The solution to http://dsalgo.openjudge.cn/dsmoochw2/1/
*/
/*
总时间限制: 1000ms 内存限制: 5000kB
描述
    我们经常遇到两多项式相加的情况，在这里，我们就需要用程序来模拟实现把两个多项式相加到一起。
    首先，我们会有两个多项式，每个多项式是独立的一行，每个多项式由系数、幂数这样的多个整数对来表示。

如多项式2x20- x17+ 5x9- 7x7+ 16x5+ 10x4 + 22x2- 15

对应的表达式为：2 20 -1 17 5 9 - 7 7 16 5 10 4 22 2 -15 0。  

为了标记每行多项式的结束，在表达式后面加上了一个幂数为负数的整数对。

同时输入表达式的幂数大小顺序是随机的。

我们需要做的就是把所给的两个多项式加起来。

输入
输入包括多行。
第一行整数n,表示有多少组的多项式需要求和。(1 < n < 100)
下面为2n行整数，每一行都是一个多项式的表达式。表示n组需要相加的多项式。
每行长度小于300。
输出
输出包括n行，每行为1组多项式相加的结果。
在每一行的输出结果中，多项式的每一项用“[x y]”形式的字符串表示，x是该项的系数、y 是该项的幂数。
要求按照每一项的幂从高到低排列，即先输出幂数高的项、再输出幂数低的项。
系数为零的项不要输出。
样例输入
2
-1 17 2 20 5 9 -7 7 10 4 22 2 -15 0 16 5 0 -1
2 19 7 7 3 17 4 4 15 10 -10 5 13 2 -7 0 8 -8
-1 17 2 23 22 2 6 8 -4 7 -18 0 1 5 21 4 0 -1
12 7 -7 5 3 17 23 4 15 10 -10 5 13 5 2 19 9 -7
样例输出
[ 2 20 ] [ 2 19 ] [ 2 17 ] [ 15 10 ] [ 5 9 ] [ 6 5 ] [ 14 4 ] [ 35 2 ] [ -22 0 ]
[ 2 23 ] [ 2 19 ] [ 2 17 ] [ 15 10 ] [ 6 8 ] [ 8 7 ] [ -3 5 ] [ 44 4 ] [ 22 2 ] [ -18 0 ]
提示
第一组样例数据的第二行末尾的8 -8，因为幂次-8为负数，所以这一行数据结束，8 -8不要参与计算。
*/
#include <stdio.h>

#define MAX 300
#define swap(a,b) {a=a^b;b=a^b;a=a^b;}

struct item{
	int co;
	int exp;
};

int findExp(item* p, int e)
{
	for (int i = 0; i < MAX; ++i)
	{
		item m = p[i];
		if (m.exp == -1 || m.exp == e) return i;
	}
	return -1;
}

void sort(item* p)
{
	for (int i=0; i<MAX; ++i)
	{
		for (int j=0; j<MAX-i-1; ++j)
		{
			if (p[j].exp>p[j+1].exp) 
			{
				swap(p[j].exp,p[j+1].exp);
				swap(p[j].co,p[j+1].co);
			}
		}
	}
}

int main()
{
	
	int n, co, exp;
	scanf("%d", &n);
	item** polys = new item*[n];
	
	// add when input
	for (int i = 0; i < n; ++i) {
		polys[i] = new item[MAX];
		// init
		for (int j = 0; j < MAX; ++j) {
			polys[i][j].co = 0;
			polys[i][j].exp = -1;
		}
		for ( scanf("%d %d", &co, &exp); exp >= 0; scanf("%d %d", &co, &exp) ) 
		{
			int index = findExp(polys[i], exp);
			polys[i][index].co += co;
			polys[i][index].exp = exp;
		}
		for ( scanf("%d %d", &co, &exp); exp >= 0; scanf("%d %d", &co, &exp) ) 
		{
			int index = findExp(polys[i], exp);
			polys[i][index].co += co;
			polys[i][index].exp = exp;
		}
	}

	// sort
	for (int i = 0; i < n; ++i)
	{
		sort(polys[i]);
	}
	
	// print
	for (int i = 0; i < n; ++i) {
		for (int j = MAX; j > 0; --j) {
			if ( (polys[i]+j-1)->co != 0)
				printf("[ %d %d ] ", (polys[i]+j-1)->co, (polys[i]+j-1)->exp);
		}
		printf("\n");
	}

	// release memory
	for (int i = 0; i < n; ++i) {
		delete[] polys[i];
	}
	delete[] polys;

	return 0;
}

/**
 * The solution to http://dsalgo.openjudge.cn/dsmoochw2/4/
*/
/**
总时间限制: 1000ms 内存限制: 65536kB
描述
把M个同样的苹果放在N个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？
（用K表示）5，1，1和1，5，1 是同一种分法。
输入
第一行是测试数据的数目t（0 <= t <= 20）。以下每行均包含二个整数M和N，以空格分开。
1<=M，N<=10。
输出
对输入的每组数据M和N，用一行输出相应的K。
样例输入
1
7 3
样例输出
8
*/
#include <iostream>

#define rept(i,n) for(int i=0; i<n; ++i)

int count(int, int, int);

using namespace std;

int main()
{
	int t;
	cin>>t;

	int M,N;
	rept(i,t)
	{
		cin>>M>>N;
		cout<<count(0,M,N)<<endl;
	}
	
	return 0;
}

int count(int min, int apples, int plates)
{
	if (1 == plates) return 1;

	int max = apples/plates;
	int c = 0;
	for (int i = min; i <= max; ++i)
	{
		c += count(i, apples-i, plates-1);
	}
	return c;
}

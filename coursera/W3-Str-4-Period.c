/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw4/4/
 * 
 * 
4:前缀中的周期

总时间限制: 3000ms 内存限制: 65536kB
描述
一个字符串的前缀是从第一个字符开始的连续若干个字符，例如"abaab"共有5个前缀，分别是a, ab, aba, abaa,  abaab。

我们希望知道一个N位字符串S的前缀是否具有循环节。换言之，对于每一个从头开始的长度为 i （i 大于1）的前缀，是否由重复出现的子串A组成，即 AAA...A （A重复出现K次,K 大于 1）。如果存在，请找出最短的循环节对应的K值（也就是这个前缀串的所有可能重复节中，最大的K值）。
输入
输入包括多组测试数据。每组测试数据包括两行。
第一行包括字符串S的长度N（2 <= N <= 1 000 000）。
第二行包括字符串S。
输入数据以只包括一个0的行作为结尾。
输出
对于每组测试数据，第一行输出 "Test case #“ 和测试数据的编号。
接下来的每一行，输出前缀长度i和重复测数K，中间用一个空格隔开。前缀长度需要升序排列。
在每组测试数据的最后输出一个空行。
样例输入
3
aaa
12
aabaabaabaab
0
样例输出
Test case #1
2 2
3 3

Test case #2
2 2
6 2
9 3
12 4
*/
#include <stdio.h>
#include <stdlib.h>

#define rept(i,s,e) for(i=s;i<e;++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=h;i>l;--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<n;++i)
#define per(i,n)    for(i=n;i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */

#define MAX_LEN    (1000000)

/* 计算KMP算法中的next数组
 * 要求调用者保证next非空并且 next.size > pattern.size
 * 返回pattern长度
 */
int
next(char* pattern, int* next)
{
	if (pattern == NULL) return -1;

	int j = 0;
	next[j] = -1;       // N[0] = -1
	int k = next[j];
	while (pattern[j] != '\0')
	{
		while ( k >=0 && pattern[j] != pattern[k] )
			k = next[k];
		++j; ++k;
		/* non-optimize version */
		next[j] = k;
		/* optimize version */
		/*
		if ( pattern[j] == pattern[k] )
			next[j] = next[k];
		else
			next[j] = k;
		*/
	}

	return j; // return the number of chars
}

/* main */
int
main()
{
	int case_no=1, len=0;
	char* str;

	for ( scanf("%d",&len); len != 0; scanf("%d",&len), ++case_no  )
	{
		str = (char*)malloc( sizeof(char)*(len+1) );
		scanf("%s",str);
		int* n = (int*)malloc( sizeof(int)*(len+1) );
		int count = next(str, n);
		// print
		printf("Test case #%d\n",case_no);
		int i = 0;
		rep(i,count+1)
		{	
			if ( n[i]>0 && i%(i-n[i])==0 )
				printf("%d %d\n", i, i/(i-n[i]));
		}
		printf("\n");

		free(n);
		free(str);
	}

	return 0;
}

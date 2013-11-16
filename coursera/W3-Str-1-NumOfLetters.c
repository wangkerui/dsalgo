/*
The solution to http://dsalgo.openjudge.cn/dsmoochw4/1/

1:统计字符数
查看 提交 统计 提问
总时间限制: 1000ms 内存限制: 65536kB
描述
判断一个由a-z这26个字符组成的字符串中哪个字符出现的次数最多
输入
第1行是测试数据的组数n，每组测试数据占1行，是一个由a-z这26个字符组成的字符串
每组测试数据之间有一个空行，每行数据不超过1000个字符且非空
输出
n行，每行输出对应一个输入。一行输出包括出现次数最多的字符和该字符出现的次数，中间是一个空格。
如果有多个字符出现的次数相同且最多，那么输出ascii码最小的那一个字符
样例输入
2
abbccc

adfadffasdf
样例输出
c 3
f 4
*/

#include <stdio.h>
#include <stdlib.h>

#define rept(i,s,e) for(i=s;i<e;++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=h;i>l;--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<n;++i)
#define per(i,n)    for(i=n;i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */

#define MAX_LEN 1000
#define ALPHA_SIZE 26

int
main()
{
	int n;     // n test cases
	char* str; // test string
	int max;   // the index of max-count
	int i,j;   // iterator

	scanf("%d",&n);
	rep(i,n)
	{	
		str = (char*)malloc(sizeof(char)*MAX_LEN);
		scanf("%s",str);
		
		int *tmp = (int*)malloc(sizeof(int)*ALPHA_SIZE);
		rep(j,ALPHA_SIZE)  // initialize
			tmp[j] = 0;
		for(j=0; str[j] != '\0'; ++j)
		{
			tmp[str[j]-'a'] += 1;
		}
		max = 0;
		rep(j,ALPHA_SIZE)
			if (tmp[j]>tmp[max]) max = j;
		printf("%c %d\n",(max+'a'),tmp[max]);

		//getline();

		free(tmp);
		free(str);
	}

	return 0;
}

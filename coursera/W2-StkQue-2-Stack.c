/**
 * The solution to http://dsalgo.openjudge.cn/dsmoochw3/2/
 *
总时间限制: 1000ms 内存限制: 1000kB
描述
栈是一种重要的数据结构，它具有push k和pop操作。push k是将数字k加入到栈中，pop则是从栈中取一个数出来。

栈是后进先出的：把栈也看成横向的一个通道，则push k是将k放到栈的最右边，而pop也是从栈的最右边取出一个数。

假设栈当前从左至右含有1和2两个数，则执行push 5和pop操作示例图如下：

          push 5          pop

栈   1 2  ------->  1 2 5 ------>  1 2

现在，假设栈是空的。给定一系列push k和pop操作之后，输出栈中存储的数字。若栈已经空了，仍然接收到pop操作，

则输出error。

输入
第一行为m，表示有m组测试输入，m<100。
每组第一行为n，表示下列有n行push k或pop操作。（n<150）
接下来n行，每行是push k或者pop，其中k是一个整数。
（输入保证同时在栈中的数不会超过100个）
输出
对每组测试数据输出一行。
该行内容在正常情况下，是栈中从左到右存储的数字，数字直接以一个空格分隔，如果栈空，则不作输出；
但若操作过程中出现栈已空仍然收到pop，则输出error。
样例输入
2
4
push 1
push 3
pop
push 5
1
pop
样例输出
1 5
error
*/
#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
	int* arr;
	int count;
	int error;
}stack_t;

int streq(char* str1, char* str2)
{
	char *p = str1, *q = str2;
	while (*p == *q && *p != '\0' && *q != '\0') {p++;q++;}
	if (*p == '\0' && *q == '\0') return 1;
	else return 0;
}

int main()
{
	int m,i;
	scanf("%d", &m);

	for (i=0; i<m; ++i)
	{
		stack_t* s;
		int n, j;

		s = (stack_t*)malloc( sizeof(stack_t) );
		s->arr = (int*)malloc( sizeof(int)*MAX_SIZE );
		s->count = 0;
		s->error = 0;
		scanf("%d", &n);
		for (j=0; j<n; ++j)
		{
			char* str = (char*)malloc( sizeof(char)*5 );
			int val;
			scanf("%s", str);
			if (streq(str, "push"))
			{
				scanf("%d", &val);
				s->arr[s->count++] = val;
			}
			if (streq(str, "pop"))
			{
				if (s->count <= 0) s->error = 1;
				else s->count--;
			}
			free(str);
		}
		// print
		if (s->error) 
			printf("%s\n", "error");
		else
		{
			int k;
			for(k=0;k<s->count;++k)
				printf("%d ", s->arr[k]);
			printf("\n");
		}

		free(s->arr);
		free(s);
	}
	
	return 0;
}

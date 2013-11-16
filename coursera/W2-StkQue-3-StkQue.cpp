/*
The solution to http://dsalgo.openjudge.cn/dsmoochw3/3/

3:stack or queue
查看 提交 统计 提问
总时间限制: 1000ms 内存限制: 65535kB
描述
栈和队列都是常用的线性结构，它们都提供两个操作：
Push：加入一个元素。
Pop：弹出一个元素。
不同的是，栈是”先进后出”，而队列则是”先进先出”。
给出一个线性结构的进出顺序，判定这个结构是栈还是队列。
输入
第一行输入一个整数t，代表有t组测试数据
对于每组测试数据，第一行输入一个整数n，代表操作的次数。
随后输入n行，每行包含两个整数 type val。
当type = 1时，表示该次操作为push操作，val表示进入的数字。当type=2时，表示该次操作为pop操作，val代表出来的数字。
3<=n<=2000
输出
每组测试数据输出一行。
输出改组数据对应的线性结构，”Stack” 或者 “Queue”。
题目保证是栈或者队列的一种。
样例输入
2
6
1 1
1 2
1 3
2 3
2 2
2 1
4
1 1
1 2
2 1
2 2
样例输出
Stack
Queue
*/

#include <iostream>
#include <string>
#include <stack>
#include <queue>

#define rept(i,s,e) for(int i=s;i<e;++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(int i=h;i>l;--i) /* i belongs to (l,h] */
#define rep(i,n)    for(int i=0;i<n;++i)
#define per(i,n)    for(int i=n;i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */

#define Stack "Stack"
#define Queue "Queue"

using namespace std;

int
main()
{
	int t;   // t test cases
	cin>>t;

	rep(i,t)
	{	
		int n;  // n inputs per case.
		cin>>n;

		stack<int> *s = new stack<int>();
		queue<int> *q = new queue<int>();
		string res = "";
		int type,val;
		rep(j,n)
		{
			cin>>type>>val;
			if (1==type)
			{
				s->push(val);
				q->push(val);
			} else if (2==type) {
				if (val==q->front()) res = Queue;
				if (val==s->top()) res = Stack;
				s->pop();q->pop();
			}
		}
		cout<<res<<endl;

		delete s;
		delete q;
	}

	return 0;
}

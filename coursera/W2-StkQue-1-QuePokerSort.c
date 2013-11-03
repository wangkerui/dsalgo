/**
 The solution to http://dsalgo.openjudge.cn/dsmoochw3/1/

总时间限制: 1000ms 内存限制: 65536kB
描述
假设这里有36张扑克牌，分别为A1~A9,B1~B9,C1~C9,D1~D9，其中A代表方片，B代表草花，C代表红桃，D代表黑桃，那么，设定如下的排序规则：
1.对于两张卡牌，X1Y1与X2Y2，X1与X2表示A～D，Y1与Y2表示1～9，如果X1与X2不同，那么依照D>C>B>A的方式进行排序
2.假如有X1与X2相同时，那么就比较Y1与Y2的大小。
例如，对于如下的四张牌，有如下的升序排序结果：
D3，C4，A4，C1
升序排序的结果为A4，C1，C4，D3
有人提出了如下的排序策略：
先建立9个队列，用于存放点数的大小，将卡牌依点数存放入各自的队列之中，然后再按队列1到队列9依次出队。
例如，对于上面的结果，依次进队后，结果如下：
队列1：C1；队列3：D3，队列4：C4，A4
将其依次出队后，结果为C1，D3，C4，A4
然后，再建立4个队列，用于存放花色。将卡牌依花色A～D存放入队列1～4中，然后再按队列1到队列4依次出队。
例如，对于上面刚刚出队的序列C1，D3，C4，A4，将其依次进队，结果如下：
队列1：A4；队列3：C1，C4；队列4：D3
将其依次出队后，结果为A4，C1，C4，D3，排序结束。
请根据上面的算法，编写一个用队列对扑克牌排序的程序，要求依照上面的排序规则，根据先花色后点数的方法进行排序。
输入
输入分为两行，第一行为一个整数n，表示一共有n张牌（1<=n<=100）
第二行用XY的形式表示每一张牌，其中X为A～D，Y为1～9
输出
输出三个部分
第一个部分为第一次进队出队的结果，用Queue1:...表示，共9行，结果用空格分隔，下同
第二部分为第二次进队出队的结果，用QueueA:...表示，共4行
第三部分为一行，即将卡牌排序后的结果（升序排序）
样例输入
8
D8 A6 C3 B8 C5 A1 B5 D3
样例输出
Queue1:A1
Queue2:
Queue3:C3 D3
Queue4:
Queue5:C5 B5
Queue6:A6
Queue7:
Queue8:D8 B8
Queue9:
QueueA:A1 A6
QueueB:B5 B8
QueueC:C3 C5
QueueD:D3 D8
A1 A6 B5 B8 C3 C5 D3 D8
提示
第二次入队出队时，可以复用第一次时9个队列中的4个。所以其实只需要开辟9个队列即可。
*/
#include <stdio.h>

#define MAX_SIZE 128
#define MASK MAX_SIZE-1
#define MOD 16
#define rept(i,n) for(i=0;i<n;++i)

typedef struct queue {
	int* arr;
	int off, count;
}queue_t, *queues;

int enqueue(queue_t* q, int val)
{
	int pos = (q->off+q->count) & MASK;
	q->arr[pos] = val;
	q->count++;
	return val;
}

int dequeue(queue_t* q)
{
	int oldval = q->arr[q->off];
	q->off = (q->off+1) & MASK;
	q->count--;
	return oldval;
}

int main()
{
	int n, *pokers, i, j;
	queues *q;

	/* Input the numbers of poker */
	scanf("%d", &n);
	
	/* Input the pokers */
	pokers = (int*)malloc( sizeof(int)*n );
	rept(i,n)
	{
		scanf("%X", &pokers[i] );
	}

	/* Initial 9 queues */
	q = (queues*)malloc( 9*sizeof(queues) );
	rept(i,9)
	{
		q[i] = (queue_t*)malloc(sizeof(queue_t));
		q[i]->arr = (int*)malloc(sizeof(int)*MAX_SIZE);
		q[i]->off = 0;
		q[i]->count = 0;
	}

	/* Enqueue as poker number */
	rept(i, n)
	{
		int index = pokers[i] & ( MOD - 1 );
		index -= 1;
		enqueue(q[index], pokers[i]);
	}
	/* Dequeue and print in order */
	j = 0;
	rept(i, 9) /* 1~9 */
	{
		printf("Queue%d:", i+1);
		while (q[i]->count > 0)
		{
			int val = dequeue(q[i]); /* dequeue */
			printf("%X ", val);       /* print */
			pokers[j++] = val;        /* cache in order */
		}
		printf("\n");
	}

	/* Enqueue as poker color */
	rept(i, n)
	{
		int index = pokers[i] / MOD - 10;
		enqueue(q[index], pokers[i]);
	}
	/* Dequeue and print in order */
	j = 0;
	rept(i, 4) /* A,B,C,D */
	{
		printf("Queue%X:", i+10);
		while (q[i]->count > 0)
		{
			int val = dequeue(q[i]); // dequeue
			printf("%X ", val);       // print
			pokers[j++] = val;        // cache in order
		}
		printf("\n");
	}

	/* Print in order */
	rept(i, n)
		printf("%X ", pokers[i]);
	printf("\n");
	
	
	/* Release memories */
	rept(i,9)
	{
		free(q[i]->arr);
		free(q[i]);
	}
	free(q);
	free(pokers);
	
	return 0;
}

/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw3/4/
 * 
 * 
中缀表达式的值

总时间限制: 200ms 内存限制: 1024kB
描述
人们熟悉的四则运算表达式称为中缀表达式，例如(23+34*45/(5+6+7))。在程序设计语言中，可以利用堆栈的方法把中缀表达式转换成保值的后缀表达式（又称逆波兰表示法），并最终变为计算机可以直接执行的指令，得到表达式的值。

给定一个中缀表达式，编写程序，利用堆栈的方法，计算表达式的值。
输入
第一行为测试数据的组数N
接下来的N行，每行是一个中缀表达式。表达式中只含数字、四则运算符和圆括号，操作数都是正整数，数和运算符、括号之间没有空格。中缀表达式的字符串长度不超过600。
输出
对每一组测试数据输出一行，为表达式的值
样例输入
3
3+5*8
(3+5)*8
(23+34*45/(5+6+7))
样例输出
43
64
108
提示
注意：运算过程均为整数运算（除法运算'/'即按照C++定义的int除以int的结果，测试数据不会出现除数为0的情况），输出结果也为整数（可能为负）。
中间计算结果可能为负。
*/
#include <iostream>
#include <string>
#include <stack>

#define rept(i,s,e) for(int i=s;i<e;++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(int i=h;i>l;--i) /* i belongs to (l,h] */
#define rep(i,n)    for(int i=0;i<n;++i)
#define per(i,n)    for(int i=n;i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */
#define isnum(c)    (c>='0' && c<='9')

#define MAX_SIZE 600
#define E 2

using namespace std;

/* 中缀表达式-->后缀表达式 */
string
convert(string in_order_exp)
{
	char op;                      /* 操作符 */
	string post_order_exp;        /* 后缀表达式 */
	stack<char> *convertor = new stack<char>();
	
	/* 优先级矩阵 
	 * *=42 +=43 -=45 /=47 ascii
	 * 0：优先级相等；1：优先级高；-1：低；E：占位符
	 * 两个$行和$列是为索引方便而填充
	 该矩阵表示的转换规则如下：
	1.当读到一个操作数时，立即将它放到输出中。操作符则不立即输出，放入栈中。遇到左圆括号也推入栈中。
	2.如果遇到一个右括号，那么就将栈元素弹出，将符号写出直到遇到一个对应的左括号。但是这个左括号只被弹出，并不输出。
	3.在读到操作符时，如果此时栈顶操作符优先性大于或等于此操作符，弹出栈顶操作符直到发现优先级更低的元素位置。除了处理）的时候，否则决不从栈中移走"（"。操作符中，+-优先级最低，（）优先级最高。
	4.如果读到输入的末尾，将栈元素弹出直到该栈变成空栈，将符号写到输出中。
	*/
	short priority[6][6] = {
		/*       *  +  $  -  $  /    */
		/* * */{ 0, 1, E, 1, E, 0},
		/* + */{-1, 0, E, 0, E,-1},
		/* $ */{ E, E, E, E, E, E},
		/* - */{-1, 0, E, 0, E,-1},
		/* $ */{ E, E, E, E, E, E},
		/* / */{ 0, 1, E, 1, E, 0}
	};
		
	// convert
	int j = 0;
	int len = in_order_exp.length();
	post_order_exp = "";
	rep(i,len)
	{
		switch(op = in_order_exp.at(i))
		{
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9': 
			/* 数值，直接存入表达式 */
			post_order_exp.operator +=(op);
			if ( i==len-1 || !isnum(in_order_exp.at(i+1)) ) // 数字之间以空格隔开
				post_order_exp.operator +=(' ');
			break;
		case '(': 
			/* 左括号，直接入栈 */
			convertor->push(op);
			break;
		case ')': 
			/* 右括号，出栈直至遇到左括号 */
			while ( (op=convertor->top()) != '(') 
			{
				convertor->pop();
				post_order_exp.operator +=(op);
			}
			convertor->pop(); /* pop '(' */
			break;
		case '+': case '-': case '*': case '/': 
			/* 加减乘除，弹出（左括号以上）且（比自己优先级高或相等）的运算符 */
			char top;
			while ( !convertor->empty() && (top=convertor->top())!='(' && priority[top-'*'][op-'*']>=0) 
			{
				convertor->pop();
				post_order_exp.operator +=(top); 
			}
			convertor->push(op);
			break;
		default:
			break;
		}
	}
	while(!convertor->empty()) /* 表达式末尾，弹出栈内剩余元素（符号） */
	{
		post_order_exp.operator +=(convertor->top());
		convertor->pop();
	}
	
	delete convertor;

	return post_order_exp;
}

/* 计算后缀表达式 */
int
eval(string exp)
{
	stack<int> *computor = new stack<int>();
	int val = 0;
	int len = exp.length();
	rep(i,len)
	{
		char c = exp.at(i);
		if (isnum(c))
		{
			val = val*10 + (c-'0');
			if (i==len-1 || !isnum(exp.at(i+1)))
			{
				computor->push(val);
				val = 0;
			}
		}
		else
		{	
			if (' '==c) continue;

			int op1,op2;
			op1 = computor->top();
			computor->pop();
			op2 = computor->top();
			computor->pop();
		
			switch(c)
			{
			case '+': computor->push(op2+op1);break;
			case '-': computor->push(op2-op1);break;
			case '*': computor->push(op2*op1);break;
			case '/': computor->push(op2/op1);break;
			}
		}
	}
	int result = computor->top();
	computor->pop();
	delete computor;
	return result;
}

int
main()
{
	int N;
	string str;
	string exp;

	cin>>N;
	rep(i,N)
	{	
		cin>>str; // 输入中缀表达式
		
		//（1）中缀转后缀
		exp = convert(str);
		
		//（2）计算
		int val = eval(exp);
		
		cout<<val<<endl;
	}

	return 0;
}

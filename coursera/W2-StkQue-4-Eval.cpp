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

using namespace std;

/* string --> int
 * 
 * Return 1 if success; 0 if fail.
 */
int str2int(string str, int* val)
{
	if (str.length() == 0 || !isnum(str.at(0)) )
		return 0;
	
	int tmp = 0;
	rep(i,str.length())
		tmp = tmp*10 + str.at(i)-'0';
	*val = tmp;
	return 1;
}

/* 中缀表达式-->后缀表达式 */
string* convert(string in_order_exp, string* post_order_exp)
{
	char op;    /* 操作符 */
	stack<char> *convertor = new stack<char>();
	
	/* 优先级矩阵 
	 * *=42 +=43 -=45 /=47 ascii
	 * 0代表优先级相等；1代表优先级高；-1代表低；2无意义，占位符
	 该矩阵表示的转换规则如下：
	1.当读到一个操作数时，立即将它放到输出中。操作符则不立即输出，放入栈中。遇到左圆括号也推入栈中。
	2.如果遇到一个右括号，那么就将栈元素弹出，将符号写出直到遇到一个对应的左括号。但是这个左括号只被弹出，并不输出。
	3.在读到操作符时，如果此时栈顶操作符优先性大于或等于此操作符，弹出栈顶操作符直到发现优先级更低的元素位置。除了处理）的时候，否则决不从栈中移走"（"。操作符中，+-优先级最低，（）优先级最高。
	4.如果读到输入的末尾，将栈元素弹出直到该栈变成空栈，将符号写到输出中。
	*/
	short priority[6][6] = {
		/*       *  +  $  -  $  /    */
		/* * */{ 0, 1, 2, 1, 2, 0},
		/* + */{-1, 0, 2, 0, 2,-1},
		/* $ */{ 2, 2, 2, 2, 2, 2},
		/* - */{-1, 0, 2, 0, 2,-1},
		/* $ */{ 2, 2, 2, 2, 2, 2},
		/* / */{ 0, 1, 2, 1, 2, 0}
	};
		
	// convert
	int j = 0;
	int len = in_order_exp.length();
	for(int i=0; i<len; ++i )
	{
		switch(op = in_order_exp.at(i))
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': /* 数值，直接存入表达式 */
			post_order_exp[j].operator +=(op);
			if ( i==len-1 || !isnum(in_order_exp.at(i+1)) ) {++j;}
			break;
		case '(': /* 左括号，直接入栈 */
			convertor->push(op);
			break;
		case ')': /* 右括号，出栈直至遇到左括号 */
			while ( (op=convertor->top()) != '(') 
			{
				convertor->pop();
				post_order_exp[j++].operator =(op);
			}
			convertor->pop(); /* pop '(' */
			break;
		case '+':
		case '-':
		case '*':
		case '/': /* 加减乘除，弹出（左括号以上）且（比自己优先级高或相等）的运算符 */
			char top;
			while ( !convertor->empty() && (top=convertor->top())!='(' && priority[top-'*'][op-'*']>=0) 
			{
				convertor->pop();
				post_order_exp[j++].operator =(top); 
			}
			convertor->push(op);
		default:
			break;
		}
	}
	while(!convertor->empty()) /* 表达式末尾，弹出栈内剩余元素 */
	{
		post_order_exp[j++].operator =(convertor->top());
		convertor->pop();
	}
	
	delete convertor;

	return post_order_exp;
}

/* 计算后缀表达式 */
int eval(string* exp)
{
	stack<int> *computor = new stack<int>();
	for (int i = 0; exp[i].length()>0; ++i)
	{
		int val1, val2;
		string str = exp[i];
		if (str2int(str,&val1))
			computor->push(val1);
		else
		{	
			val1 = computor->top();
			computor->pop();
			val2 = computor->top();
			computor->pop();
		}

		switch(str[0])
		{
		case '+': computor->push(val2+val1);break;
		case '-': computor->push(val2-val1);break;
		case '*': computor->push(val2*val1);break;
		case '/': computor->push(val2/val1);break;
		}
	}
	int val = computor->top();
	computor->pop();
	delete computor;
	return val;
}

int main()
{
	int N;
	string str;
	string *exp;

	cin>>N;
	rep(i,N)
	{	
		cin>>str;
		//（1）中缀转后缀
		exp = new string[MAX_SIZE];
		convert(str, exp);
		//（2）计算
		int val = eval(exp);
		delete[] exp;

		cout<<val<<endl;
	}

}

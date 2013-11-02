/**==============================================================
 * == The solution to http://dsalgo.openjudge.cn/dsmoochw2/2/  == 
 * ==============================================================
*/
/**
 * 总时间限制: 1000ms 内存限制: 65536kB
 * 描述
 * 有两个字符串str和substr，str的字符个数不超过10，substr的字符个数为3。
 * （字符个数不包括字符串结尾处的'\0'。）
 * 将substr插入到str中ASCII码最大的那个字符后面，若有多个最大则只考虑第一个。
 * 输入
 * 输入包括若干行，每一行为一组测试数据，格式为
 * str substr
 * 输出
 * 对于每一组测试数据，输出插入之后的字符串。
 * 样例输入
 * abcab eee
 * 12343 555
 * 样例输出
 * abceeeab
 * 12345553
*/
#include <iostream>

using namespace std;

int main()
{
	char str[14] = {'\0'};
	char substr[4] = {'\0'};
	
	while (cin>>str>>substr) {
		char *head = str, *curr = str, *max = str;
		
		while (*curr != '\0')
		{
			if (*curr > *max) max = curr;
			curr++;
		}
		while (curr > max)
		{
			*(curr+3) = *curr;
			curr--;
		}

		*(curr+1) = substr[0];
		*(curr+2) = substr[1];
		*(curr+3) = substr[2];
		
		cout<<str<<endl;

	}

	return 0;
}

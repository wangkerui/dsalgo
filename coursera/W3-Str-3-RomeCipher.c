/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw4/3/
 * 
 * 
3:古代密码

总时间限制: 1000ms 内存限制: 65536kB

描述
古罗马帝王有一个包括各种部门的强大政府组织。其中有一个部门就是保密服务部门。
为了保险起见，在省与省之间传递的重要文件中的大写字母是加密的。
当时最流行的加密方法是替换和重新排列。 
替换方法是将所有出现的字符替换成其它的字符。有些字符会碰巧替换成它自己。
例如：替换规则可以是将'A' 到 'Y'替换成它的下一个字符，将'Z'替换成 'A'，
如果原词是 "VICTORIOUS" 则它变成 "WJDUPSJPVT"。 
排列方法改变原来单词中字母的顺序。
例如：将顺序 <2, 1, 5, 4, 3, 7, 6, 10, 9, 8> 应用到 "VICTORIOUS" 上，
则得到"IVOTCIRSUO"。 
人们很快意识到单独应用替换方法或排列方法，加密是很不保险的。
但是如果结合这两种方法，在当时就可以得到非常可靠的加密方法。
所以，很多重要信息先使用替换方法加密，再将加密的结果用排列的方法加密。
用两中方法结合就可以将"VICTORIOUS" 加密成"JWPUDJSTVP"。 
考古学家最近在一个石台上发现了一些信息。初看起来它们毫无意义，
所以有人设想它们可能是用替换和排列的方法被加密了。
人们试着解读了石台上的密码，现在他们想检查解读的是否正确。
他们需要一个计算机程序来验证她，你的任务就是写这个验证程序。

输入
输入有两行。第一行是石台上的文字。文字中没有空格，并且只有大写英文字母。
第二行是被解读出来的加密前的文字。第二行也是由大写英文字母构成的。
两行字符数目的长度都不超过计划100。

输出
如果第二行经过某种加密方法后可以产生第一行的信息，输出 "YES"，否则输出"NO"。

样例输入
JWPUDJSTVP
VICTORIOUS

样例输出
YES
*/
#include <stdio.h>
#include <stdlib.h>

#define rept(i,s,e) for(i=s;i<e;++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=h;i>l;--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<n;++i)
#define per(i,n)    for(i=n;i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */

#define MOD             26
#define MAX_TEXT_LEN    (100+1)

/* We say two strings are "pesudoequals"
 * if one can be formed by REPLACEING & REORDERING the other one.
 */
int 
pesudoequals(char* str1, char* str2)
{
	if (str1==NULL&&str2!=NULL || str1!=NULL&&str2==NULL) return 0;
	if (str1==NULL && str2==NULL) return 1;

	char *p = str1, *q = str2;
	short *arr1 = (short*)malloc(sizeof(short)*26); /* count the number of str1 letters */
	short *arr2 = (short*)malloc(sizeof(short)*26); /* count the number of str2 letters */
	int i;
	rep(i,26) /* initialize */
	{
		arr1[i] = 0; arr2[i] = 0;
	}
	while(*p != '\0' && *q != '\0')
	{
		arr1[*p-'A'] += 1; ++p;
		arr2[*q-'A'] += 1; ++q;
	}
	while(*p != '\0') {arr1[*p-'A'] += 1; ++p;}
	while(*q != '\0') {arr2[*q-'A'] += 1; ++q;}

	short *arr = (short*)malloc(sizeof(short)*MAX_TEXT_LEN);
	rep(i,MAX_TEXT_LEN)  /* initialize */
		arr[i] = 0;
	rep(i,26)
	{
		arr[arr1[i]] += 1; arr[arr2[i]] -= 1;
	}

	int same = 1;
	rep(i,MAX_TEXT_LEN)
	{
		if (arr[i] != 0) 
		{
			same = 0;
			break;
		}
	}

	free(arr2); free(arr1); free(arr);
	return same;
}

/* main */
int
main()
{
	int key;        /* iterator for keys */
	int flag = 0;   /* means NO */
	char* line1 = (char*)malloc( sizeof(char)*MAX_TEXT_LEN );
	char* line2 = (char*)malloc( sizeof(char)*MAX_TEXT_LEN );
	char* tmp = (char*)malloc( sizeof(char)*MAX_TEXT_LEN );

	gets(line1);
	gets(line2);

	rept(key,0,26)
	{
		if ( pesudoequals(line1, line2) ) 
		{
			flag = 1;
			break;
		}
	}

	free(tmp); free(line2); free(line1);
	if (flag) printf("YES\n");
	else printf("NO\n");
	return 0;
}

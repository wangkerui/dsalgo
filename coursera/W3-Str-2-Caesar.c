/*
 * The solution to http://dsalgo.openjudge.cn/dsmoochw4/2/
 * 
 * 
2:Caesar 密码

总时间限制: 1000ms 内存限制: 65536kB

描述
Julius Caesar 生活在充满危险和阴谋的年代。为了生存，他首次发明了密码，用于军队的消息传递。假设你是Caesar 军团中的一名军官，需要把Caesar 发送的消息破译出来、并提供给你的将军。消息加密的办法是：对消息原文中的每个字母，分别用该字母之后的第5个字母替换（例如：消息原文中的每个字母A都分别替换成字母F），其他字符不 变，并且消息原文的所有字母都是大写的。 

密码字母：A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
原文字母：V W X Y Z A B C D E F G H I J K L M N O P Q R S T U
输入
最多不超过100个数据集组成。每个数据集由3部分组成：
起始行：START 
密码消息：由1到200个字符组成一行，表示Caesar发出的一条消息
结束行：END 
在最后一个数据集之后，是另一行：ENDOFINPUT
输出
每个数据集对应一行，是Caesar 的原始消息。
样例输入
START
NS BFW, JAJSYX TK NRUTWYFSHJ FWJ YMJ WJXZQY TK YWNANFQ HFZXJX
END
START
N BTZQI WFYMJW GJ KNWXY NS F QNYYQJ NGJWNFS ANQQFLJ YMFS XJHTSI NS WTRJ
END
START
IFSLJW PSTBX KZQQ BJQQ YMFY HFJXFW NX RTWJ IFSLJWTZX YMFS MJ
END
ENDOFINPUT
样例输出
IN WAR, EVENTS OF IMPORTANCE ARE THE RESULT OF TRIVIAL CAUSES
I WOULD RATHER BE FIRST IN A LITTLE IBERIAN VILLAGE THAN SECOND IN ROME
DANGER KNOWS FULL WELL THAT CAESAR IS MORE DANGEROUS THAN HE
*/
#include <stdio.h>
#include <stdlib.h>

#define rept(i,s,e) for(i=s;i<e;++i) /* i belongs to [s,e) */
#define tper(i,h,l) for(i=h;i>l;--i) /* i belongs to (l,h] */
#define rep(i,n)    for(i=0;i<n;++i)
#define per(i,n)    for(i=n;i>0;--i)
#define swap(a,b)   {a=a^b;b=a^b;a=a^b;}  /* swap a and b */
#define dec(c)      (((c)-'A'-5+MOD)%MOD + 'A')

#define MOD 26
#define START      "START"
#define END        "END"
#define ENDOFINPUT "ENDOFINPUT"
#define MAX_MARK_LEN    (10+1)
#define MAX_TEXT_LEN    (200+1)

/* DECODE */
char*
decode(char* cipher, char* plain)
{
	if (cipher==NULL) return NULL;
	
	char *p=cipher, *q=plain;
	while( (*q=*p) != '\0' )
	{
		if(*q>='A' && *q<='Z') *q = dec(*q);
		++q; ++p;
	}
	
	return plain;
}

/* string.equals */
int 
equals(char* str1, char* str2)
{
	if (str1==NULL&&str2!=NULL || str1!=NULL&&str2==NULL) return 0;
	if (str1==NULL && str2==NULL) return 1;

	char *p = str1, *q = str2;
	while(*p != '\0' && *q != '\0' && *p++==*q++);

	if (*p=='\0' && *q=='\0') return 1;
	else return 0;
}

/* main */
int
main()
{
	char* mark = (char*)malloc( sizeof(char)*MAX_MARK_LEN );
	for(;;)
	{
		gets(mark); /* read START */
		if(equals(mark,ENDOFINPUT)) break;

		char* text = (char*)malloc( sizeof(char)*MAX_TEXT_LEN );
		gets(text);
		text = decode(text,text);
		printf("%s\n",text);
		free(text);

		gets(mark); /* read END */
	}

	free(mark);
	return 0;
}

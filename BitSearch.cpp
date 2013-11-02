#include <iostream>

#define MOD 0x8000
#define mask(i) (1<<i)
#define rept(i,n) for(int i=0; i<n; ++i)

int count_i(int*, int, int);
void add_d(int *, int, int);

using namespace std;

int main()
{
	int N, M;
	cin>>N>>M;
	
	int* nums = new int[N];
	rept(i,N)
	{
		cin>>nums[i];
	}

	char op; int val;
	rept(i,M)
	{
		cin>>op>>val;
		if ('Q' == op)
			cout<<count_i(nums, N, val)<<endl;
		if ('C' == op)
			add_d(nums, N, val);
	}

	return 0;
}

int count_i(int* nums, int len, int i)
{
	int count = 0;
	rept(k,len)
	{
		int res = *(nums+k) & mask(i);
		if ( res != 0 ) count++;
	}
	return count;
}

void add_d(int* nums,int len, int d)
{
	rept(k,len)
	{
		*(nums+k) = (*(nums+k) + d) & (MOD-1); 
	}
}

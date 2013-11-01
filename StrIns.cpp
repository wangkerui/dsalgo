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

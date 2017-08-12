#include <bits/stdc++.h>
using namespace std;

int m,n;
bool ok[26][26]={};
char a[55],b[55];

int main() {	
	scanf("%d%d",&m,&n);
	while(m--) {
		scanf("%s%s",a,b);
		ok[a[0]-'a'][b[0]-'a'] = 1;
	}
	for(int i = 0; i < 26; ++i)
		ok[i][i] = 1;
	for(int k = 0; k < 26; ++k)
		for(int i = 0; i < 26; ++i)
			for(int j = 0; j < 26; ++j)
				ok[i][j] |= ok[i][k] && ok[k][j];
	while(n--) {
		scanf("%s%s",a,b);
		int len = strlen(a);
		bool good = len == strlen(b);
		for(int i = 0; good && i < len; ++i)
			good &= ok[a[i]-'a'][b[i]-'a'];
		printf(good?"yes\n":"no\n");
	}
}
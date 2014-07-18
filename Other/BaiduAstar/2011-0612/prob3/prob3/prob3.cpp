#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

#define LOCAL

int n, m;

long long gcd(long long a, long long b){
	long long c;
	if(a<b)swap(a,b);
	while(b){
		c = b;
		b = a%b;
		a = c;
	}
	return a;
}


int main(){
#ifdef LOCAL
	freopen("i.txt", "r", stdin);
	freopen("o.txt", "w", stdout);
#endif

	long long mx1 = 0, mx2 = 0, mmx = 0;
	int m1 = 0, m2 = 0, mm = 1, a;

	cin >> n >> m;
	if(m == 1){
		while(n--){
			cin >> a;
			if(a > mmx) mmx = a;
		}
	} else
	while(n--){
		cin >> a;

		long long tmx1 = mx1 + a;
		int tm1 = m1 + 1;
		if((double)tmx1/tm1 < (double)a){
			tmx1 = a;
			tm1 = 1;
		}

		long long tmx2 = mx2 + a;
		int tm2 = m2 + 1;
		if(m1+1 >= m && (double)tmx2/tm2 < (double)(mx1+a)/(m1+1)){
			tmx2 = mx1 + a;
			tm2 = m1 + 1;
		}

		mx1 = tmx1;
		m1 = tm1;
		mx2 = tmx2;
		m2 = tm2;

		if((double)mx2/m2 > (double)mmx/mm){
			mmx = mx2;
			mm = m2;
		}
	}

	long long g = gcd(mmx, mm);
	mmx /= g;
	mm /= g;

	if(mm == 1) cout << mmx << '\n';
	else cout << mmx << '/' << mm << '\n';
}

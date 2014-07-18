#include <cstdio>
#include <cstdlib>
#include <cmath>

int main(int argc, char *argv[]){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);

	int n;
	long long a, b, x;
	scanf ("%d", &n);
	for (int i = 0; i < n; ++ i){
		scanf ("%lld%lld%lld", &x, &a, &b);
		int m = 1;
		long long n;
		n = x;
		while (n = n / 10)
			m ++;
		if (a <= x && b >= x){
			printf ("%lld\n", (b - x) / (long long)(pow(10.0, m)+0.5) + 1);
		}
		else if (b < x){
			printf ("0\n");
		}
		else{
			long long n = a / (long long)pow(10.0, m) * (long long)(pow(10.0, m)+0.5) + x;
			if (a < n){
				a = n;
			}
			else{
				a = n + (long long)(pow(10.0, m)+0.5);
			}
			if (a > b){
				printf ("0\n");
			}
			else{
				printf("%lld\n", (b - a) / (long long)(pow(10.0, m)+0.5) + 1);
			}
		}
	}

	return 0;
}
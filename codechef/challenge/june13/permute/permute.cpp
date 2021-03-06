#include <cstdio>

#define MAX_N 1000000
#define MOD_PRIME 1000000007

using namespace std;

long long fact[MAX_N + 1];

int skip_whitespace()
{
	int ch;
	while (true) {
		ch = getchar_unlocked();
		if (ch != ' ' && ch != '\n')
			break;
	}
	return ch;
}

template<typename T>
T read_unsigned_integer()
{
	T result = (T) 0;
	int ch = skip_whitespace();
	while (ch >= '0' && ch <= '9') {
		result = 10 * result + (ch - '0');
		ch = getchar_unlocked();
	}
	return result;
}

long long mulmod(long long x, long long y)
{
	long long prod = x;
	prod = (prod * y) % MOD_PRIME;
	return prod;
}

long long powmod(long long x, int e)
{
	long long result = 1;
	long long base = x;

	if (e > 0) {
		while (true) {
			if (e & 1) {
				result = (result * base) % MOD_PRIME;
			}
			e >>= 1;
			if (e <= 0)
				break;
			base = (base * base) % MOD_PRIME;
		}
	}

	return result;
}

void build_fact()
{
	fact[0] = 1LL;
	for (int i = 0; i < MAX_N; i++)
		fact[i + 1] = mulmod(i + 1, fact[i]);
}

int solve_problem()
{
	int n, m;

	n = read_unsigned_integer<int>();
	m = read_unsigned_integer<int>();

	int k = m - n;
	long long result = fact[k + 1];

	int e = n - (k + 1);
	long long q = mulmod(k, k + 1);
	result = mulmod(result, powmod(q, e / 2));
	if (e & 1)
		result = mulmod(result, k);
	printf("%lld\n", result);

	return 0;
}

int main()
{
	int num_tests;

	num_tests = read_unsigned_integer<int>();

	build_fact();
	for (int i = 0; i < num_tests; i++)
		solve_problem();

	return 0;
}

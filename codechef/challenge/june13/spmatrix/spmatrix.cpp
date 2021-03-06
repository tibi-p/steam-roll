#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define MAX_N 10000000
#define MOD_PRIME 1000000007

using namespace std;

int midfact[MAX_N + 1];
int hyperfact[MAX_N + 1];

int addmod(int x, int y)
{
	int sum = x + y;
	if (sum >= MOD_PRIME)
		sum -= MOD_PRIME;
	return sum;
}

int submod(int x, int y)
{
	int diff = x - y;
	if (diff < 0)
		diff += MOD_PRIME;
	return diff;
}

int mulmod(int x, int y)
{
	long long prod = x;
	prod = (prod * y) % MOD_PRIME;
	return (int) prod;
}

int mulmod(int x, int y, int z)
{
	long long prod = x;
	prod = (prod * y) % MOD_PRIME;
	prod = (prod * z) % MOD_PRIME;
	return (int) prod;
}

int mulmod(int x, int y, int z, int t)
{
	long long left_prod = x;
	left_prod = (left_prod * y) % MOD_PRIME;
	long long right_prod = z;
	right_prod = (right_prod * t) % MOD_PRIME;
	return (int) ((left_prod * right_prod) % MOD_PRIME);
}

int powmod(int x, int e)
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

	return (int) result;
}

int invmod(int x)
{
	int result[2][2] = { {1, 0}, {0, 1} };
	int base[2][2] = { {0, 1}, {1, 0}};

	int y = x % MOD_PRIME;
	x = MOD_PRIME;
	while (y > 0) {
		int q = x / y;
		int r = x % y;
		base[1][1] = -q;
		int tmp[2][2] = { {0, 0}, {0, 0} };
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					tmp[i][j] += result[i][k] * base[k][j];
		memcpy(result, tmp, sizeof(result));
		x = y;
		y = r;
	}

	int inv = result[1][0];
	if (inv < 0)
		inv += MOD_PRIME;
	return inv;
}

void build_tables(int n)
{
	if (n <= 3)
		n = 3;

	midfact[2] = 2;
	fill(hyperfact, hyperfact + 3, 0);
	int alpha = 3;
	for (int i = 3; i <= MAX_N; i++) {
		midfact[i] = mulmod(midfact[i - 1], alpha);
		alpha = addmod(alpha, i);
		hyperfact[i] = addmod(mulmod(alpha, hyperfact[i - 1]), midfact[i]);
		alpha = addmod(alpha, i - 1);
	}
}

int compute_comtet(int n)
{
	static int inv2 = invmod(2);
	static int inv3 = invmod(3);

	if (n < 3)
		return 0;

	int g = powmod(inv2, n);
	int f = addmod(g, g);
	int x = mulmod(midfact[n], n - 1, n - 2, g);
	int y = mulmod(hyperfact[n], inv3, f);
	return submod(x, y);
}

int solve_problem()
{
	int n;

	if (scanf("%d", &n) != 1)
		return 1;

	printf("%d\n", compute_comtet(n));

	return 0;
}

int main()
{
	int num_tests;

	build_tables(MAX_N);

	if (scanf("%d", &num_tests) != 1)
		return 1;

	for (int i = 0; i < num_tests; i++)
		solve_problem();

	return 0;
}

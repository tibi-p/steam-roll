#include <algorithm>
#include <cstdio>

#define MAX_N 50
#define MAX_VALUE 16
#define pow2i(x) (1 << (x))

using namespace std;

int a[MAX_N];
int b[MAX_N];
int p[MAX_N];
pair<double, int> dp[1 << MAX_VALUE];

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

template<typename T>
T read_signed_integer()
{
	T result = (T) 0;
	bool flip = false;
	int ch = skip_whitespace();
	if (ch == '-') {
		flip = true;
		ch = skip_whitespace();
	}
	while (ch >= '0' && ch <= '9') {
		result = 10 * result + (ch - '0');
		ch = getchar_unlocked();
	}
	return flip ? -result : result;
}

int solve_problem()
{
	int n;

	n = read_unsigned_integer<int>();
	for (int i = 0; i < n; i++) {
		p[i] = read_unsigned_integer<int>();
		a[i] = read_unsigned_integer<int>() - 1;
		b[i] = read_unsigned_integer<int>() - 1;
	}

	double result = 0.0;
	if (n <= 16) {
		dp[0].first = (double) p[0] / 100;
		dp[0].second = pow2i(a[0]);
		dp[1].first = (double) (100 - p[0]) / 100;
		dp[1].second = pow2i(b[0]);
		for (int i = 1; i < n; i++) {
			double pos_prob = (double) p[i] / 100;
			double neg_prob = (double) (100 - p[i]) / 100;
			int max_mask = pow2i(i);
			int pos_mask = pow2i(a[i]);
			int neg_mask = pow2i(b[i]);
			for (int j = 0; j < max_mask; j++)
				if (dp[j].second != 0) {
					if ((dp[j].second & neg_mask) == 0) {
						dp[max_mask + j].first = dp[j].first * neg_prob;
						dp[max_mask + j].second = dp[j].second | neg_mask;
					} else {
						dp[max_mask + j].second = 0;
					}
					if ((dp[j].second & pos_mask) == 0) {
						dp[j].first = dp[j].first * pos_prob;
						dp[j].second = dp[j].second | pos_mask;
					} else {
						dp[j].second = 0;
					}
				} else {
					dp[max_mask + j].second = 0;
				}
		}
		int limit = pow2i(n);
		for (int i = 0; i < limit; i++)
			if (dp[i].second != 0)
				result += dp[i].first;
	}

	printf("%lf\n", result);

	return 0;
}

int main()
{
	int num_tests;

	num_tests = read_unsigned_integer<int>();
	for (int i = 0; i < num_tests; i++)
		solve_problem();

	return 0;
}

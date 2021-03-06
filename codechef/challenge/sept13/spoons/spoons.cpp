#include <algorithm>
#include <cstdio>

#define MAX_VALUE 65

using namespace std;

long long table[MAX_VALUE];

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

void build_table()
{
	table[2] = 2;
	for (int i = 3; i < MAX_VALUE; i++)
		if (i & 1)
			table[i] = 2 * table[i - 1] / (i + 1) * i;
		else
			table[i] = 2 * table[i - 1];
}

int solve_problem()
{
	long long n;

	n = read_unsigned_integer<long long>();
	long long *p = lower_bound(table + 1, table + MAX_VALUE - 1, n);
	printf("%ld\n", p - table);

	return 0;
}

int main()
{
	int num_tests;

	build_table();

	num_tests = read_unsigned_integer<int>();
	for (int i = 0; i < num_tests; i++)
		solve_problem();

	return 0;
}

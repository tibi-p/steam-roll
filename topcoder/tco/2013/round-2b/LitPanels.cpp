#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>

#define MAX_N 40
#define MOD_PRIME 1000000007

using namespace std;

class LitPanels {
public:
	int pow2[MAX_N * MAX_N + 1];

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
		return (prod * y) % MOD_PRIME;
	}

	int sqrmod(int x)
	{
		return mulmod(x, x);
	}

	int count1(int x, int y, int u, int v)
	{
		assert(x <= u && y <= v);
		int result = 0;

		if (x > 1 && y > 1) {
			int a = submod(pow2[x - 2], 1);
			int b = submod(pow2[y - 2], 1);
			int c = mulmod(a, b);
			int prod = sqrmod(c);
			prod = mulmod(prod, pow2[(x - 2) * (y - 2)]);
			result = addmod(result, prod);

			prod = c;
			prod = mulmod(prod, pow2[(x - 2) * (y - 2) + (x - 2) + (y - 2)]);
			prod = mulmod(prod, 4);
			result = addmod(result, prod);
			
			prod = a;
			prod = mulmod(prod, pow2[(x - 2) * (y - 2) + (x - 2) + 2 * (y - 2)]);
			prod = mulmod(prod, 2);
			result = addmod(result, prod);
			
			prod = b;
			prod = mulmod(prod, pow2[(x - 2) * (y - 2) + 2 * (x - 2) + (y - 2)]);
			prod = mulmod(prod, 2);
			result = addmod(result, prod);
			
			prod = pow2[x * y - 4];
			prod = mulmod(prod, 7);
			result = addmod(result, prod);
		} else {
			if (x == 1) {
				if (y == 1) {
					result = addmod(result, 1);
				} else {
					result = addmod(result, pow2[y - 2]);
				}
			} else {
				result = addmod(result, pow2[x - 2]);
			}
		}

		return result;
	}

	int count2(int x, int y, int u, int v)
	{
		assert((x <= u && y > v) || (x > u && y <= v));
		if (y > v)
			return count1(x, min(2 * v, y), x, y);
		else
			return count1(min(2 * u, x), y, x, y);
	}

	int count3(int x, int y, int u, int v)
	{
		assert(x > u && y > v && x < 2 * u && y < 2 * v);
		int result = 0;

		int a = submod(pow2[2 * u - x], 1);
		int b = submod(pow2[2 * v - y], 1);
		int c = mulmod(a, b);
		int prod = sqrmod(c);
		prod = mulmod(prod, pow2[(2 * u - x) * (2 * v - y) + (2 * u - x) * 2 * (y - v - 1) + (2 * v - y) * 2 * (x - u - 1)]);
		result = addmod(result, prod);

		int p = submod(pow2[u - 1], 1);
		int q = submod(pow2[v - 1], 1);
		int r = mulmod(p, q);
		int left = pow2[(2 * u - x) * (2 * v - y) + (2 * u - x) * (y - v - 1) + (2 * v - y) * (x - u - 1)];
		left = mulmod(left, c);
		int right = addmod(pow2[(u - 1) + (v - 1)], r);
		right = mulmod(right, pow2[(u - 1) * (v - 1)]);
		prod = submod(right, left);
		prod = mulmod(prod, c);
		prod = mulmod(prod, pow2[(2 * u - x) * (y - v - 1) + (2 * v - y) * (x - u - 1)]);
		prod = mulmod(prod, 4);
		result = addmod(result, prod);

		int up = pow2[(2 * u - x) * (y - v - 1) + (2 * v - y) * (x - u - 1)];
		up = mulmod(up, c);
		int down = addmod(pow2[(u - 1) + (v - 1)], r);
		down = mulmod(down, pow2[(u - 1) * (v - 1) - (2 * u - x) * (2 * v - y)]);
		prod = submod(right, left);
		prod = mulmod(prod, submod(down, up));
		prod = mulmod(prod, 2);
		result = addmod(result, prod);

		return result;
	}

	int count4(int x, int y, int u, int v)
	{
		assert(x > u && y > v && (x >= 2 * u || y >= 2 * v));
		int result = 0;

		result = addmod(result, pow2[2 * (u * v - 1)]);

		int a = submod(pow2[u - 1], 1);
		int b = submod(pow2[v - 1], 1);
		int c = mulmod(a, b);
		int prod = sqrmod(c);
		prod = mulmod(prod, pow2[2 * (u - 1) * (v - 1)]);
		result = addmod(result, prod);

		prod = pow2[u * v - 1];
		prod = mulmod(prod, c);
		prod = mulmod(prod, pow2[(u - 1) * (v - 1)]);
		prod = mulmod(prod, 2);
		result = addmod(result, prod);

		result = mulmod(result, 2);
		return result;
	}

	int countPatterns(int X, int Y, int sx, int sy) {
		pow2[0] = 1;
		for (int i = 1; i <= X * Y; i++)
			pow2[i] = (2 * pow2[i - 1]) % MOD_PRIME;

		int result = 1;
		for (int i = 1; i <= X; i++)
			for (int j = 1; j <= Y; j++) {
				int term = 0;
				if (i <= sx && j <= sy) {
					term = count1(i, j, sx, sy);
				} else if ((i <= sx && j > sy) || (i > sx && j <= sy)) {
					term = count2(i, j, sx, sy);
				} else if (i > sx && j > sy && i < 2 * sx && j < 2 * sy) {
					term = count3(i, j, sx, sy);
				} else {
					term = count4(i, j, sx, sy);
				}
				term = mulmod(term, X - i + 1);
				term = mulmod(term, Y - j + 1);
				result = addmod(result, term);
			}

		return result;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, int p1, int p2, int p3, bool hasAnswer, int p4) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << p2 << "," << p3;
	cout << "]" << endl;
	LitPanels *obj;
	int answer;
	obj = new LitPanels();
	clock_t startTime = clock();
	answer = obj->countPatterns(p0, p1, p2, p3);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p4 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p4;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	int p0;
	int p1;
	int p2;
	int p3;
	int p4;
	
	{
	// ----- test 0 -----
	p0 = 2;
	p1 = 2;
	p2 = 1;
	p3 = 1;
	p4 = 11;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = 2;
	p1 = 3;
	p2 = 1;
	p3 = 2;
	p4 = 40;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 4;
	p1 = 4;
	p2 = 3;
	p3 = 2;
	p4 = 14096;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = 40;
	p1 = 39;
	p2 = 5;
	p3 = 8;
	p4 = 877713074;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!

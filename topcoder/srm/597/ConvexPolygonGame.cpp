#include <vector>
#include <limits>
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

using namespace std;

long long mul_ll(long long a, long long b)
{
	return a * b;
}

template<typename T>
T divide_round_down(T a, T b)
{
	return a / b - (a % b < 0);
}

class ConvexPolygonGame {
public:
	string winner(vector <int> X, vector <int> Y) {
		vector<int> tx, ty;
		size_t pos = numeric_limits<size_t>::max();
		int lx = numeric_limits<int>::max();
		int rx = numeric_limits<int>::min();
		for (size_t i = 0; i < X.size(); i++) {
			if (X[i] < lx) {
				lx = X[i];
				pos = i;
			}
			if (X[i] > rx)
				rx = X[i];
		}
		for (size_t i = 0; i < X.size(); i++) {
			tx.push_back(X[(i + pos) % X.size()]);
			ty.push_back(Y[(i + pos) % X.size()]);
		}
		size_t i = 0;
		size_t j = 0;
		vector<int> px, py;
		for (int x = lx; x <= rx; x++) {
			while (x > tx[(i + 1) % X.size()])
				++i;
			while (x > tx[(j + X.size() - 1) % X.size()]) {
				j = (j + X.size() - 1) % X.size();
			}
			int ax = tx[i];
			int ay = ty[i];
			int bx = tx[(i + 1) % X.size()];
			int by = ty[(i + 1) % X.size()];
			int cx = tx[j];
			int cy = ty[j];
			int dx = tx[(j + X.size() - 1) % X.size()];
			int dy = ty[(j + X.size() - 1) % X.size()];

			int t, s;
			if (ax != bx && cx != dx) {
				long long tu = mul_ll(ay, bx - ax) + mul_ll(by - ay, x - ax);
				long long td = bx - ax;
				long long su = mul_ll(cy, dx - cx) + mul_ll(dy - cy, x - cx);
				long long sd = dx - cx;
				t = divide_round_down(tu + td - 1, td);
				s = divide_round_down(su, sd);
			} else {
				if (ax == bx) {
					t = min(ay, by);
					s = max(ay, by);
				} else {
					t = min(cy, dy);
					s = max(cy, dy);
				}
			}
			if ((x == ax && t == ay) || (x == bx && t == by))
				++t;
			if ((x == cx && s == cy) || (x == dx && s == dy))
				--s;
			if (t <= s) {
				int d = s - t + 1;
				if (px.size() == 0) {
					for (int y = t; y <= s && y <= t + 1; y++) {
						px.push_back(x);
						py.push_back(y);
					}
				} else if (px.size() == 1) {
					if (d == 1) {
						px.push_back(x);
						py.push_back(s);
					} else {
						return "Masha";
					}
				} else {
					if (d == 1) {
						int y = t;
						long long delta = mul_ll(px[0] - x, py[1] - y) - mul_ll(px[1] - x, py[0] - y);
						if (delta != 0)
							return "Masha";
					} else {
						return "Masha";
					}
				}
			}
		}
		return "Petya";
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, bool hasAnswer, string p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}";
	cout << "]" << endl;
	ConvexPolygonGame *obj;
	string answer;
	obj = new ConvexPolygonGame();
	clock_t startTime = clock();
	answer = obj->winner(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "\"" << p2 << "\"" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "\"" << answer << "\"" << endl;
	if (hasAnswer) {
		res = answer == p2;
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
	
	vector <int> p0;
	vector <int> p1;
	string p2;
	
	{
	// ----- test 0 -----
	int t0[] = {0,1,0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,0,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Petya";
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	int t0[] = {0,4,2};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,0,2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Masha";
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	int t0[] = {0,100,100,0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,0,100,100};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Masha";
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	int t0[] = {0,50,100,50};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,-1,0,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Petya";
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	int t0[] = {-100000,100000,100000,-100000};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {-1,-1,1,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "Masha";
	all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	int t0[] = {1,2,2,1,0,0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,0,1,2,2,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	all_right = KawigiEdit_RunTest(5, p0, p1, false, p2) && all_right;
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
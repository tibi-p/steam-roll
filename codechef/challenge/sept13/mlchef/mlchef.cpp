#include <algorithm>
#include <limits>
#include <vector>
#include <cstdio>
#include <cstring>

#define MAX_N 100001

#define pow2s(x) (((size_t) 1) << (x))

using namespace std;

struct tree_node {

	int alive;
	int min_health;
	int lazy_value;

	tree_node() : alive(0), min_health(numeric_limits<int>::max()), lazy_value(0) { }

};

vector<int> neighbours[MAX_N];
int health[MAX_N];
int prev[MAX_N];
int next[MAX_N];
int current_node;

tree_node tree[(1 << 18) - 1];

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

int get_msb(int n)
{
	int k = 0;
	for (; n > 0; n >>= 1)
		k++;
	return k;
}

int get_upper_exp(int n)
{
	return get_msb(n - 1);
}

void combine_nodes(tree_node &parent, const tree_node &left, const tree_node &right)
{
	parent.alive = left.alive + right.alive;
	parent.min_health = min(left.min_health, right.min_health);
}

size_t build_interval_tree(tree_node *tree, int n)
{
	const int num_bits = get_upper_exp(n);
	size_t tree_size = pow2s(num_bits + 1) - 1;

	size_t offset = pow2s(num_bits) - 1;
	for (int i = 0; i < n; i++) {
		size_t j = offset + (size_t) prev[i];
		tree[j].alive = (i != 0);
		tree[j].min_health = health[i];
	}

	for (size_t index = offset; index > 0;) {
		--index;
		size_t left_index = 2 * index + 1;
		size_t right_index = left_index + 1;
		tree_node &parent = tree[index];
		tree_node &left = tree[left_index];
		tree_node &right = tree[right_index];
		combine_nodes(parent, left, right);
	}

	return tree_size;
}

void propagate_flips(tree_node &node, int left_index, int right_index, bool has_children)
{
	if (node.lazy_value > 0) {
		int lazy_value = node.lazy_value;
		node.min_health -= lazy_value;
		node.lazy_value = 0;
		if (has_children) {
			tree[(size_t) left_index].lazy_value += lazy_value;
			tree[(size_t) right_index].lazy_value += lazy_value;
		}
	}
}

void kill_tree(int index, int start, int end)
{
	tree_node &node = tree[(size_t) index];
	int left_index = (index << 1) + 1;
	int right_index = left_index + 1;
	bool has_children = (start < end);

	propagate_flips(node, left_index, right_index, has_children);
	if (node.min_health > 0)
		return;

	if (has_children) {
		int mid = start + ((end - start) >> 1);
		kill_tree(left_index, start, mid);
		kill_tree(right_index, mid + 1, end);
		combine_nodes(node, tree[(size_t) left_index], tree[(size_t) right_index]);
	} else {
		node.min_health = numeric_limits<int>::max();
		node.alive = 0;
	}
}

tree_node update_tree(int index, int start, int end, int left, int right, int value)
{
	tree_node &node = tree[(size_t) index];
	int left_index = (index << 1) + 1;
	int right_index = left_index + 1;

	if (right < start || end < left) {
		propagate_flips(node, left_index, right_index, start < end);
		return node;
	}

	if (left <= start && end <= right) {
		node.lazy_value += value;
		if (node.min_health <= node.lazy_value)
			kill_tree(index, start, end);
		else
			propagate_flips(node, left_index, right_index, start < end);
	} else {
		propagate_flips(node, left_index, right_index, true);
		int mid = start + ((end - start) >> 1);
		tree_node left_node = update_tree(left_index, start, mid, left, right, value);
		tree_node right_node = update_tree(right_index, mid + 1, end, left, right, value);
		combine_nodes(node, left_node, right_node);
	}
	return node;
}

tree_node query_tree(int index, int start, int end, int left, int right)
{
	tree_node best_node;

	if (right < start || end < left)
		return best_node;

	int left_index = (index << 1) + 1;
	int right_index = left_index + 1;
	tree_node &parent_node = tree[(size_t) index];

	propagate_flips(parent_node, left_index, right_index, start < end);

	if (left <= start && end <= right)
		return parent_node;

	int mid = start + ((end - start) >> 1);
	tree_node left_node = query_tree(left_index, start, mid, left, right);
	tree_node right_node = query_tree(right_index, mid + 1, end, left, right);
	combine_nodes(best_node, left_node, right_node);
	return best_node;
}

tree_node update_full_tree(size_t tree_size, int left, int right, int value)
{
	return update_tree(0, 0, tree_size / 2, left, right, value);
}

tree_node query_full_tree(size_t tree_size, int left, int right)
{
	return query_tree(0, 0, tree_size / 2, left, right);
}

void dfs(int root)
{
	prev[root] = current_node;
	++current_node;
	for (vector<int>::iterator it = neighbours[root].begin(); it != neighbours[root].end(); ++it) {
		int node = *it;
		dfs(node);
	}
	next[root] = current_node - 1;
}

int solve_problem()
{
	int n, q;

	n = read_unsigned_integer<int>();
	health[0] = numeric_limits<int>::max();
	for (int i = 1; i <= n; i++) {
		health[i] = read_unsigned_integer<int>();
		int parent = read_unsigned_integer<int>();
		neighbours[parent].push_back(i);
	}

	current_node = 0;
	dfs(0);

	size_t tree_size = build_interval_tree(tree, n + 1);

	q = read_unsigned_integer<int>();
	for (int i = 0; i < q; i++) {
		int t = read_unsigned_integer<int>();
		if (t == 1) {
			int a = read_unsigned_integer<int>();
			int x = read_unsigned_integer<int>();
			int left = prev[a] + 1;
			int right = next[a];
			if (left <= right)
				update_full_tree(tree_size, left, right, x);
		} else {
			int a = read_unsigned_integer<int>();
			int left = prev[a] + 1;
			int right = next[a];
			int result = 0;
			if (left <= right)
				result = query_full_tree(tree_size, left, right).alive;
			printf("%d\n", result);
		}
	}

	return 0;
}

int main()
{
	solve_problem();
	return 0;
}

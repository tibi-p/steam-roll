#include <stdio.h>
#include <string.h>

#define BUFFER_LENGTH 1000
#define NUM_CHARACTERS 26

int solve_problem()
{
	int freq[NUM_CHARACTERS];
	char str[BUFFER_LENGTH + 10];
	size_t i, n;
	int result = 1;

	if (scanf("%s", str) != 1)
		return 1;

	n = strlen(str);
	memset(freq, 0, sizeof(freq));
	for (i = 0; i < n / 2; i++) {
		freq[str[i] - 'a']++;
		freq[str[n - 1 - i] - 'a']--;
	}

	for (i = 0; i < NUM_CHARACTERS; i++)
		if (freq[i] != 0) {
			result = 0;
			break;
		}

	printf("%s\n", result ? "YES" : "NO");

	return 0;
}

int main()
{
	int i, num_tests;

	if (scanf("%d", &num_tests) != 1)
		return 1;

	for (i = 0; i < num_tests; i++)
		solve_problem();

	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void reverse_string(char* str, int s, int e)
{
	for (int i = s; i <= (e + 1) / 2; i++) {
		char tmp;

		tmp = str[i];
		str[i] = str[e - i];
		str[e - i] = tmp;
	}
}

int main()
{
	char str[100];

	printf("Enter any string: ");
	scanf("%s", str);

	reverse_string(str, 0, strlen(str) - 1);

	printf("Reversed String is: %s", str);

	return 0;
} 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void reverse_string(char* str, int s, int e)
{
	if (s < e) {
		char tmp;

		tmp = str[s];
		str[s++] = str[e]; //s 하나씩 증가
		str[e--] = tmp; //e 하나씩 감소

		reverse_string(str, s, e);
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
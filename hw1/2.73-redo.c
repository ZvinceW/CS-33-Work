#include "limits.h"
#include <stdio.h>

int saturating_add(int x, int y)
{
	int xSign = x >> 31; //0 when positive, -1 when negative
	int ySign = y >> 31; //0 when positive, -1 when negative
	int sum = x + y;
	int sumSign = sum >> 31; //0 when positive, -1 when negative
	int *res;
	int isOver = (!xSign && !ySign) && __builtin_sadd_overflow(x, y, *res);
	int isNegOver = (!!xSign && !!ySign) && __builtin_sadd_overflow(x, y, *res);
	int isNormal = !(isOver || isNegOver);
	return (isOver)*(INT_MAX) + (isNegOver)*(INT_MIN) + (isNormal)*(sum);
}

int main ()
{
	printf("%d", saturating_add(3,4));
	printf("%d", saturating_add(2147483600,2147483600));
	printf("%d", saturating_add(-2147483600,-2147483600));
}
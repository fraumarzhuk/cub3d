#include "xMath.h"

int	is_whole(double number)
{
	if (floor(number) == number)
		return (1);
	return (0);
}
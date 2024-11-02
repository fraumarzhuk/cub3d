#include "xMath.h"

int	is_whole(double number)
{
	return (floor(number) == number);
}

int	is_whole_t(double number, double tolerance)
{
	return (floor(number) + tolerance >= number && floor(number) - tolerance <= number);
}
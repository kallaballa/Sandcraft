#include <math.h>

int
main(int argc, char *argv[])
{
	float f = 1.0;
	double d = 1.0;

	d = fabs(d);
	f = sqrtf(fabsf(f));
	return (f > d) ? 0 : 1;
}

#include "kernel.hh"

void	swap(double* a, double*b)
{
	double	c;

	c = *a;
	*a = *b;
	*b = c;
}

double		line_point(double start, double end, double p)
{
	return ((start + (end - start) * p));
}

double3		rotate_x(double3 v, double angle)
{
	double y = v[1];
	double c = cos(angle);
	double s = sin(angle);

	v[1] = y * c - s * v[2];
	v[2] = y * s + c * v[2];
	return (v);
}

double3		rotate_y(double3 v, double angle)
{
	double x = v[0];
	double c = cos(angle);
	double s = sin(angle);

	v[0] = x * c + s * v[2];
	v[2] = -x * s + c * v[2];
	return (v);
}

double3		rotate_z(double3 v, double angle)
{
	double x = v[0];
	double c = cos(angle);
	double s = sin(angle);

	v[0] = x * c - s * v[1];
	v[1] = x * s + c * v[1];
	return (v);
}

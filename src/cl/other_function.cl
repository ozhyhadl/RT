#include "kernel.h"

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

double3	rotate_camera(double3 direction, t_pov pov)
{
	double new_x;
	double new_y;
	double new_z;

	new_x = direction[0] * pov.cy + direction[2] * pov.sy;
	new_z = -direction[0] * pov.sy + direction[2] * pov.cy;
	direction[0] = new_x;
	direction[2] = new_z;
	new_y = direction[1] * pov.cx + direction[2] * pov.sx;
	new_z = -direction[1] * pov.sx + direction[2] * pov.cx;
	direction[1] = new_y;
	direction[2] = new_z;
	return (direction);
}

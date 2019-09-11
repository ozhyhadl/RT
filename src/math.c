#include "../includes/rt.h"

cl_double3	ft_rotate_camera(cl_double3 direction, t_pov pov)
{
	double new_x;
	double new_y;
	double new_z;

	new_x = direction.s[0] * pov.cy + direction.s[2] * pov.sy;
	new_z = -direction.s[0] * pov.sy + direction.s[2] * pov.cy;
	direction.s[0] = new_x;
	direction.s[2] = new_z;
	new_y = direction.s[1] * pov.cx + direction.s[2] * pov.sx;
	new_z = -direction.s[1] * pov.sx + direction.s[2] * pov.cx;
	direction.s[1] = new_y;
	direction.s[2] = new_z;
	return (direction);
}

cl_double3	add_double3(cl_double3 a, cl_double3 b)
{
	return ((cl_double3){{a.s[0] + b.s[0], a.s[1] + b.s[1], a.s[2] + b.s[2]}});
}

double		vector_len(cl_double3 a)
{
	return (sqrt(a.s[0] * a.s[0] + a.s[1] * a.s[1] + a.s[2] * a.s[2]));
}

cl_double3	ft_normalize(cl_double3 a)
{
	double	lenght;

	lenght = vector_len(a);

	return ((cl_double3){{a.s[0] / lenght, a.s[1] / lenght, a.s[2] / lenght}});
}
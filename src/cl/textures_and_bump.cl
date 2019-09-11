#include "kernel.h"

double2	cartesian_to_sperical_coords(double3 intersect_point, t_fig data)
{
	double		s;
	double		t;

	double3		point = intersect_point - data.shape.sphere.cent;
	if (length(data.rotation) > 0)
		point = rotate_z(rotate_y(rotate_x(point, data.rotation[0]), data.rotation[1]), data.rotation[2]);
	point = normalize(point);
	s = acos(point[2]) / PI;
	if (fabs(point[0]) < fabs(sin(s * PI))) //this is for arcos(x) where x < -1 or x > 1. \
												Could be optimized with 1 time caculus of sin
		t = acos(point[0] / sin(s * PI)) / (2 * PI);
	else
		t = point[0] < 0 ? 0.5 : 0;
	if (point[1] < 0)
		t = 1 - t;
	return ((double2)(s, t));
}

uint	get_texture_pixel(double2 coord, __global uint *texture, int no)
{
	int			is;
	int			it;

	is = coord[0] * 4095;
	it = coord[1] * 8191;
	return (texture[is * 8192 + it]);
}
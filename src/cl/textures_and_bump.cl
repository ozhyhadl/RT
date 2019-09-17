#include "kernel.h"

double3	new_basis(double3 point, t_rotation_matrix m)
{
	double3		res;

	res[0] = m.e1[0] * point[0] + m.e2[0] * point[1] + m.e3[0] * point[2];
	res[1] = m.e1[1] * point[0] + m.e2[1] * point[1] + m.e3[1] * point[2];
	res[2] = m.e1[2] * point[0] + m.e2[2] * point[1] + m.e3[2] * point[2];
	return (res);
}

double2	get_sperical_coords(double3 intersect_point, t_fig data)
{
	double2		st;
	double		tmp;

	double3		point = intersect_point - data.shape.sphere.cent;
	if (length(data.rotation) > 0)
		point = new_basis(point, data.rotation_martix);
	point = normalize(point);
	st[0] = acos(point[2]) / PI;
	tmp = sin(st[0] * PI);
	if (fabs(point[0]) < fabs(tmp))
		st[1] = acos(point[0] / tmp) / (2 * PI);
	else
		st[1] = point[0] < 0 ? 0.5 : 0;
	if (point[1] < 0)
		st[1] = 1 - st[1];
	st *= data.txt_scale;
	return (st);
}

double2	get_plane_coords(double3 intersect_point, t_fig data)
{
	double2		st;

	double3		point = intersect_point - data.shape.plane.dot;
	if (length(data.rotation) > 0)
		point = new_basis(point, data.rotation_martix);
	st = (double2)(point[0], point[1]);
	st *= data.txt_scale;
	return (st);
}

double2	get_cylin_coords(double3 intersect_point, t_fig data)
{
	double2		st;


	double3		point = intersect_point - data.shape.cone.vertex;
	if (length(data.rotation) > 0)
		point = new_basis(point, data.rotation_martix);
	st[1] = 0.5 + atan2(point[1], point[0]) / (PI); //what should be first what second?
	if (st[1] < 1)
		st[1] = 1 + st[1];
	st[0] = point[2];  //what should be first what second?
	return (st);
}

double2	get_cone_coords(double3 intersect_point, t_fig data)
{
	double2		st;

	double3		point = intersect_point - data.shape.sphere.cent;
	if (length(data.rotation) > 0)
		point = new_basis(point, data.rotation_martix);
	st[1] = atan2(point[1], point[0]) / (PI * 2); //what should be first what second?
	if (st[1] < 1)
		st[1] = 1 + st[1];
	st[0] = point[2]; //what should be first what second?
	st *= data.txt_scale; 
	return (st);
}

uint	get_texture_pixel(double2 coord, __global uint *texture, t_txt_params params, int no)
{
	int			is;
	int			it;

	is = coord[0] * (params.h - 1);
	it = coord[1] * (params.w - 1);
	is %= params.h;
	it %= params.w;
	return (texture[params.start_pos + is * params.w + it]);
}

double2	get_texture_space_coords(double3 intersect_point, t_fig data)
{
	double2	st;

	switch (data.fig_type)
	{
		case SPHERE:
			st = get_sperical_coords(intersect_point, data);
			break;
		case PLANE:
			st = get_plane_coords(intersect_point, data);
			break;
		case CYLIN:
			st = get_cylin_coords(intersect_point, data);
			break;
		case CONE:
			st = get_cone_coords(intersect_point, data);
			break;
	}
	st += data.txt_offset;
	st[0] = st[0] < 0 ? (abs((int)st[0]) + 1) + st[0] : st[0]; //just take the float part of float
	st[1] = st[1] < 0 ? (abs((int)st[1]) + 1) + st[1] : st[1]; //just take the float part of float
	return (st);
}

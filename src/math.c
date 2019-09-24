/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:49:51 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/22 18:55:38 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

cl_double3	ft_rotate_camera(cl_double3 direction, t_pov pov) //should be replaced with rotate_xyz() declarated below
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

cl_double2	*reverse_matrix_2x2(cl_double2 *src)
{
	cl_double2	col1;
	cl_double2	col2;
	double		det;

	col1 = src[0];
	col2 = src[1];

	det = det_matrix_2x2(src);
	src[0].s[0] = col2.s[1] / det;
	src[1].s[0] = -col2.s[0] / det;
	src[0].s[1] = -col1.s[1] / det;
	src[1].s[1] = col1.s[0] / det;
	return (src);
}

double		det_matrix_2x2(cl_double2 *src)
{
	return (src[0].s[0] * src[1].s[1] - src[1].s[0] * src[0].s[1]);
}

cl_double3	ft_rotate_reverse_camera(cl_double3 direction, t_pov pov)
{
	double new_x;
	double new_y;
	double new_z;

	new_y = direction.s[1] * pov.cx - direction.s[2] * pov.sx;
	new_z = direction.s[1] * pov.sx + direction.s[2] * pov.cx;
	direction.s[1] = new_y;
	direction.s[2] = new_z;
	new_x = direction.s[0] * pov.cy - direction.s[2] * pov.sy;
	new_z = direction.s[0] * pov.sy + direction.s[2] * pov.cy;
	direction.s[0] = new_x;
	direction.s[2] = new_z;

	return (direction);
}

cl_double3	add_double3(cl_double3 a, cl_double3 b)
{
	return ((cl_double3){{a.s[0] + b.s[0], a.s[1] + b.s[1], a.s[2] + b.s[2]}});
}

cl_double3	minus_double3(cl_double3 a, cl_double3 b)
{
	return ((cl_double3){{a.s[0] - b.s[0], a.s[1] - b.s[1], a.s[2] - b.s[2]}});
}

cl_double3	increase_double3(cl_double3 a, double multi)
{
	return ((cl_double3){{a.s[0] * multi, a.s[1] * multi, a.s[2] * multi}});
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

cl_double3		rotate_x(cl_double3 v, double angle)
{
	double y = v.s[1];
	double c = cos(angle);
	double s = sin(angle);

	v.s[1] = y * c - s * v.s[2];
	v.s[2] = y * s + c * v.s[2];
	return (v);
}

cl_double3		rotate_y(cl_double3 v, double angle)
{
	double x = v.s[0];
	double c = cos(angle);
	double s = sin(angle);

	v.s[0] = x * c + s * v.s[2];
	v.s[2] = -x * s + c * v.s[2];
	return (v);
}

cl_double3		rotate_z(cl_double3 v, double angle)
{
	double x = v.s[0];
	double c = cos(angle);
	double s = sin(angle);

	v.s[0] = x * c - s * v.s[1];
	v.s[1] = x * s + c * v.s[1];
	return (v);
}

cl_double3		rotate_xyz(cl_double3 v, cl_double3 a)
{
	return (rotate_x(rotate_y(rotate_z(v, a.s[2]), a.s[1]), a.s[0]));
}

t_rotation_matrix build_rotation_matrix_form_angles(cl_double3 rot)
{
	t_rotation_matrix	res;
	
	res.e1 = (cl_double3){{1.0, 0, 0}};
	res.e2 = (cl_double3){{0, 1.0, 0}};
	res.e3 = (cl_double3){{0, 0, 1.0}};

	res.e1 = rotate_xyz(res.e1, rot);
	res.e2 = rotate_xyz(res.e2, rot);
	res.e3 = rotate_xyz(res.e3, rot);

	res.e1 = ft_normalize(res.e1);
	res.e2 = ft_normalize(res.e2);
	res.e3 = ft_normalize(res.e3);
	return (res);
}

cl_double3		cross(cl_double3 a, cl_double3 b)
{
	return ((cl_double3){a.s[1] * b.s[2] - a.s[2] * b.s[1], \
							a.s[2] * b.s[0] - a.s[0] * b.s[2], \
							a.s[0] * b.s[1] - a.s[1] * b.s[0]});
}

t_rotation_matrix build_rotation_matrix_for_cylin(cl_double3 dir)
{
	t_rotation_matrix	rm;

	rm.e3 = dir;
	rm.e1 = (cl_double3){{1, 1, 0}}; //dovilnii napryamok golovne shchob buv ortogonalnii
	rm.e1.s[2] = -(rm.e3.s[0] * rm.e1.s[0] + rm.e3.s[1] * rm.e1.s[1]) / rm.e3.s[2];
	rm.e2 = cross(rm.e3, rm.e1);
	printf("%f %f %f\n%f %f %f\n%f %f %f\n", rm.e1.s[0], rm.e1.s[1], rm.e1.s[2], rm.e2.s[0], rm.e2.s[1], rm.e2.s[2], rm.e3.s[0], rm.e3.s[1], rm.e3.s[2]);
	fflush(stdout);
	return (rm);
}
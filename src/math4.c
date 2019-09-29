/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:48:48 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/27 18:11:58 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

cl_double3			rotate_z(cl_double3 v, double angle)
{
	double x;
	double c;
	double s;

	x = v.s[0];
	c = cos(angle);
	s = sin(angle);
	v.s[0] = x * c - s * v.s[1];
	v.s[1] = x * s + c * v.s[1];
	return (v);
}

cl_double3			rotate_xyz(cl_double3 v, cl_double3 a)
{
	return (rotate_x(rotate_y(rotate_z(v, a.s[2]), a.s[1]), a.s[0]));
}

t_rotation_matrix	build_rotation_matrix_form_angles(cl_double3 rot)
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

cl_double3			cross(cl_double3 a, cl_double3 b)
{
	return ((cl_double3){{a.s[1] * b.s[2] - a.s[2] * b.s[1], \
							a.s[2] * b.s[0] - a.s[0] * b.s[2], \
							a.s[0] * b.s[1] - a.s[1] * b.s[0]}});
}

int					check_rectangle_in_plane(t_rectangle_data rectange)
{
	cl_double	h;
	cl_double3	n;
	cl_double3	v1;
	cl_double3	v2;

	v1 = minus_double3(rectange.v1, rectange.v0);
	v2 = minus_double3(rectange.v2, rectange.v0);
	n = cross(v1, v2);
	h = -n.s[0] * rectange.v1.s[0] - n.s[1] * \
		rectange.v1.s[1] - n.s[2] * rectange.v1.s[2];
	if (comp_real(dot(n, rectange.v3) + h, 0, 1))
		return (1);
	return (0);
}

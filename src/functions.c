/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:17:16 by anri              #+#    #+#             */
/*   Updated: 2019/09/28 11:22:41 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

cl_double3			*get_obj_dot(t_fig *fig)
{
	if (fig->fig_type == SPHERE)
		return (&fig->shape.sphere.cent);
	else if (fig->fig_type == PLANE)
		return (&fig->shape.plane.dot);
	else if (fig->fig_type == CONE)
		return (&fig->shape.cone.vertex);
	else if (fig->fig_type == CYLIN)
		return (&fig->shape.cylin.dot);
	else if (fig->fig_type == TORUS)
		return (&fig->shape.torus.cent);
	else if (fig->fig_type == ELLIPSE)
		return (&fig->shape.ellipse.cent);
	else if (fig->fig_type == DISK)
		return (&fig->shape.disk.cent);
	return (0);
}

t_rotation_matrix	build_rotation_matrix_for_rectangles(\
cl_double3 normal, t_rectangle_data r)
{
	t_rotation_matrix	rm;

	rm.e3 = ft_normalize(normal);
	rm.e1 = ft_normalize(minus_double3(r.v1, r.v0));
	rm.e2 = cross(rm.e3, rm.e1);
	rm.e2 = ft_normalize(rm.e2);
	return (rm);
}

cl_double3			normal_for_triangle_or_rectangle(t_fig fig)
{
	t_triangle_data		t;
	t_rectangle_data	r;
	cl_double3			v0;
	cl_double3			v1;

	if (fig.fig_type == TRIANGLE)
	{
		t = fig.shape.triangle;
		v0 = minus_double3(t.v1, t.v0);
		v1 = minus_double3(t.v2, t.v0);
		return (ft_normalize(cross(v0, v1)));
	}
	else
	{
		r = fig.shape.rectangle;
		v0 = minus_double3(r.v1, r.v0);
		v1 = minus_double3(r.v2, r.v0);
		return (ft_normalize(cross(v0, v1)));
	}
}

cl_double3			get_obj_dir(t_fig fig)
{
	if (fig.fig_type == SPHERE)
		return (fig.rotation);
	else if (fig.fig_type == PLANE)
		return (fig.shape.plane.normal);
	else if (fig.fig_type == CONE)
		return (fig.shape.cone.dir);
	else if (fig.fig_type == CYLIN)
		return (fig.shape.cylin.dir);
	else if (fig.fig_type == TORUS)
		return (fig.shape.torus.cent);
	else if (fig.fig_type == ELLIPSE)
		return (fig.shape.ellipse.dir);
	else if (fig.fig_type == TRIANGLE)
		return (normal_for_triangle_or_rectangle(fig));
	else if (fig.fig_type == RECTANGLE)
		return (normal_for_triangle_or_rectangle(fig));
	else if (fig.fig_type == DISK)
		return (fig.shape.disk.normal);
	return (fig.rotation);
}

t_rectangle_data	set_rectangles(cl_double3 *v, int r)
{
	if (r == 0)
		return ((t_rectangle_data){v[0], v[1], v[2], v[3]});
	else if (r == 1)
		return ((t_rectangle_data){v[0], v[3], v[7], v[4]});
	else if (r == 2)
		return ((t_rectangle_data){v[3], v[7], v[6], v[2]});
	else if (r == 3)
		return ((t_rectangle_data){v[6], v[2], v[1], v[5]});
	else if (r == 4)
		return ((t_rectangle_data){v[7], v[6], v[5], v[4]});
	else
		return ((t_rectangle_data){v[0], v[4], v[5], v[1]});
}

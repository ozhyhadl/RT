/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_create_obj2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:39:38 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/27 19:46:40 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_create_disk(t_scene *scene, int i, t_filters *filter)
{
	scene->obj[i].fig_type = (cl_int)DISK;
	scene->obj[i].shape.disk.cent = (cl_double3){{0, 0, 0}};
	scene->obj[i].shape.disk.normal = (cl_double3){{0, 0, 1}};
	scene->obj[i].shape.disk.radius = 1;
	ft_create_all(scene, i, filter);
}

void	ft_create_triangle(t_scene *scene, int i, t_filters *filter)
{
	scene->obj[i].fig_type = (cl_int)TRIANGLE;
	scene->obj[i].shape.triangle.v0 = (cl_double3){{1, 1, 1}};
	scene->obj[i].shape.triangle.v1 = (cl_double3){{-1, 1, 1}};
	scene->obj[i].shape.triangle.v2 = (cl_double3){{0, -1, 1}};
	ft_create_all(scene, i, filter);
}

void	ft_create_rectangle(t_scene *scene, int i, t_filters *filter)
{
	scene->obj[i].fig_type = (cl_int)RECTANGLE;
	scene->obj[i].shape.rectangle.v0 = (cl_double3){{1, 1, 0}};
	scene->obj[i].shape.rectangle.v1 = (cl_double3){{-1, 1, 0}};
	scene->obj[i].shape.rectangle.v2 = (cl_double3){{-1, -1, 0}};
	scene->obj[i].shape.rectangle.v3 = (cl_double3){{1, -1, 0}};
	ft_create_all(scene, i, filter);
}

void	ft_create_ellipse(t_scene *scene, int i, t_filters *filter)
{
	scene->obj[i].fig_type = (cl_int)ELLIPSE;
	scene->obj[i].shape.ellipse.cent = (cl_double3){{0, 0, 0}};
	scene->obj[i].shape.ellipse.dir = (cl_double3){{0, 0, 1}};
	scene->obj[i].shape.ellipse.radius_sum = 2;
	scene->obj[i].shape.ellipse.dist_btwn_cent = 1.5;
	ft_create_all(scene, i, filter);
}

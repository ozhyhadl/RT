/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_create_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:47:05 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 13:03:46 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		ft_create_all(t_scene *scene, int i, t_filters *filter)
{
	scene->obj[i].color = (cl_double3){{255, 0, 0}};
	scene->obj[i].color_index = -1;
	scene->obj[i].specular = (cl_int)-1;
	scene->obj[i].reflective = 0;
	scene->obj[i].trans = 0;
	scene->obj[i].text_no = -1;
	scene->obj[i].noise = -1;
	scene->obj[i].normal_map_no = -1;
	scene->obj[i].txt_offset = (cl_double2){{0, 0}};
	scene->obj[i].txt_scale = (cl_double2){{1, 1}};
	scene->obj[i].rotation = (cl_double3){{M_PI / 2, 0, 0}};
	scene->obj[i].rotation_martix = build_rotation_matrix_for_dir(\
	get_obj_dir(scene->obj[i]));
	scene->obj[i].ior = MIN_IOR;
	scene->obj[i].cutting = 0;
	scene->obj[i].transparancy_map_no = -1;
	scene->obj[i].cutting_plane.dot = (cl_double3){{0, 0, 0}};
	scene->obj[i].cutting_plane.normal = (cl_double3){{0, 1, 1}};
	scene->obj[i].complex_fig = -1;
	filter->obj_movement[i].move = 0;
	filter->obj_movement[i].dir = (cl_double3){{0, 1, 1}};
}

void		ft_create_spher(t_scene *scene, int i, t_filters *filter)
{
	scene->obj[i].fig_type = (cl_int)SPHERE;
	scene->obj[i].shape.sphere.cent = (cl_double3){{0, 0, 0}};
	scene->obj[i].shape.sphere.radius = 1.0;
	ft_create_all(scene, i, filter);
}

void		ft_create_pale(t_scene *scene, int i, t_filters *filter)
{
	scene->obj[i].fig_type = (cl_int)PLANE;
	scene->obj[i].shape.plane.dot = (cl_double3){{0, 0, 0}};
	scene->obj[i].shape.plane.normal = (cl_double3){{0, 1, 0}};
	ft_create_all(scene, i, filter);
}

void		ft_create_cone(t_scene *scene, int i, t_filters *filter)
{
	scene->obj[i].fig_type = (cl_int)CONE;
	scene->obj[i].shape.cone.dir = (cl_double3){{0, 1, 0}};
	scene->obj[i].shape.cone.vertex = (cl_double3){{0, 0, 0}};
	scene->obj[i].shape.cone.tangent = 0.24;
	scene->obj[i].shape.cone.mmax = BIG_VALUE;
	scene->obj[i].shape.cone.mmin = -BIG_VALUE;
	ft_create_all(scene, i, filter);
}

void		ft_create_cylin(t_scene *scene, int i, t_filters *filter)
{
	scene->obj[i].fig_type = (cl_int)CYLIN;
	scene->obj[i].shape.cylin.dir = (cl_double3){{1, 0, 0}};
	scene->obj[i].shape.cylin.dot = (cl_double3){{0, 0, 0}};
	scene->obj[i].shape.cylin.radius = 1.0;
	scene->obj[i].shape.cylin.mmax = BIG_VALUE;
	scene->obj[i].shape.cylin.mmin = -BIG_VALUE;
	ft_create_all(scene, i, filter);
}

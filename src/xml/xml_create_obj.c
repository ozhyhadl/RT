/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_create_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:47:05 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/12 20:18:45 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

static void	ft_create_all(t_scene *scene, int i)
{
	scene->obj[i].color = (cl_double3){{255, 0, 0}};
	scene->obj[i].specular = (cl_int)500;
	scene->obj[i].reflective = (cl_double)0;
	scene->obj[i].trans = (cl_double) 0;
	scene->obj[i].text_no = -1;
	scene->obj[i].normal_map_no = -1;
}

void		ft_create_spher(t_scene *scene, int i)
{
	scene->obj[i].fig_type = (cl_int)SPHERE;
	scene->obj[i].shape.sphere.cent = (cl_double3){{0, 0, 0}};
	scene->obj[i].shape.sphere.radius = (cl_double)1;
	ft_create_all(scene, i);
}

void		ft_create_pale(t_scene *scene, int i)
{
	scene->obj[i].fig_type = (cl_int)PLANE;
	scene->obj[i].shape.plane.dot = (cl_double3){{0, 0, 0}};
	scene->obj[i].shape.plane.normal = (cl_double3){{0, 1, 0}};
	ft_create_all(scene, i);
}

void		ft_create_cone(t_scene *scene, int i)
{
	scene->obj[i].fig_type = (cl_int)CONE;
	scene->obj[i].shape.cone.dir = (cl_double3){{0, 1, 0}};
	scene->obj[i].shape.cone.vertex = (cl_double3){{0, 0, 0}};
	scene->obj[i].shape.cone.tangent = 0.24;
	ft_create_all(scene, i);
}

void		ft_create_cylin(t_scene *scene, int i)
{
	scene->obj[i].fig_type = (cl_int)CYLIN;
	scene->obj[i].shape.cylin.dir = (cl_double3){{1, 0, 0}};
	scene->obj[i].shape.cylin.dot = (cl_double3){{0, 0, 0}};
	scene->obj[i].shape.cylin.radius = (cl_double)1;
	ft_create_all(scene, i);
}
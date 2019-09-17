/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_add_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:11:17 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/16 20:23:42 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	add_for_all_obj(const char *str, t_scene *scene, int i, const char *tag)
{
	cl_double	one_dot;

	if (!ft_get_3param(1, str, NULL, &one_dot))
		return (1);
	else if (ft_strequ(tag, "specular") && (one_dot < -1 || one_dot > 1000))
		return (error_message(RED"XML: -1 <= specular <= 1000"COLOR_OFF));
	else if (ft_strequ(tag, "reflective") && (one_dot < 0 || one_dot > 1))
		return (error_message(RED"XML: 0 <= reflective <= 1"COLOR_OFF));
	else if (ft_strequ(tag, "transparency") && (one_dot < 0 || one_dot > 1))
		return (error_message(RED"XML: 0 <= transparency <= 1"COLOR_OFF));
	else if (ft_strequ(tag, "specular"))
		scene->obj[i].specular = (cl_int)ft_atoi(str);
	else if (ft_strequ(tag, "reflective"))
		scene->obj[i].reflective = (cl_double)one_dot;
	else if (ft_strequ(tag, "transparency"))
		scene->obj[i].trans = (cl_double)one_dot;
	else if (ft_strequ(tag, "texture"))
		scene->obj[i].text_no = (cl_int)ft_atoi(str);
	else if (ft_strequ(tag, "bump"))
		scene->obj[i].normal_map_no = (cl_int)ft_atoi(str);
	else
		return (1);
	return (0);
}

int	add_position(const char *str, t_scene *scene, int i, const char *tag)
{
	cl_double3	dot;

	if (ft_strequ(tag, "centre") && scene->obj[i].fig_type == SPHERE && \
		ft_get_3param(3, str, &dot, NULL))
		scene->obj[i].shape.sphere.cent = (cl_double3)dot;
	else if (ft_strequ(tag, "dot") && scene->obj[i].fig_type == PLANE \
		&& ft_get_3param(3, str, &dot, NULL))
		scene->obj[i].shape.plane.dot = (cl_double3)dot;
	else if (ft_strequ(tag, "vertex") && scene->obj[i].fig_type == CONE \
		&& ft_get_3param(3, str, &dot, NULL))
		scene->obj[i].shape.cone.vertex = (cl_double3)dot;
	else if (ft_strequ(tag, "dot") && scene->obj[i].fig_type == CYLIN \
			&& ft_get_3param(3, str, &dot, NULL))
		scene->obj[i].shape.cylin.dot = (cl_double3)dot;
	else
	{
		ft_putstr(RED"XML : invalid param "COLOR_OFF);
		ft_putstr(tag);
		ft_putendl(RED"spher -> centre, plane/cylin -> dot, cone -> vertex"\
			COLOR_OFF);
		return (1);
	}
	return (0);
}

int	ft_add_radius(const char *str, t_scene *scene, int i)
{
	cl_double one_dot;

	if (!ft_get_3param(1, str, NULL, &one_dot))
		return (1);
	if (one_dot < 1)
		return (error_message(RED"XML: Radius must be >= 1"COLOR_OFF));
	if (scene->obj[i].fig_type == SPHERE)
		scene->obj[i].shape.sphere.radius = (cl_double)one_dot;
	else if (scene->obj[i].fig_type == CYLIN)
		scene->obj[i].shape.cylin.radius = (cl_double)one_dot;
	else
	{
		ft_putendl(RED"XML : invalid param(radius have spher/cylin)"COLOR_OFF);
		return (1);
	}
	return (0);
}

int	ft_add_normal_dir(const char *str, t_scene *scene, int i, const char *tag)
{
	cl_double3	dot;

	if (!ft_get_3param(3, str, &dot, NULL))
		return (1);
	if (ft_strequ(tag, "normal") && scene->obj[i].fig_type == PLANE)
		scene->obj[i].shape.plane.normal = ft_normalize((cl_double3)dot);
	else if (ft_strequ(tag, "dir") && scene->obj[i].fig_type == CYLIN)
		scene->obj[i].shape.cylin.dir = ft_normalize((cl_double3)dot);
	else if (ft_strequ(tag, "dir") && scene->obj[i].fig_type == CONE)
		scene->obj[i].shape.cone.dir = ft_normalize((cl_double3)dot);
	else
	{
		if (ft_strequ(tag, "normal"))
			ft_putendl(RED\
				"XML : invalid param(only plane has normal)"COLOR_OFF);
		else
			ft_putendl(RED\
				"XML : invalid param(only cone/cylin has dir)"COLOR_OFF);
		return (1);
	}
	return (0);
}

int	ft_add_tanget(const char *str, t_scene *scene, int i)
{
	cl_double one_dot;

	if (scene->obj[i].fig_type == CONE && ft_get_3param(1, str, NULL, &one_dot))
		if (one_dot >= 0.1 && one_dot < 180)
			scene->obj[i].shape.cone.tangent = (cl_double)one_dot * M_PI / 180.0;
		else
			return (error_message(RED"XML : 0.1˚ < angle < 180˚"COLOR_OFF));
	else
	{
		ft_putendl(RED"XML : invalid param(only the cone has angle)"COLOR_OFF);
		return (1);
	}
	return (0);
}
